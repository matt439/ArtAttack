#ifndef WEAPONBUILDER_H
#define WEAPONBUILDER_H

#include "Weapon.h"

class WeaponBuilder
{
public:
	WeaponBuilder() = default;
	static std::unique_ptr<Weapon> build_weapon(
		player_team team,
		int player_num,
		const MattMath::Colour& team_colour,
		wep_type type,
		const MattMath::Vector2F& player_center,
		DirectX::SpriteBatch* sprite_batch,
		ResourceManager* resource_manager,
		const float* dt);
};

#endif // !WEAPONBUILDER_H
