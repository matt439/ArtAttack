#ifndef LEVELBUILDER_H
#define LEVELBUILDER_H

#include "Level.h"
#include "MenuLevelSettings.h"
#include "TeamColour.h"
#include "PlayerBuilder.h"
#include "ResolutionManager.h"
#include "ResourceManager.h"
#include "LevelObjectBuilder.h"
#include "rapidjson/document.h"
#include "ViewportManager.h"
#include "ThreadPool.h"

class LevelBuilder
{
private:
	std::unique_ptr<TeamColour> _team_colour = nullptr;
	std::unique_ptr<PlayerBuilder> _player_builder = nullptr;
	ResourceManager* _resource_manager = nullptr;
	DirectX::SpriteBatch* _sprite_batch = nullptr;
	const float* _dt = nullptr;
	ViewportManager* _viewport_manager = nullptr;
	std::unique_ptr<LevelObjectBuilder> _level_object_builder = nullptr;
	ID3D11SamplerState* _sampler_state = nullptr;
	ResolutionManager* _resolution_manager = nullptr;
	ThreadPool* _thread_pool = nullptr;


public:
	LevelBuilder(ViewportManager* viewport_manager,
		const float* dt,
		DirectX::SpriteBatch* sprite_batch,
		ResourceManager* resource_manager,
		ID3D11SamplerState* sampler_state,
		ResolutionManager* resolution_manager,
		ThreadPool* thread_pool);

	std::unique_ptr<Level> build_level(const MenuLevelSettings& settings);
};

#endif // !LEVELBUILDER_H
