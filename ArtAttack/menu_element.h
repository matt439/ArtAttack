#ifndef MENU_ELEMENT_H
#define MENU_ELEMENT_H

enum class menu_element
{
	MAIN_MENU_START,
	MAIN_MENU_PLAY,
	MAIN_MENU_OPTIONS,
	MAIN_MENU_EXIT,
	MAIN_MENU_RESOLUTION,
	MAIN_MENU_FULLSCREEN,
	MAIN_MENU_APPLY,
	MAIN_MENU_BACK,
	MAIN_MENU_STANDARD_MODE,
	MAIN_MENU_TEAM_DEATHMATCH,
	MAIN_MENU_DEATHMATCH,
	MAIN_MENU_PRACTICE,
	MAIN_MENU_ONE_PLAYER,
	MAIN_MENU_TWO_PLAYERS,
	MAIN_MENU_THREE_PLAYERS,
	MAIN_MENU_FOUR_PLAYERS,
	
	PAUSE_MENU_RESUME,
	PAUSE_MENU_RESTART,
	PAUSE_MENU_QUIT,
	PAUSE_MENU_CONFIRMATION_YES,
	PAUSE_MENU_CONFIRMATION_NO,

	NONE,
};

#endif // !MENU_ELEMENT_H