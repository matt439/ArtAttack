#include "pch.h"
#include "PlayerBuilder.h"

using namespace DirectX;
using namespace MattMath;
using namespace player_consts;

PlayerBuilder::PlayerBuilder()
{
    this->_weapon_builder = std::make_unique<WeaponBuilder>();
}

std::unique_ptr<std::vector<std::unique_ptr<Player>>> PlayerBuilder::build_players(
	const MenuLevelSettings& settings,
	const LevelLoadedInfo* load_info,
	TeamColour team_colours,
	ResourceManager* resource_manager,
	const ViewportManager* viewport_manager,
	const float* dt) const
{
	auto players = std::make_unique<std::vector<std::unique_ptr<Player>>>();

	const std::vector<Vector2F> team_a_spawns = load_info->get_team_a_spawns();
	const std::vector<Vector2F> team_b_spawns = load_info->get_team_b_spawns();

	int i = 0;
	for (auto& setting : settings.get_player_settings())
	{
		Vector2F position = Vector2F::ZERO;
		if (setting.team == player_team::A)
		{
			position = team_a_spawns[i];
		}
		else
		{
			position = team_b_spawns[i];
		}
		auto rect = RectangleF(position, DEFAULT_SIZE);

		auto player = std::make_unique<Player>(
			rect,
			DEFAULT_ANIMATION_INFO,
			resource_manager,
			setting.num,
			setting.team,
			setting.weapon,
			this->_weapon_builder->build_weapon(
				setting.team,
				setting.num,
				team_colours.get_team_colour(setting.team),
				setting.weapon,
				rect.get_center(),
				resource_manager,
				dt),
			wep_type::GRENADE_STD,
			team_colours.get_team_colour(setting.team),
			viewport_manager->
				get_player_viewport(setting.num),
			dt,
			position);

		players->push_back(std::move(player));

		i++;
	}
	return players;
}
