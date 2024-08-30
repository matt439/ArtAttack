#ifndef MENU_PLAYER_SETTINGS_H
#define MENU_PLAYER_SETTINGS_H

#include "player_team.h"
#include "wep_type.h"

struct MenuPlayerSettings
{
    player_team team = player_team::NONE;
    wep_type weapon = wep_type::SPRAYER;
    int num = -1;

    MenuPlayerSettings(player_team team, wep_type wep, int num) :
		team(team), weapon(wep), num(num) {}
    MenuPlayerSettings() = default;
};

#endif // !MENU_PLAYER_SETTINGS_H
