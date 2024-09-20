#include "pch.h"
#include "level.h"

using namespace MattMath;
using namespace DirectX;

Level::Level(std::unique_ptr<std::vector<std::unique_ptr<IGameObject>>> non_collision_objects,
	std::unique_ptr<std::vector<std::unique_ptr<ICollisionGameObject>>> collision_objects,
	std::unique_ptr<std::vector<std::unique_ptr<Player>>> player_objects,
	std::unique_ptr<std::vector<std::unique_ptr<IGameObject>>> viewport_dividers,
	level_stage stage,
	const team_colour& team_colours,
	const RectangleF& out_of_bounds,
	const RectangleF& camera_bounds,
	const std::vector<Vector2F>& team_a_spawns,
	const std::vector<Vector2F>& team_b_spawns,
	const std::string& sound_bank_name,
	const std::string& music_name,
	float music_volume,
	const float* dt,
	//SpriteBatch* sprite_batch,
	ID3D11SamplerState* sampler_state,
	const std::string& level_name,
	const ResolutionManager* resolution_manager,
	ViewportManager* viewport_manager,
	ResourceManager* resource_manager,
	ThreadPool* thread_pool) :
	_non_collision_objects(std::move(non_collision_objects)),
	_collision_objects(std::move(collision_objects)),
	_player_objects(std::move(player_objects)),
	_viewport_dividers(std::move(viewport_dividers)),
	_music_name(music_name),
	_music_volume(music_volume),
	_level_name(level_name),
	_resolution_manager(resolution_manager),
	_viewport_manager(viewport_manager),
	_resource_manager(resource_manager),
	_team_colours(team_colours),
	_stage(stage),
	_out_of_bounds(out_of_bounds),
	_camera_bounds(camera_bounds),
	_team_a_spawns(team_a_spawns),
	_team_b_spawns(team_b_spawns),
	_dt(dt),
	//_sprite_batch(sprite_batch),
	_sampler_state(sampler_state),
	_thread_pool(thread_pool)
{
	this->_debug_text = std::make_unique<DebugText>(
		resource_manager, dt, resolution_manager);
	this->_camera_tools = std::make_unique<CameraTools>();
	this->_sound_bank = resource_manager->get_sound_bank(sound_bank_name);
}
void Level::stop_music() const
{
	this->_sound_bank->stop_effect(this->_music_name, true);
}
void Level::update(const std::vector<player_input>& player_inputs)
{
	if (this->_first_update)
	{
		//this->_sound_bank->play_effect(this->_music_name, true, this->_music_volume);
			
		// update player cameras
		int player_index = 0;
		for (auto& object : *this->_player_objects)
		{
			Camera camera = this->_camera_tools->calculate_camera(
				object->get_center(),
				this->_viewport_manager->get_player_viewport(player_index).get_size(),
				object->get_camera(),
				this->_camera_bounds);
			object->set_camera(camera);
			player_index++;
		}
		this->_first_update = false;
	}

	this->update_level_logic(player_inputs);
}
void Level::update_collision_objects(int start, int end) const
{
	for (int i = start; i < end; i++)
	{
		this->_collision_objects->at(i)->update();
	}
}

void Level::update_player_objects(int start, int end,
	const std::vector<player_input>& player_inputs) const
{
	for (int i = start; i < end; i++)
	{
		this->_player_objects->at(i)->set_player_input(player_inputs[i]);
		this->_player_objects->at(i)->update();

		// update player camera
		Camera camera = this->_camera_tools->calculate_camera(
			this->_player_objects->at(i)->get_center(),
			this->_viewport_manager->get_player_viewport(i).get_size(),
			this->_player_objects->at(i)->get_camera(),
			this->_camera_bounds);
		this->_player_objects->at(i)->set_camera(camera);

		//// update player weapon
		//auto new_projs = this->_player_objects->at(i)->update_weapon_and_get_projectiles();

		//// add new projectiles to collision objects
		//for (auto& proj : new_projs)
		//{
		//	this->_collision_objects->push_back(std::move(proj));
		//}
	}
}

void Level::update_weapon_objects(int start, int end,
	std::vector<std::unique_ptr<ICollisionGameObject>>& new_projs) const
{
	for (int i = start; i < end; i++)
	{
		// update player weapon
		auto projs = this->_player_objects->at(i)->update_weapon_and_get_projectiles();

		// add new projectiles to collision objects
		for (auto& proj : projs)
		{
			new_projs.push_back(std::move(proj));
		}
	}
}

void Level::update_non_collision_objects(int start, int end) const
{
	for (int i = start; i < end; i++)
	{
		this->_non_collision_objects->at(i)->update();
	}
}

void Level::check_out_of_bounds_players(int start, int end) const
{
	for (int i = start; i < end; i++)
	{
		if (this->is_object_out_of_bounds(this->_player_objects->at(i).get()))
		{
			throw std::exception("Player out of bounds");
		}
	}
}

void Level::check_out_of_bounds_objects(int start, int end) const
{
	for (int i = start; i < end; i++)
	{
		if (this->is_object_out_of_bounds(this->_collision_objects->at(i).get()))
		{
			throw std::exception("Collision object out of bounds");
		}
	}
}

void Level::check_player_collisions(int start, int end) const
{
	for (int i = start; i < end; i++)
	{
		for (int j = 0; j < this->_collision_objects->size(); j++)
		{
			std::scoped_lock lock(this->_collision_objects->at(j)->get_mutex());
			
			if (this->_collision_objects->at(j)->get_for_deletion())
			{
				continue;
			}
			
			if (this->_player_objects->at(i)->is_colliding(this->_collision_objects->at(j).get()))
			{
				this->_player_objects->at(i)->on_collision(this->_collision_objects->at(j).get());
				this->_collision_objects->at(j)->on_collision(this->_player_objects->at(i).get());
			}
		}
		this->_player_objects->at(i)->update_weapon_position();
		this->_player_objects->at(i)->update_prev_rectangle();
	}
}

void Level::check_collision_object_collisions(int start, int end) const
{
	for (int i = start; i < end; i++)
	{
		// check collision object collisions with players
		for (int j = 0; j < this->_player_objects->size(); j++)
		{
			std::scoped_lock lock(this->_player_objects->at(j)->get_mutex());

			if (this->_collision_objects->at(i)->get_for_deletion() ||
				this->_player_objects->at(j)->get_for_deletion())
			{
				continue;
			}
			if (this->_collision_objects->at(i)->is_colliding(this->_player_objects->at(j).get()))
			{
				this->_collision_objects->at(i)->on_collision(this->_player_objects->at(j).get());
				this->_player_objects->at(j)->on_collision(this->_collision_objects->at(i).get());
			}
		}

		// check collision object collisions with other collision objects
		for (int j = 0; j < this->_collision_objects->size(); j++)
		{
			std::scoped_lock lock(this->_collision_objects->at(j)->get_mutex());

			if (i == j)
			{
				continue;
			}
			if (this->_collision_objects->at(i)->get_for_deletion() ||
				this->_collision_objects->at(j)->get_for_deletion())
			{
				continue;
			}
			if (this->_collision_objects->at(i)->is_colliding(this->_collision_objects->at(j).get()))
			{
				this->_collision_objects->at(i)->on_collision(this->_collision_objects->at(j).get());
				this->_collision_objects->at(j)->on_collision(this->_collision_objects->at(i).get());
			}
		}
	}
	
	//for (auto& object : *this->_collision_objects)
	//{
	//	// check collision object collisions with players
	//	for (auto& player : *this->_player_objects)
	//	{
	//		if (object->get_for_deletion() || player->get_for_deletion())
	//		{
	//			continue;
	//		}
	//		if (object->is_colliding(player.get()))
	//		{
	//			object->on_collision(player.get());
	//			player->on_collision(object.get());
	//		}
	//	}

	//	// check collision object collisions with other collision objects
	//	for (auto& object_2 : *this->_collision_objects)
	//	{
	//		if (object->get_for_deletion() || object_2->get_for_deletion())
	//		{
	//			continue;
	//		}
	//		if (object == object_2)
	//		{
	//			continue;
	//		}
	//		if (object->is_colliding(object_2.get()))
	//		{
	//			object->on_collision(object_2.get());
	//			object_2->on_collision(object.get());
	//		}
	//	}
	//}
}

void Level::update_level_logic(const std::vector<player_input>& player_inputs) const
{
	int num_threads = this->_thread_pool->get_max_num_threads();
	
	// partition non-collision objects
	auto partioned_non_coll_objs =
		Partitioner::partition(this->_non_collision_objects->size(), num_threads);

	// update non-collision objects
	for (int i = 0; i < partioned_non_coll_objs.size(); i++)
	{
		this->_thread_pool->add_task([this, i, partioned_non_coll_objs]()
			{
				this->update_non_collision_objects(partioned_non_coll_objs[i].first,
				partioned_non_coll_objs[i].second);
			});
	}

	// partition collision objects
	auto partitioned_coll_objs =
		Partitioner::partition(this->_collision_objects->size(), num_threads);

	// update collision objects
 	for (int i = 0; i < partitioned_coll_objs.size(); i++)
	{
		this->_thread_pool->add_task([this, i, partitioned_coll_objs]()
			{
				this->update_collision_objects(partitioned_coll_objs[i].first,
					partitioned_coll_objs[i].second);
			});
	}

	// partition player objects
	auto partitioned_players =
		Partitioner::partition(this->_player_objects->size(), num_threads);

	// update player objects
	for (int i = 0; i < partitioned_players.size(); i++)
	{
		this->_thread_pool->add_task([this, i, partitioned_players, player_inputs]()
			{
				this->update_player_objects(partitioned_players[i].first,
					partitioned_players[i].second, player_inputs);
			});
	}

	// create vector to hold new projectiles
	std::vector<std::vector<std::unique_ptr<ICollisionGameObject>>>
		new_projs(partitioned_players.size());

	// update weapon objects
	for (int i = 0; i < partitioned_players.size(); i++)
	{
		this->_thread_pool->add_task([this, i, partitioned_players, &new_projs]()
			{
				this->update_weapon_objects(partitioned_players[i].first,
				partitioned_players[i].second, new_projs[i]);
			});
	}

	this->_thread_pool->wait_for_tasks_to_complete();

	// add new projectiles to collision objects
	for (auto& proj_vec : new_projs)
	{
		for (auto& proj : proj_vec)
		{
			this->_collision_objects->push_back(std::move(proj));
		}
	}

	// check player collisions
	for (int i = 0; i < partitioned_players.size(); i++)
	{
		this->_thread_pool->add_task([this, i, partitioned_players]()
			{
				this->check_player_collisions(partitioned_players[i].first,
					partitioned_players[i].second);
			});
	}

	//this->_thread_pool->wait_for_tasks_to_complete();

	// check collision objects collisions
	for (int i = 0; i < partitioned_coll_objs.size(); i++)
	{
		this->_thread_pool->add_task([this, i, partitioned_coll_objs]()
			{
				this->check_collision_object_collisions(partitioned_coll_objs[i].first,
					partitioned_coll_objs[i].second);
			});
	}

	this->_thread_pool->wait_for_tasks_to_complete();

	// check for deletable objects
	for (size_t i = 0; i < this->_collision_objects->size(); i++)
	{
		if (this->_collision_objects->at(i)->get_for_deletion())
		{
			this->_collision_objects->at(i) = std::move(
				this->_collision_objects->back());
			this->_collision_objects->pop_back();
			i--;
		}
	}

	// check for out of bounds players
	for (int i = 0; i < partitioned_players.size(); i++)
	{
		this->_thread_pool->add_task([this, i, partitioned_players]()
			{
				this->check_out_of_bounds_players(partitioned_players[i].first,
				partitioned_players[i].second);
			});
	}

	// partition collision objects
	auto partitioned_coll_objs_2 =
		Partitioner::partition(this->_collision_objects->size(), num_threads);

	// check for out of bounds objects
	for (int i = 0; i < partitioned_coll_objs_2.size(); i++)
	{
		this->_thread_pool->add_task([this, i, partitioned_coll_objs_2]()
			{
				this->check_out_of_bounds_objects(partitioned_coll_objs_2[i].first,
				partitioned_coll_objs_2[i].second);
			});
	}

	this->_thread_pool->wait_for_tasks_to_complete();
}
void Level::stop_player_sounds() const
{
	for (auto& player : *this->_player_objects)
	{
		player->stop_sounds();
	}

}
void Level::draw(std::vector<SpriteBatch*>* sprite_batches) const
{		
	this->draw_active_level(sprite_batches);
}
void Level::draw_active_level(std::vector<SpriteBatch*>* sprite_batches) const
{
	for (auto& player : *this->_player_objects)
	{
		const int player_num = player->get_player_num();

		// apply player viewport
		this->_viewport_manager->apply_player_viewport(
			player_num);

		const Camera& camera = player->get_camera();
		const RectangleF camera_view =
			this->_viewport_manager->get_camera_adjusted_player_viewport_rect(
				player_num, camera);

		sprite_batches->at(0)->Begin(SpriteSortMode_Deferred, nullptr, this->_sampler_state);

		// draw non-collision objects
		for (auto& object : *this->_non_collision_objects)
		{
			if (object->is_visible_in_viewport(camera_view))
			{
				object->draw(sprite_batches->at(0), camera);
			}
		}
		// draw collision objects
		for (auto& object : *this->_collision_objects)
		{
			if (object->is_visible_in_viewport(camera_view))
			{
				object->draw(sprite_batches->at(0), camera);
			}
		}
		// draw player objects
		for (auto& object : *this->_player_objects)
		{
			if (object->is_visible_in_viewport(camera_view))
			{
				object->draw(sprite_batches->at(0), camera);
			}
		}

		// draw viewport dividers
		const Viewport player_vp =
			this->_viewport_manager->get_player_viewport(player_num);
		const Camera viewport_camera = Camera(player_vp);
		for (auto& divider : *this->_viewport_dividers)
		{
			divider->draw(sprite_batches->at(0), viewport_camera);
		}

		sprite_batches->at(0)->End();

		// draw debug info
		//if (player->get_showing_debug())
		if (true)
		{
			int num_projectiles = this->count_projectiles();
			this->_debug_text->draw_debug_info(sprite_batches->at(0), player.get(), num_projectiles);
		}
	}
}


int Level::count_projectiles() const
{
	int count = 0;
	for (auto& object : *this->_collision_objects)
	{
		collision_object_type type = object->get_collision_object_type();

		bool is_projectile =
			type == collision_object_type::PROJECTILE_SPRAY_TEAM_A ||
			type == collision_object_type::PROJECTILE_SPRAY_TEAM_B ||
			type == collision_object_type::PROJECTILE_JET_TEAM_A ||
			type == collision_object_type::PROJECTILE_JET_TEAM_B ||
			type == collision_object_type::PROJECTILE_ROLLING_TEAM_A ||
			type == collision_object_type::PROJECTILE_ROLLING_TEAM_B ||
			type == collision_object_type::PROJECTILE_BALL_TEAM_A ||
			type == collision_object_type::PROJECTILE_BALL_TEAM_B ||
			type == collision_object_type::PROJECTILE_MIST_TEAM_A ||
			type == collision_object_type::PROJECTILE_MIST_TEAM_B;
		if (is_projectile)
		{
			count++;
		}
	}
	return count;
}

float Level::get_dt() const
{
	return *this->_dt;
}

bool Level::is_object_out_of_bounds(const ICollisionGameObject* object) const
{
	bool object_in_bounds =
		this->_out_of_bounds.intersects(object->get_shape()->get_bounding_box());
	return !object_in_bounds;
}
