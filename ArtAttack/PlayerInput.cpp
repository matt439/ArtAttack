#include "pch.h"
#include "PlayerInput.h"

using namespace DirectX;
using namespace MattMath;
using namespace player_input_consts;

PlayerInput::PlayerInput(GamePad* gamepad) :
    _gamepad(gamepad)
{
    for (int i = 0; i < 4; i++)
    {
        this->_prev_inputs[i] = RawPlayerInput();
    }
}

std::vector<player_input> PlayerInput::get_test_player_inputs()
{
	std::vector<player_input> result;

	player_input input_1;
	input_1.connection = connection_state::CONNECTED;
	Vector2F direction_1 = { 1.0f, -3.0f };
    direction_1.normalize();
    input_1.shoot_angle = direction_1.angle();
    input_1.shoot_direction = direction_1;
    input_1.shoot_direction_requested = true;
	input_1.primary_shoot = true;

	player_input input_2;
	input_2.connection = connection_state::CONNECTED;
	Vector2F direction_2 = { 1.0f, -1.0f };
	direction_2.normalize();
	input_2.shoot_angle = direction_2.angle();
	input_2.shoot_direction = direction_2;
	input_2.shoot_direction_requested = true;
	input_2.primary_shoot = true;

	player_input input_3;
	input_3.connection = connection_state::CONNECTED;
	Vector2F direction_3 = { 1.0f, -2.0f };
	direction_3.normalize();
	input_3.shoot_angle = direction_3.angle();
	input_3.shoot_direction = direction_3;
	input_3.shoot_direction_requested = true;
	input_3.primary_shoot = true;

	player_input input_4;
	input_4.connection = connection_state::CONNECTED;
	Vector2F direction_4 = { 1.0f, -0.5f };
	direction_4.normalize();
	input_4.shoot_angle = direction_4.angle();
	input_4.shoot_direction = direction_4;
	input_4.shoot_direction_requested = true;
	input_4.primary_shoot = true;

	result.push_back(input_1);
	result.push_back(input_2);
	result.push_back(input_3);
	result.push_back(input_4);

	return result;
}

RawPlayerInput PlayerInput::get_raw_input(int gamepad_num) const
{
    RawPlayerInput result = RawPlayerInput();
    auto pad = this->_gamepad->GetState(gamepad_num, GamePad::DEAD_ZONE_CIRCULAR);
    if (pad.IsConnected())
    {
        result.left_analog_stick = Vector2F(pad.thumbSticks.leftX,
            -pad.thumbSticks.leftY);
        result.right_analog_stick = Vector2F(pad.thumbSticks.rightX,
			-pad.thumbSticks.rightY);
        result.jump_button = pad.buttons.a;
        result.jump_trigger = pad.triggers.left;
        result.primary_shoot = pad.triggers.right;
        result.secondary_shoot = pad.buttons.rightShoulder;
        result.show_debug = pad.buttons.back;
        result.pause_menu = pad.buttons.start;
        result.connected = true;
    }
    return result;
}

player_input PlayerInput::calculate_player_input(
    const RawPlayerInput& current, const RawPlayerInput& previous)
{
    player_input result;

    result.jump_held = current.jump_button || current.jump_trigger > TRIGGER_JUMP_THRESHOLD;

    bool jump_button_pressed = current.jump_button && !previous.jump_button;
    bool jump_trigger_pressed = current.jump_trigger > TRIGGER_JUMP_THRESHOLD &&
        previous.jump_trigger <= TRIGGER_JUMP_THRESHOLD;
    result.jump_pressed = jump_button_pressed || jump_trigger_pressed;
    
    result.secondary_shoot = current.secondary_shoot;

    // pause menu is on key press
    bool pause_menu = !current.pause_menu && previous.pause_menu;
    if (pause_menu)
	{
		result.toggle_pause_menu = true;
	}
	else
	{
		result.toggle_pause_menu = false;
	}

    // show debug is on key press
    bool show_debug = !current.show_debug && previous.show_debug;
    if (show_debug)
	{
		result.toggle_debug = true;
	}
	else
	{
		result.toggle_debug = false;
	}

    // primary shoot is analog trigger
    // so need to check if it has gone past threshold
    bool primary_shoot = current.primary_shoot > TRIGGER_SHOOT_THRESHOLD;
    if (primary_shoot)
	{
        result.primary_shoot = true;
	}
	else
{
        result.primary_shoot = false;
	}

    if (std::fabs(current.left_analog_stick.x) > STICK_DEADZONE)
    {
		result.x_movement = current.left_analog_stick.x;
	}
    else
    {
        result.x_movement = 0.0f;
    }


    Vector2F direction = current.right_analog_stick;
    if (direction.length() > STICK_DEADZONE)
	{
		direction.normalize();
        result.shoot_angle = direction.angle();
        result.shoot_direction = direction;
        result.shoot_direction_requested = true;
	}
	else
	{
        result.shoot_direction = Vector2F::ZERO;
        result.shoot_angle = 0.0f;
        result.shoot_direction_requested = false;
	}

    result.connection = connection_state::CONNECTED;

    result.left_analog_stick = current.left_analog_stick;
    result.right_analog_stick = current.right_analog_stick;

    return result;
}

std::vector<player_input> PlayerInput::update_and_get_player_inputs()
{
    RawPlayerInput current[4];
    for (int i = 0; i < 4; i++)
    {
        current[i] = this->get_raw_input(i);
    }
    std::vector<player_input> result;
    for (int i = 0; i < 4; i++)
    {
        if (current[i].connected)
        {
            player_input input = calculate_player_input(current[i],
                this->_prev_inputs[i]);
            result.push_back(input);
        }
        this->_prev_inputs[i] = current[i];
    }
    return result;
}