#include "pch.h"
#include "GameStates.h"

GameData* GameLevel::get_data() const
{
    return this->_game_data;
}
void GameLevel::init()
{
    this->_player_input = std::make_unique<PlayerInput>(
        this->get_data()->get_gamepad());

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
            //this->_player_input->update_and_get_player_inputs();
			this->_player_input->get_test_player_inputs();
        this->_level->update(player_inputs);
        break;
    }
    default:
		break;
    }
}

void GameLevel::draw()
{
    if (this->_state == game_level_state::ACTIVE)
    {
		this->_level->draw();
    }
}
