#ifndef PAINTTILE_H
#define PAINTTILE_H

#include "player_team.h"
#include "TextureObject.h"
#include "TeamColour.h"
#include "ICollisionGameObject.h"
//#include "VisualAnimation.h"
#include "AnimationObject.h"
//#include "SoundBank.h"

namespace paint_tile_consts
{
	constexpr float WIDTH = 4.0f;
	constexpr float HEIGHT = 4.0f;
	constexpr float THICKNESS = 12.0f;
	//constexpr float SPLASH_DURATION = 0.5f;
	const static std::string SHEET_NAME = "sprite_sheet_1";
	const static std::string FRAME_NAME = "pixel";

	const static std::string SPLASH_SPRITE_SHEET_NAME = "sprite_sheet_1";
	const static std::string SPLASH_ANIMATION_STRIP_NAME = "splash_1";
	const static MattMath::RectangleF SPLASH_RECTANGLE = { 0.0f, 0.0f, THICKNESS * 2.0f, THICKNESS * 2.0f };

	//const std::string SOUND_BANK_NAME = "sound_bank_1";
	//const std::string SOUND_NAME = "WaterSplashing";
	//constexpr float SOUND_VOLUME = 0.05f;
}

class PaintTileSplash : public AnimationObject, public IGameObject
{
public:
	PaintTileSplash() = default;
	PaintTileSplash(const float* dt,
		const MattMath::RectangleF& rectangle,
		const std::string& sheet_name,
		const std::string& animation_strip_name,
		DirectX::SpriteBatch* sprite_batch,
		ResourceManager* resource_manager,
		const MattMath::Colour& color = colour_consts::WHITE,
		float rotation = 0.0f,
		const MattMath::Vector2F& origin = MattMath::Vector2F::ZERO,
		DirectX::SpriteEffects effects = DirectX::SpriteEffects_None,
		float layer_depth = 0.0f) :
		AnimationObject(dt, sheet_name, animation_strip_name,
			sprite_batch, resource_manager,
			color, rotation, origin, effects, layer_depth),
		_rectangle(rectangle){}

	void set_rectangle_center(const MattMath::Vector2F& center);
	void reset_and_play();
	void set_colour(const MattMath::Colour& colour);

	void update() override;
	void draw(const MattMath::Camera& camera) override;
	void draw() override;
	bool is_visible_in_viewport(const MattMath::RectangleF& view) const override;
private:
	MattMath::RectangleF _rectangle = MattMath::RectangleF::ZERO;
};


class PaintTile : public TextureObject, public ICollisionGameObject
{
public:
	PaintTile() = default;
	PaintTile(const MattMath::RectangleF& rectangle,
		const std::string& sheet_name,
		const std::string& frame_name,
		DirectX::SpriteBatch* sprite_batch,
		ResourceManager* resource_manager,
		const team_colour& team_colours,
		const float* dt,
		const MattMath::Colour& color = colour_consts::WHITE,
		float rotation = 0.0f,
		const MattMath::Vector2F& origin = MattMath::Vector2F::ZERO,
		DirectX::SpriteEffects effects = DirectX::SpriteEffects_None,
		float layer_depth = 0.0f);
	void draw(const MattMath::Camera& camera) override;
	void draw() override;
	void update() override;
	float get_area() const;
	player_team get_team() const;
	//void set_team(player_team team);
	//const MattMath::RectangleF& get_rectangle() const;
	bool is_colliding(const ICollisionGameObject* other) const override;
	const MattMath::Shape* get_shape() const override;

	void on_collision(const ICollisionGameObject* other) override;
	collision_object_type get_collision_object_type() const override;
	bool get_for_deletion() const override;
	bool is_visible_in_viewport(const MattMath::RectangleF& view) const override;
	//void play_splash_sound();
private:
	MattMath::RectangleF _rectangle = MattMath::RectangleF::ZERO;
	player_team _team = player_team::NONE;
	team_colour _team_colours = team_colour();
	const float* _dt = nullptr;
	//float _splash_timer = 0.0f;
	PaintTileSplash _splash;
	//SoundBank* _sound_bank = nullptr;
};

#endif // !PAINTTILE_H
