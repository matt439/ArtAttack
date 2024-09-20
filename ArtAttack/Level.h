#ifndef LEVEL_H
#define LEVEL_H

#include "CameraTools.h"
#include "DebugText.h"
#include "ICollisionGameObject.h"
#include "level_stage.h"
#include "Player.h"
#include "PlayerInput.h"
#include "ResolutionManager.h"
#include "SoundBank.h"
#include "TeamColour.h"
#include "TextDropShadow.h"
#include "ViewportManager.h"
#include "ThreadPool.h"
#include "Partitioner.h"
#include <mutex>

class Level final
{
public:
	Level() = default;
	Level(std::unique_ptr<std::vector<std::unique_ptr<IGameObject>>> non_collision_objects,
		std::unique_ptr<std::vector<std::unique_ptr<ICollisionGameObject>>> collision_objects,
		std::unique_ptr<std::vector<std::unique_ptr<Player>>> player_objects,
		std::unique_ptr<std::vector<std::unique_ptr<IGameObject>>> viewport_dividers,
		level_stage stage,
		const team_colour& team_colours,
		const MattMath::RectangleF& out_of_bounds,
		const MattMath::RectangleF& camera_bounds,
		const std::vector<MattMath::Vector2F>& team_a_spawns,
		const std::vector<MattMath::Vector2F>& team_b_spawns,
		const std::string& sound_bank_name,
		const std::string& music_name,
		float music_volume,
		const float* dt,
		DirectX::SpriteBatch* sprite_batch,
		ID3D11SamplerState* sampler_state,
		const std::string& level_name,
		const ResolutionManager* resolution_manager,
		ViewportManager* viewport_manager,
		ResourceManager* resource_manager,
		ThreadPool* thread_pool);

	void update(const std::vector<player_input>& player_inputs);
	void draw() const;
	void stop_music() const;

private:
	std::unique_ptr<std::vector<std::unique_ptr<IGameObject>>>
		_non_collision_objects = nullptr;

	std::unique_ptr<std::vector<std::unique_ptr<ICollisionGameObject>>>
		_collision_objects = nullptr;

	std::unique_ptr<std::vector<std::unique_ptr<Player>>>
		_player_objects = nullptr;

	std::unique_ptr<std::vector<std::unique_ptr<IGameObject>>>
		_viewport_dividers = nullptr;

	SoundBank* _sound_bank = nullptr;

	ThreadPool* _thread_pool = nullptr;

	std::string _music_name = "";
	float _music_volume = 0.0f;

	std::unique_ptr<TextDropShadow> _countdown_text = nullptr;

	std::unique_ptr<CameraTools> _camera_tools = nullptr;

	std::string _level_name = "";
	const ResolutionManager* _resolution_manager = nullptr;
	ViewportManager* _viewport_manager = nullptr;
	ResourceManager* _resource_manager = nullptr;

	bool _first_update = true;

	team_colour _team_colours = team_colour();
	level_stage _stage = level_stage::KING_OF_THE_HILL;

	MattMath::RectangleF _out_of_bounds = MattMath::RectangleF::ZERO;
	MattMath::RectangleF _camera_bounds = MattMath::RectangleF::ZERO;

	std::vector<MattMath::Vector2F> _team_a_spawns;
	std::vector<MattMath::Vector2F> _team_b_spawns;

	const float* _dt = nullptr;
	DirectX::SpriteBatch* _sprite_batch = nullptr;
	ID3D11SamplerState* _sampler_state = nullptr;

	std::vector<player_input> _player_inputs;
	std::unique_ptr<DebugText> _debug_text = nullptr;

	int count_projectiles() const;
	float get_dt() const;
	bool is_object_out_of_bounds(const ICollisionGameObject* object) const;

	void update_level_logic(const std::vector<player_input>& player_inputs) const;

	void draw_active_level() const;

	void stop_player_sounds() const;

	void update_collision_objects(int start, int end) const;
	void update_player_objects(int start, int end,
		const std::vector<player_input>& player_inputs) const;

	void update_weapon_objects(int start, int end,
		std::vector<std::unique_ptr<ICollisionGameObject>>& new_projs) const;

	void update_non_collision_objects(int start, int end) const;
	void check_out_of_bounds_players(int start, int end) const;
	void check_out_of_bounds_objects(int start, int end) const;
	void check_player_collisions(int start, int end) const;
	void check_collision_object_collisions(int start, int end) const;
};

#endif
