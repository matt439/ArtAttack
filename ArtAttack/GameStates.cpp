#include "pch.h"
#include "GameStates.h"

GameData* GameLevel::get_data()
{
    return this->_game_data;
}
void GameLevel::init()
{
    this->_player_input = std::make_unique<PlayerInput>(
        this->get_data()->get_gamepad());
    //this->_menu_input = std::make_unique<MenuInput>(
    //    this->get_data()->get_gamepad());

    this->_level_builder = std::make_unique<LevelBuilder>(
        this->get_data()->get_viewport_manager(),
        this->get_data()->get_dt(),
        this->get_data()->get_sprite_batch(),
        this->get_data()->get_resource_manager(),
        this->get_data()->get_common_states()->PointClamp(),
        this->get_data()->get_resolution_manager());

    this->get_data()->get_viewport_manager()->
        set_layout(this->_settings.get_screen_layout());

    this->_level = std::move(this->_level_builder->build_level(
        this->_settings));
}
void GameLevel::update()
{

    switch (this->_state)
    {
    case game_level_state::FIRST_UPDATE:
        this->_state = game_level_state::SECOND_UPDATE;
        return;
    case game_level_state::SECOND_UPDATE:
        this->_state = game_level_state::ACTIVE;
        //no break here so it goes to active
    case game_level_state::ACTIVE:
    {
        std::vector<player_input> player_inputs =
            this->_player_input->update_and_get_player_inputs();

        this->_level->update(player_inputs);
        break;
    }
    default:
		break;
    }
}

void GameLevel::draw()
{
    switch (this->_state)
    {
    case game_level_state::FIRST_UPDATE:
        break;
    case game_level_state::SECOND_UPDATE:
        break;
    case game_level_state::ACTIVE:
        this->_level->draw();
        break;
    //case game_level_state::PAUSE_MENU:
    //    this->_level->draw();
    //    this->_pause_menu->draw();
    //    break;
    //case game_level_state::RESULTS:
    //    this->_level->draw();
    //    this->_results_menu->draw();
    //    break;
    //case game_level_state::END_MENU:
    //    this->_level->draw();
    //    this->_end_menu->draw();
    //    break;
    }
}

//int GameLevel::check_for_pause_input(
//    const std::vector<player_input>& player_inputs)
//{
//    for (int i = 0; i < static_cast<int>(player_inputs.size()); i++)
//    {
//        if (player_inputs[i].toggle_pause_menu)
//        {
//            return i;
//        }
//    }
//    return -1;
//}