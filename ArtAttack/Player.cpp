#include "pch.h"
#include "Player.h"

using namespace DirectX;
using namespace MattMath;
using namespace player_consts;
using namespace colour_consts;

Player::Player(const RectangleF& rectangle,
    const PlayerAnimationInfo& animation_info,
    ResourceManager* resource_manager,
    int player_num,
    player_team team,
    wep_type primary,
    std::unique_ptr<Weapon> primary_weapon,
    wep_type secondary,
    const Colour& team_colour,
    const Viewport& view_port,
    const float* dt,
    const MattMath::Vector2F& respawn_position,
    const Vector2F& velocity,
    float rotation,
    const Vector2F& origin,
    SpriteEffects effects,
    float layer_depth) :
    MovingObject(velocity),
    AnimationObject(dt, animation_info.sprite_sheet,
                    animation_info.animation,
                    resource_manager, DEFAULT_PLAYER_COLOUR, rotation, origin, effects, layer_depth),
    TextureObject(animation_info.sprite_sheet, animation_info.uniform_texture,
                  resource_manager, team_colour, rotation, origin, effects, layer_depth),
    _primary(std::move(primary_weapon)),
    _player_num(player_num),
    _team(team),
    _primary_type(primary),
    _secondary_type(secondary),
    _team_colour(team_colour),
    _viewport(view_port),
    _rectangle(rectangle),
    _prev_rectangle(rectangle),
    _respawn_position(respawn_position),
    _dt(dt)
{
    this->_sound_bank = resource_manager->get_sound_bank(SOUND_BANK);
}

void Player::draw(SpriteBatch* sprite_batch, const Camera& camera)
{
    if (this->_state == player_state::DEAD)
    {
        return;
    }
    
    player_animation_state current_animation_state = this->_animation_state;
    player_animation_state new_animation_state = this->calculate_animation_state();

    if (current_animation_state != new_animation_state)
    {
		this->_animation_state = new_animation_state;

        const PlayerAnimationInfo& info = this->get_animation_info(new_animation_state);
        TextureObject::set_sprite_sheet_name(info.sprite_sheet);
        TextureObject::set_element_name(info.uniform_texture);

        set_animation_strip_and_reset(info.sprite_sheet, info.animation);
        if (info.frame_time != FLT_MIN)
        {
            set_frame_time(info.frame_time);
		}
        else
        {
			set_frame_time_to_default();
        }
	}

    SpriteEffects effects = SpriteEffects_None;
    bool facing_right = this->get_facing_right();
    if (!facing_right)
    {
        effects = SpriteEffects_FlipHorizontally;
    }

    TextureObject::set_effects(effects);
    TextureObject::draw(sprite_batch, this->_rectangle, camera);

    AnimationObject::set_effects(effects);
    AnimationObject::draw(sprite_batch, this->_rectangle, camera);

    this->_primary->draw(sprite_batch, camera, this->_showing_debug);
}
void Player::draw(SpriteBatch* sprite_batch)
{
    AnimationObject::draw(sprite_batch, this->_rectangle, Camera::DEFAULT_CAMERA);
	this->_primary->draw(sprite_batch, Camera::DEFAULT_CAMERA);
}
collision_object_type Player::get_collision_object_type() const
{
    if (this->_state == player_state::ALIVE)
    {
        switch (this->_team)
        {
        case player_team::A:
            return collision_object_type::PLAYER_TEAM_A;
        case player_team::B:
            return collision_object_type::PLAYER_TEAM_B;
        default:
            throw std::exception("Invalid player team");
        };
    }
    else if (this->_state == player_state::DEAD)
	{
		switch (this->_team)
		{
		case player_team::A:
			return collision_object_type::PLAYER_TEAM_A_DEAD;
		case player_team::B:
			return collision_object_type::PLAYER_TEAM_B_DEAD;
		default:
			throw std::exception("Invalid player team");
		};
	}
	else
	{
		throw std::exception("Invalid player state");
	}

}
const Shape* Player::get_shape() const
{
	return this->get_collision_rectangle();
}
bool Player::get_for_deletion() const
{
	return false;
}

const RectangleF* Player::get_collision_rectangle() const
{
	return &this->_rectangle;
}

bool Player::is_matching_collision_object_type(
    const ICollisionGameObject* other)
{
    collision_object_type other_type = other->get_collision_object_type();
    return is_structure(other_type);
}
bool Player::is_colliding(const ICollisionGameObject* other) const
{
    // dead check
    if (this->_state == player_state::DEAD)
	{
		return false;
	}
    
    // type check
    if (!is_matching_collision_object_type(other))
    {
        return false;
    }

    // aabb check
    if (!this->get_shape()->AABB_intersects(other->get_shape()))
    {
        return false;
    }
    else // AABBs are intersecting
    {
        // if the other object is a rectangle, then we have a collision
        // since the AABB check passed
        shape_type other_shape_type = other->get_shape()->get_shape_type();
        if (other_shape_type == shape_type::RECTANGLE)
        {
            return true;
        }
    }

    // narrow phase check
    if (this->get_shape()->intersects(other->get_shape()))
    {
        return true;
    }

    return false;
}
void Player::on_collision(const ICollisionGameObject* other)
{
    collision_object_type other_type = other->get_collision_object_type();

    bool structure_collision =
        other_type == collision_object_type::STRUCTURE ||
        other_type == collision_object_type::STRUCTURE_PAINTABLE;

    bool structure_jump_through_collision =
		other_type == collision_object_type::STRUCTURE_JUMP_THROUGH;

	bool structure_ramp_collision = is_structure_ramp(other_type);

    player_team team = this->_team;
    bool projectile_collision = false;
    if (team == player_team::A)
    {
            bool projectile_team_b =
            other_type == collision_object_type::PROJECTILE_SPRAY_TEAM_B ||
            other_type == collision_object_type::PROJECTILE_JET_TEAM_B ||
            other_type == collision_object_type::PROJECTILE_ROLLING_TEAM_B ||
            other_type == collision_object_type::PROJECTILE_BALL_TEAM_B ||
            other_type == collision_object_type::PROJECTILE_MIST_TEAM_B;

        projectile_collision = projectile_team_b;
    }
    else if (team == player_team::B)
    {
        bool projectile_team_a =
            other_type == collision_object_type::PROJECTILE_SPRAY_TEAM_A ||
            other_type == collision_object_type::PROJECTILE_JET_TEAM_A ||
            other_type == collision_object_type::PROJECTILE_ROLLING_TEAM_A ||
            other_type == collision_object_type::PROJECTILE_BALL_TEAM_A ||
            other_type == collision_object_type::PROJECTILE_MIST_TEAM_A;

        projectile_collision = projectile_team_a;
    }

    if (projectile_collision)
	{
		this->on_projectile_collision(other);
	}
    else if (structure_collision)
    {
		this->on_structure_collision(other);
	}
    else if (structure_jump_through_collision)
	{
		this->on_structure_jump_through_collision(other);
	}
	else if (structure_ramp_collision)
	{
		this->on_structure_ramp_collision(other);
	}
	else
	{
		throw std::exception("Invalid collision object type.");
	}
}
void Player::on_structure_ramp_collision(const ICollisionGameObject* other)
{
    Vector2F direction = CollisionTools::calculate_object_collision_direction(
        this->get_shape(), other->get_shape());

	direction = Vector2F::direction_to_8_cardinal_direction(direction);

	collision_object_type other_type = other->get_collision_object_type();

	bool bottom_edge_collision = direction == Vector2F::DIRECTION_UP ||
		direction == Vector2F::DIRECTION_UP_LEFT ||
		direction == Vector2F::DIRECTION_UP_RIGHT;

	bool side_wall_collision = (direction == Vector2F::DIRECTION_RIGHT &&
        other_type == collision_object_type::STRUCTURE_RAMP_LEFT) 
		|| (direction == Vector2F::DIRECTION_LEFT &&
			other_type == collision_object_type::STRUCTURE_RAMP_RIGHT);

	bool perform_structure_collision = bottom_edge_collision || side_wall_collision;

	if (perform_structure_collision)
	{
		this->on_structure_collision(other);
		return;
    }
    
	bool is_on_ramp = this->get_move_state() == player_move_state::ON_RAMP_LEFT ||
		this->get_move_state() == player_move_state::ON_RAMP_RIGHT;

	if (other_type == collision_object_type::STRUCTURE_RAMP_LEFT)
	{
        // TODO
	}
	else if (other_type == collision_object_type::STRUCTURE_RAMP_RIGHT)
	{
        if (direction == Vector2F::DIRECTION_DOWN)
        {
            CollisionTools::resolve_object_collision(&this->_rectangle,
                other->get_shape(), Vector2F::DIRECTION_DOWN);

            this->set_move_state(player_move_state::ON_RAMP_RIGHT);

            this->set_velocity_y(0.0f);
        }
        else if (direction == Vector2F::DIRECTION_RIGHT)
        {
            CollisionTools::resolve_object_collision(&this->_rectangle,
                other->get_shape(), Vector2F::DIRECTION_DOWN);

            this->set_move_state(player_move_state::ON_RAMP_RIGHT);

            this->set_velocity_y(0.0f);
        }
        else if (direction == Vector2F::DIRECTION_DOWN_LEFT)
        {
            CollisionTools::resolve_object_collision(&this->_rectangle,
                other->get_shape(), Vector2F::DIRECTION_DOWN);

            this->set_move_state(player_move_state::ON_RAMP_RIGHT);

            this->set_velocity_y(0.0f);
            
            /*player_move_state move_state = this->get_move_state();

			RectangleF ramp_rect = other->get_shape()->get_bounding_box();

			Point2F player_center = this->get_center();
            Point2F ramp_top = ramp_rect.get_top();

            MattMath::direction dir = this->get_velocity().get_direction();
            bool moving_up = dir == direction::UP || dir == direction::UP_LEFT ||
                dir == direction::UP_RIGHT;

            if (move_state == player_move_state::ON_RAMP_RIGHT ||
				(player_center.y < ramp_top.y && !moving_up))

            {
                CollisionTools::resolve_object_collision(&this->_rectangle,
                    other->get_shape(), Vector2F::DIRECTION_DOWN);

                this->set_move_state(player_move_state::ON_RAMP_RIGHT);

                this->set_velocity_y(0.0f);
            }
            else
            {
                CollisionTools::resolve_object_collision(&this->_rectangle,
                    other->get_shape(), Vector2F::DIRECTION_LEFT);

				this->set_velocity_x(0.0f);
            }*/
        }
        else if (direction == Vector2F::DIRECTION_DOWN_RIGHT)
        {
            CollisionTools::resolve_object_collision(&this->_rectangle,
                other->get_shape(), Vector2F::DIRECTION_DOWN);

            this->set_move_state(player_move_state::ON_RAMP_RIGHT);

            this->set_velocity_y(0.0f);
        }
        else if (direction == Vector2F::ZERO)
        {
            throw std::exception("No collision direction.");
        }
		else
        {
            throw std::exception("Invalid collision direction.");
        }
	}
	else
	{
		throw std::exception("Invalid ramp type.");
	}   
}
void Player::on_structure_jump_through_collision(const ICollisionGameObject* other)
{
    // only collide if player is moving down and on previous cycle
    // was above the structure
    
    Vector2F velocity = this->get_velocity();
    direction dir = velocity.get_direction();

    bool moving_down = dir == direction::DOWN || dir == direction::DOWN_LEFT ||
        dir == direction::DOWN_RIGHT;

    const RectangleF& other_rect = other->get_shape()->get_bounding_box();
    bool was_above = this->_prev_rectangle.get_bottom() <= other_rect.get_top();

    player_move_state move_state = this->get_move_state();

    if (moving_down && was_above && move_state != player_move_state::DROPPING_DOWN)
	{
        MovingObject::set_velocity_y(0.0f);

        const RectangleF& rect = other->get_shape()->get_bounding_box();
        this->_rectangle.set_position_y_from_bottom(rect.get_top());
        this->set_move_state(player_move_state::ON_DROP_DOWN_GROUND);
	}
	else
	{
		// no collision
	}
}
void Player::on_structure_collision(const ICollisionGameObject* other)
{
	//Vector2F col_direction = CollisionTools::calculate_object_collision_direction(
	//	this->get_shape(), other->get_shape());

	//if (col_direction == Vector2F::ZERO)
 //   {
	//	throw std::exception("Player and structure are not colliding.");
	//}
 //   
	//Vector2F cardinal_col_direction = Vector2F::direction_to_8_cardinal_direction(col_direction);

 //   Vector2F player_direction = Vector2F::unit_vector(this->get_dx());

 //   
	//// check for wall collision
	//if (cardinal_col_direction == Vector2F::DIRECTION_LEFT ||
	//	cardinal_col_direction == Vector2F::DIRECTION_RIGHT)
	//{
 //       CollisionTools::resolve_object_collision(&this->_rectangle,
 //           other->get_shape(), Vector2F(col_direction.x, 0.0f));

 //       this->on_wall_collision();
	//}
 ////   // ground or ceiling collision
	////else
 ////   if (cardinal_col_direction == Vector2F::DIRECTION_UP ||
	////	cardinal_col_direction == Vector2F::DIRECTION_DOWN)
 ////   {
	////	if (player_direction.y > 0.0f)
	////	{
	////		this->on_ground_collision();

 ////           CollisionTools::resolve_object_collision(&this->_rectangle,
 ////               other->get_shape(), Vector2F(0.0f, col_direction.y));
	////	}
	////	else if (player_direction.y < 0.0f)
	////	{
	////		this->on_ceiling_collision();

 ////           CollisionTools::resolve_object_collision(&this->_rectangle,
 ////               other->get_shape(), Vector2F(0.0f, col_direction.y));
	////	}
	////}
	//// up collision
	//else 
 //   if (cardinal_col_direction == Vector2F::DIRECTION_UP_LEFT ||
	//	cardinal_col_direction == Vector2F::DIRECTION_UP_RIGHT ||
	//	cardinal_col_direction == Vector2F::DIRECTION_UP)
	//{
 //       Vector2F amount = CollisionTools::calculate_object_collision_depth(
	//		this->get_shape(), other->get_shape(), cardinal_col_direction);

 //       //CollisionTools::resolve_object_collision(&this->_rectangle,
 //       //    other->get_shape(), Vector2F(cardinal_col_direction.x, 0.0f));
 //       
 //       if (amount.abs_x_greater_than_y())
 //       {
 //           CollisionTools::resolve_object_collision(&this->_rectangle,
 //               other->get_shape(), Vector2F(0.0f, cardinal_col_direction.y));
 //           this->on_ceiling_collision();
 //       }
 //       else
 //       {
	//		CollisionTools::resolve_object_collision(&this->_rectangle,
	//			other->get_shape(), Vector2F(cardinal_col_direction.x, 0.0f));
	//		this->on_wall_collision();
 //       }
	//}
	//// down collision
	//else
 //   if (cardinal_col_direction == Vector2F::DIRECTION_DOWN_LEFT ||
	//	cardinal_col_direction == Vector2F::DIRECTION_DOWN_RIGHT ||
	//	cardinal_col_direction == Vector2F::DIRECTION_DOWN)
 //   {
 //       Vector2F amount = CollisionTools::calculate_object_collision_depth(
 //           this->get_shape(), other->get_shape(), cardinal_col_direction);

	//	if (amount.abs_x_greater_than_y())
	//	{
	//		CollisionTools::resolve_object_collision(&this->_rectangle,
	//			other->get_shape(), Vector2F(0.0f, cardinal_col_direction.y));
	//		this->on_ground_collision();
	//	}
	//	else
	//	{
	//		CollisionTools::resolve_object_collision(&this->_rectangle,
	//			other->get_shape(), Vector2F(cardinal_col_direction.x, 0.0f));
	//		this->on_wall_collision();
	//	}
 //   }
	//else
	//{
	//	throw std::exception("Invalid collision direction.");
	//}

	// check if the player is not moving in the same direction as the collision


    Vector2F direction = CollisionTools::calculate_object_collision_direction_by_edge(
    	this->get_shape(), other->get_shape());

    if (direction == Vector2F::DIRECTION_UP)
    {
		this->on_top_collision(other);
	}
	else if (direction == Vector2F::DIRECTION_DOWN)
	{
		this->on_bottom_collision(other);
    }
	else if (direction == Vector2F::DIRECTION_LEFT)
	{
		this->on_left_collision(other);
    }
	else if (direction == Vector2F::DIRECTION_RIGHT)
	{
		this->on_right_collision(other);
	}
	else if (direction == Vector2F::DIRECTION_UP_LEFT)
	{
		this->on_top_left_collision(other);
	}
	else if (direction == Vector2F::DIRECTION_UP_RIGHT)
	{
		this->on_top_right_collision(other);
	}
	else if (direction == Vector2F::DIRECTION_DOWN_LEFT)
	{
		this->on_bottom_left_collision(other);
	}
	else if (direction == Vector2F::DIRECTION_DOWN_RIGHT)
	{
		this->on_bottom_right_collision(other);
	}
	else
	{
		throw std::exception("Invalid collision direction.");   
	}
}

//void Player::on_ground_collision()
//{
//    MovingObject::set_velocity_y(0.0f);
//    this->set_move_state(player_move_state::ON_GROUND);
//}
//void Player::on_ceiling_collision()
//{
//	MovingObject::set_velocity_y(0.0f);
//	this->set_move_state(player_move_state::ON_CEILING);
//}
//void Player::on_wall_collision()
//{
//	MovingObject::set_velocity_x(0.0f);
//}

void Player::on_top_collision(const ICollisionGameObject* other)
{
    MovingObject::set_velocity_y(0.0f);

    CollisionTools::resolve_object_collision(&this->_rectangle,
        other->get_shape(), Vector2F::DIRECTION_UP);

	this->set_move_state(player_move_state::ON_CEILING);
}
void Player::on_bottom_collision(const ICollisionGameObject* other)
{
    MovingObject::set_velocity_y(0.0f);

    CollisionTools::resolve_object_collision(&this->_rectangle,
        other->get_shape(), Vector2F::DIRECTION_DOWN);

    this->set_move_state(player_move_state::ON_GROUND);
}
void Player::on_left_collision(const ICollisionGameObject* other)
{
    this->set_velocity_x(0.0f);

    CollisionTools::resolve_object_collision(&this->_rectangle,
        other->get_shape(), Vector2F::DIRECTION_LEFT);
}
void Player::on_right_collision(const ICollisionGameObject* other)
{
    this->set_velocity_x(0.0f);

    CollisionTools::resolve_object_collision(&this->_rectangle,
        other->get_shape(), Vector2F::DIRECTION_RIGHT);
}
void Player::on_top_left_collision(const ICollisionGameObject* other)
{
    Vector2F amount = CollisionTools::calculate_object_collision_depth(
        this->get_shape(), other->get_shape(), Vector2F::DIRECTION_UP_LEFT);

    if (amount.abs_x_greater_than_y())
    {
        this->on_top_collision(other);
    }
    else
    {
        this->on_left_collision(other);
    }
}
void Player::on_top_right_collision(const ICollisionGameObject* other)
{
	Vector2F amount = CollisionTools::calculate_object_collision_depth(
		this->get_shape(), other->get_shape(), Vector2F::DIRECTION_UP_RIGHT);

    if (amount.abs_x_greater_than_y())
    {
        this->on_top_collision(other);
    }
    else
    {
        this->on_right_collision(other);
    }
}
void Player::on_bottom_left_collision(const ICollisionGameObject* other)
{
    direction dir = this->get_velocity().get_direction();
    bool moving_up = dir == direction::UP || dir == direction::UP_LEFT ||
		dir == direction::UP_RIGHT;

	Vector2F amount = CollisionTools::calculate_object_collision_depth(
		this->get_shape(), other->get_shape(), Vector2F::DIRECTION_DOWN_LEFT);

    if (amount.abs_x_greater_than_y() && !moving_up)
    {
        this->on_bottom_collision(other);
    }
    else
    {
        this->on_left_collision(other);
    }
}
void Player::on_bottom_right_collision(const ICollisionGameObject* other)
{
    direction dir = this->get_velocity().get_direction();
    bool moving_up = dir == direction::UP || dir == direction::UP_LEFT ||
        dir == direction::UP_RIGHT;

	Vector2F amount = CollisionTools::calculate_object_collision_depth(
		this->get_shape(), other->get_shape(), Vector2F::DIRECTION_DOWN_RIGHT);

    if (amount.abs_x_greater_than_y() && !moving_up)
    {
        this->on_bottom_collision(other);
    }
    else
    {
        this->on_right_collision(other);
    }
}

void Player::update_weapon_position() const
{
    this->_primary->set_player_center(this->get_center());
}
void Player::on_projectile_collision(const ICollisionGameObject* other)
{
    collision_object_type other_type = other->get_collision_object_type();

    if (other_type == collision_object_type::PROJECTILE_SPRAY_TEAM_A ||
        other_type == collision_object_type::PROJECTILE_SPRAY_TEAM_B)
    {
		this->_health -= SPRAY_DAMAGE;
        //this->_health_regen_timer = 0.0f;
	}
	else if (other_type == collision_object_type::PROJECTILE_JET_TEAM_A ||
		other_type == collision_object_type::PROJECTILE_JET_TEAM_B)
	{
		this->_health -= JET_DAMAGE;
        //this->_health_regen_timer = 0.0f;
	}
	else if (other_type == collision_object_type::PROJECTILE_ROLLING_TEAM_A ||
		other_type == collision_object_type::PROJECTILE_ROLLING_TEAM_B)
	{
		this->_health -= ROLLING_DAMAGE;
        //this->_health_regen_timer = 0.0f;
	}
	else if (other_type == collision_object_type::PROJECTILE_BALL_TEAM_A ||
		other_type == collision_object_type::PROJECTILE_BALL_TEAM_B)
	{
		this->_health -= BALL_DAMAGE;
        //this->_health_regen_timer = 0.0f;
	}
	else if (other_type == collision_object_type::PROJECTILE_MIST_TEAM_A ||
		other_type == collision_object_type::PROJECTILE_MIST_TEAM_B)
	{
		this->_health -= MIST_DAMAGE;
        //this->_health_regen_timer = 0.0f;
	}
	else
	{
		throw std::exception("Invalid projectile type.");
    }
    this->_health_regen_timer = 0.0f;

    if (this->_damage_sound_timer >= DAMAGE_SOUND_DELAY)
	{
		this->_sound_bank->play_wave(DAMAGE_SOUND, DAMAGE_SOUND_VOLUME);
		this->_damage_sound_timer = 0.0f;
	}
}

float Player::get_dt() const
{
	return *this->_dt;
}
void Player::update()
{
    if (this->_state == player_state::ALIVE)
    {   
        this->update_movement();

        AnimationObject::update();

        if (this->_health <= 0.0f)
        {
			this->_state = player_state::DEAD;
			this->_sound_bank->play_wave(DEATH_SOUND, DEATH_SOUND_VOLUME);
        }

        this->_damage_sound_timer += this->get_dt();
    }
    else if (this->_state == player_state::DEAD)
    {
        this->_respawn_timer -= this->get_dt();

        if (this->_respawn_timer <= 0.0f)
        {
            this->respawn();
            this->_respawn_timer = RESPAWN_DELAY;
        }
    }
	else
	{
		throw std::exception("Invalid player state.");
	}
    if (this->_input.toggle_debug)
    {
        this->_showing_debug = !this->_showing_debug;
    }

    //ammo regen
    if (this->_health_regen_timer >= HEALTH_REGEN_DELAY)
    {
        this->_health += HEALTH_REGEN_RATE * this->get_dt();
        if (this->_health > 1.0f)
        {
            this->_health = 1.0f;
        }
    }
    this->_health_regen_timer += this->get_dt();
}
std::vector<std::unique_ptr<ICollisionGameObject>>
    Player::update_weapon_and_get_projectiles() const
{
    return this->_primary->update_and_get_projectiles(
        this->get_input(),
        this->get_center(),
        MovingObject::get_velocity(),
        this->get_facing_right());
}
void Player::update_prev_rectangle()
{
	this->_prev_rectangle = this->_rectangle;
}

void Player::update_movement()
{
    const PlayerInputData input = this->_input;
    const float x_input = input.x_movement;
    const player_move_state move_state = this->get_move_state();
    const float dt = this->get_dt();
    const bool analog_stick_down = this->_input.left_analog_stick.y >
        DROP_DOWN_ANALOG_THRESHOLD;
    const bool jump_pressed = this->_input.jump_pressed;

    //If the player's velocity is zero and the user is requesting to move the player
    if (are_equal(MovingObject::get_velocity_x(), 0.0f) && x_input != 0.0f)
    {
        MovingObject::set_velocity_x(X_INITIAL_VELOCITY * x_input);
    }
    //If accelerating in the same direction as currently moving. right
    else if (MovingObject::get_velocity_x() > 0.0f && x_input > 0.0f)
    {
        MovingObject::alter_velocity_x(X_ACCELERATION * dt * x_input);
        if (MovingObject::get_velocity_x() > MAX_VELOCITY.x)
        {
            MovingObject::set_velocity_x(MAX_VELOCITY.x);
        }
    }
    //If accelerating in the same direction as currently moving. left
    else if (MovingObject::get_velocity_x() < 0.0f && x_input < 0.0f)
    {
        MovingObject::alter_velocity_x(X_ACCELERATION * dt * x_input);
        if (MovingObject::get_velocity_x() < -MAX_VELOCITY.x)
        {
            MovingObject::set_velocity_x(-MAX_VELOCITY.x);
        }
    }
    //If accelerating in the opposite direction as currently moving. right
    else if (MovingObject::get_velocity_x() > 0.0f && x_input < 0.0f)
    {
        MovingObject::alter_velocity_x(X_DEACCELERATION * dt * x_input);
        MovingObject::alter_velocity_x(X_ACCELERATION * dt * x_input);
    }
    //If accelerating in the opposite direction as currently moving. left
    else if (MovingObject::get_velocity_x() < 0.0f && x_input > 0.0f)
    {
        MovingObject::alter_velocity_x(X_DEACCELERATION * dt * x_input);
        MovingObject::alter_velocity_x(X_ACCELERATION * dt * x_input);
    }
    //No key pressed deaccelaration right
    else if (MovingObject::get_velocity_x() > 0.0f && are_equal(x_input, 0.0f))
    {
        MovingObject::alter_velocity_x(-X_DEACCELERATION * dt);
        if (MovingObject::get_velocity_x() < 0.0f)
        {
            MovingObject::set_velocity_x(0.0f);
        }
    }
    //No key pressed deaccelaration left
    else if (MovingObject::get_velocity_x() < 0.0f && are_equal(x_input, 0.0f))
    {
        MovingObject::alter_velocity_x(X_DEACCELERATION * dt);
        if (MovingObject::get_velocity_x() > 0.0f)
        {
            MovingObject::set_velocity_x(0.0f);
        }
    }
    //gravity
    if (this->is_on_ramp())
    {
		// increase gravity on ramp
		MovingObject::alter_velocity_y(GRAVITY * RAMP_GRAVITY_MULTIPLIER * dt);
	}
	else
	{
		MovingObject::alter_velocity_y(GRAVITY * dt);
    }
    if (MovingObject::get_velocity_y() > MAX_VELOCITY.y)
    {
        MovingObject::set_velocity_y(MAX_VELOCITY.y);
    }

    // DROPPING_DOWN state only lasts for one frame
    if (move_state == player_move_state::DROPPING_DOWN)
	{
		this->set_move_state(player_move_state::IN_AIR);
	}

    // check if dropping down from a platform
    if (move_state == player_move_state::ON_DROP_DOWN_GROUND && analog_stick_down &&
        !jump_pressed)
    {
        MovingObject::alter_velocity_y(DROP_DOWN_VELOCITY);
        this->set_move_state(player_move_state::DROPPING_DOWN);
    }
	else
	{
        this->do_jump();
	}

    MovingObject::set_dx_x(MovingObject::get_velocity_x() * dt);
    MovingObject::set_dx_y(MovingObject::get_velocity_y() * dt);

    this->_rectangle.offset(MovingObject::get_dx_x(),
        MovingObject::get_dx_y());

    if (x_input > 0.0f)
    {
        this->set_facing_right(true);
    }
    else if (x_input < 0.0f)
    {
        this->set_facing_right(false);
    }
}

void Player::do_jump()
{
    const player_move_state move_state = this->get_move_state();
    const bool jump_pressed = this->_input.jump_pressed;
    const bool jump_held = this->_input.jump_held;
    const float dt = this->get_dt();
   
    if (this->is_on_ground() && jump_pressed)
    {
		MovingObject::set_velocity_y(JUMP_LAUNCH_VELOCITY);
		this->set_air_time(0.0f);
		this->set_move_state(player_move_state::JUMPING);
		this->_sound_bank->play_wave(JUMP_SOUND, JUMP_SOUND_VOLUME);
	}
	else if (move_state == player_move_state::ON_CEILING)
	{
		// do nothing
	}
	else if (move_state == player_move_state::JUMPING)
	{
		if (jump_held)
		{
			if (this->get_air_time() <= JUMP_MAX_TIME)
			{
				MovingObject::alter_velocity_y(JUMP_ACCELERATION * dt);
			}
			else
			{
				this->set_move_state(player_move_state::IN_AIR);
			}
		}
		else // !jump held
		{
			this->set_move_state(player_move_state::IN_AIR);
		}
		this->alter_air_time(dt);
	}
	else if (move_state == player_move_state::IN_AIR)
	{
		// do nothing
	}

    if (this->get_velocity_y() < -MAX_VELOCITY.y)
    {
        this->set_velocity_y(-MAX_VELOCITY.y);
    }
}

bool Player::is_visible_in_viewport(const RectangleF& view) const
{
    RectangleF player_and_weapon_rect = this->_rectangle;
    player_and_weapon_rect.inflate(Vector2F(200.0f, 200.0f));
    return player_and_weapon_rect.intersects(view);
}
void Player::set_player_input(const PlayerInputData& input)
{
	this->_input = input;
}

const RectangleF& Player::get_rectangle() const
{
	return this->_rectangle;
}
Vector2F Player::get_center() const
{
	return this->_rectangle.get_center();
}
const Vector2F& Player::get_velocity() const
{
    return MovingObject::get_velocity();
}
const Camera& Player::get_camera() const
{
	return this->_camera;
}
const Viewport& Player::get_viewport() const
{
	return this->_viewport;
}
float Player::get_input_x_movement() const
{
	return this->_input.x_movement;
}
const Vector2F& Player::get_input_shoot_direction() const
{
	return this->_input.shoot_direction;
}
bool Player::get_input_primary_shoot() const
{
	return this->_input.primary_shoot;
}
bool Player::get_input_jump_pressed() const
{
	return this->_input.jump_pressed;
}
bool Player::get_input_jump_held() const
{
	return this->_input.jump_held;
}
player_move_state Player::get_move_state() const
{
	return this->_move_state;
}
bool Player::get_showing_debug() const
{
	return this->_showing_debug;
}
const PlayerAnimationInfo& Player::get_animation_info(player_animation_state state)
{
    switch (state)
    {
    case player_animation_state::IDLE:
        return ANIMATION_INFO_IDLE;
    case player_animation_state::WALKING:
        return ANIMATION_INFO_WALK;
    case player_animation_state::RUNNING:
        return ANIMATION_INFO_RUNNING;
    case player_animation_state::JUMPING:
        return ANIMATION_INFO_JUMPING;
    case player_animation_state::FALLING:
        return ANIMATION_INFO_FALLING;
    default:
        throw std::exception("Invalid player animation state.");
    }
}
void Player::respawn()
{
    this->_rectangle.set_position(this->_respawn_position);
    MovingObject::set_rotation(0.0f);
    MovingObject::set_velocity(Vector2F::ZERO);
    MovingObject::set_dx(Vector2F::ZERO);
	this->_health = 1.0f;
	this->_primary->reset_ammo();
	this->_state = player_state::ALIVE;
    this->_sound_bank->play_wave(RESPAWN_SOUND, RESPAWN_SOUND_VOLUME);
}
player_animation_state Player::calculate_animation_state() const
{
    player_move_state move_state = this->get_move_state();
    if (this->is_on_ground())
    {
        float velocity_x = this->get_velocity_x();
        if (velocity_x == 0.0f)
        {
			return player_animation_state::IDLE;
		}
        else if (std::fabs(velocity_x) > 600.0f)
        {
			return player_animation_state::RUNNING;
		}
        else
        {
			return player_animation_state::WALKING;
		}
	}
    else if (move_state == player_move_state::ON_CEILING)
    {
		return player_animation_state::IDLE;
	}
    else if (move_state == player_move_state::JUMPING)
    {
		return player_animation_state::JUMPING;
	}
    else if (move_state == player_move_state::IN_AIR ||
		move_state == player_move_state::DROPPING_DOWN)
    {
        if (this->get_velocity_y() > 0.0f)
        {
			return player_animation_state::FALLING;
		}
        else
        {
			return player_animation_state::JUMPING;
		}
	}
    else
    {
		throw std::exception("Invalid player move state.");
	}
}
void Player::stop_sounds() const
{
    this->_primary->stop_sounds();
}
void Player::set_move_state(player_move_state state)
{
	this->_move_state = state;
}

void Player::set_air_time(float time)
{
	this->_air_time = time;
}

void Player::alter_air_time(float time)
{
	this->_air_time += time;
}

void Player::set_facing_right(bool facing_right)
{
	this->_facing_right = facing_right;
}

bool Player::get_facing_right() const
{
	return this->_facing_right;
}

int Player::get_player_num() const
{
	return this->_player_num;
}

float Player::get_health() const
{
	return this->_health;
}

void Player::set_health(float health)
{
	this->_health = health;
}

void Player::alter_health(float change)
{
	this->_health += change;
}

void Player::set_respawn_timer(float respawn_timer)
{
	this->_respawn_timer = respawn_timer;
}

void Player::alter_respawn_timer(float change)
{
	this->_respawn_timer += change;
}

void Player::set_score(int score)
{
	this->_score = score;
}

void Player::alter_score(int change)
{
	this->_score += change;
}

int Player::get_score() const
{
	return this->_score;
}

void Player::set_team(player_team team)
{
	this->_team = team;
}

void Player::set_team_colour(const Colour& team_colour)
{
	this->_team_colour = team_colour;
}

void Player::set_viewport(const Viewport& viewport)
{
	this->_viewport = viewport;
}

void Player::set_input(const PlayerInputData& input)
{
	this->_input = input;
}

wep_type Player::get_primary() const
{
	return this->_primary_type;
}

void Player::set_primary(wep_type primary)
{
	this->_primary_type = primary;
}

wep_type Player::get_secondary() const
{
	return this->_secondary_type;
}

void Player::set_secondary(wep_type secondary)
{
	this->_secondary_type = secondary;
}

void Player::set_showing_debug(bool showing_debug)
{
	this->_showing_debug = showing_debug;
}

void Player::set_player_num(int player_num)
{
	this->_player_num = player_num;
}

void Player::set_camera(const Camera& camera)
{
	this->_camera = camera;
}

float Player::get_weapon_ammo() const
{
	return this->_primary->get_ammo();
}

const Colour& Player::get_team_colour() const
{
	return this->_team_colour;
}

player_state Player::get_state() const
{
	return this->_state;
}
void Player::set_state(player_state state)
{
	this->_state = state;
}

player_team Player::get_team() const
{
	return this->_team;
}

float Player::get_respawn_timer() const
{
	return this->_respawn_timer;
}

float Player::get_air_time() const
{
	return this->_air_time;
}

const PlayerInputData& Player::get_input() const
{
	return this->_input;
}

std::string Player::get_player_move_state_string() const
{
    switch (this->_move_state)
    {
    case player_move_state::ON_GROUND:
        return "on_ground";
    case player_move_state::ON_DROP_DOWN_GROUND:
        return "on_drop_down_ground";
    case player_move_state::ON_CEILING:
        return "on_ceiling";
	case player_move_state::ON_RAMP_LEFT:
		return "on_ramp_left";
	case player_move_state::ON_RAMP_RIGHT:
		return "on_ramp_right";
    case player_move_state::IN_AIR:
        return "in_air";
    case player_move_state::JUMPING:
        return "jumping";
    };
	return "invalid";
}

bool Player::is_on_ground() const
{
	return this->_move_state == player_move_state::ON_GROUND ||
		this->_move_state == player_move_state::ON_DROP_DOWN_GROUND ||
		this->_move_state == player_move_state::ON_RAMP_LEFT ||
		this->_move_state == player_move_state::ON_RAMP_RIGHT;
}

bool Player::is_on_ramp() const
{
	return this->_move_state == player_move_state::ON_RAMP_LEFT ||
		this->_move_state == player_move_state::ON_RAMP_RIGHT;
}

void Player::on_no_collision()
{
	player_move_state move_state = this->get_move_state();

	if (move_state == player_move_state::ON_GROUND ||
		move_state == player_move_state::ON_DROP_DOWN_GROUND ||
		move_state == player_move_state::ON_RAMP_LEFT ||
		move_state == player_move_state::ON_RAMP_RIGHT)
	{
		this->set_move_state(player_move_state::IN_AIR);
	}
}