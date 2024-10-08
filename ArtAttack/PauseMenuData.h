#ifndef PAUSEMENUDATA_H
#define PAUSEMENUDATA_H

#include "MenuData.h"
#include "pause_menu_action.h"

class PauseMenuData : public MenuData
{
private:
	int _player_num = -1;
	pause_menu_action* _action = nullptr;
public:
	PauseMenuData(GameData* game_data, MenuInput* input, int player_num,
		pause_menu_action* action) :
		MenuData(game_data, input),
		_player_num(player_num),
		_action(action) {}

	int get_player_num() { return this->_player_num; }
	void set_player_num(int player_num) { this->_player_num = player_num; }
	pause_menu_action* get_action() { return this->_action; }
	void set_action(pause_menu_action* action) { this->_action = action; }
};

#endif // !PAUSEMENUDATE_H
