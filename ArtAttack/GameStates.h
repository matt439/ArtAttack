#ifndef GAMESTATES_H
#define GAMESTATES_H

#include "State.h"
#include "MenuLevelSettings.h"
#include "GameData.h"
#include "LevelBuilder.h"
#include "PauseMenu.h"
#include "ResultsMenu.h"
#include "MainMenu.h"
#include "EndMenu.h"
#include "PlayerInput.h"

class GameMenu : public State
{
private:
    GameData* _game_data = nullptr; // need this to pass to GameLevel
    std::unique_ptr<StateContext> _menu = nullptr;
    std::unique_ptr<MenuInput> _menu_input = nullptr;
    std::unique_ptr<MainMenuData> _menu_data = nullptr;
    std::unique_ptr<MenuLevelSettings> _menu_level_settings = nullptr;
    std::unique_ptr<bool> _is_ready_to_load_level = nullptr;
    main_menu_screen _screen = main_menu_screen::TITLE;
    //void create_main_menu_data();
    void set_main_menu_data_ptrs();
    void order_level_creation();
public:
    GameMenu(GameData* game_data);
    GameMenu(GameData* game_data,
        const main_menu_midway_load_settings& settings);
    void update() override;
    void draw() override;
    void init() override;
};

enum class game_level_state
{
    FIRST_UPDATE,
    SECOND_UPDATE,
    ACTIVE,
    PAUSE_MENU,
    RESULTS,
    END_MENU,
    //BACK_TO_MAIN_MENU,
};

class GameLevel : public State
{
private:
    GameData* _game_data = nullptr;
    MenuLevelSettings _settings = MenuLevelSettings();
    std::unique_ptr<Level> _level = nullptr;
    std::unique_ptr<LevelBuilder> _level_builder = nullptr;
    std::unique_ptr<PlayerInput> _player_input = nullptr;
    std::unique_ptr<StateContext> _pause_menu = nullptr;
    std::unique_ptr<pause_menu_action> _pause_menu_action = nullptr;
    std::unique_ptr<PauseMenuData> _pause_menu_data = nullptr;
    std::unique_ptr<MenuInput> _menu_input = nullptr;
    std::unique_ptr<StateContext> _results_menu = nullptr;
    std::unique_ptr<results_menu_action> _results_menu_action = nullptr;
    std::unique_ptr<ResultsMenuData> _results_menu_data = nullptr;
    std::unique_ptr<StateContext> _end_menu = nullptr;
    std::unique_ptr<end_menu_action> _end_menu_action = nullptr;
    std::unique_ptr<EndMenuData> _end_menu_data = nullptr;
    game_level_state _state = game_level_state::FIRST_UPDATE;
    int check_for_pause_input(
        const std::vector<player_input>& player_inputs);
    GameData* get_data();
public:
    GameLevel(GameData* game_data, const MenuLevelSettings& settings) :
        _settings(settings), _game_data(game_data) {}
    void update() override;
    void draw() override;
    void init() override;
};

#endif // !GAMELEVEL_H
