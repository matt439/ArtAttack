#ifndef GAMESTATES_H
#define GAMESTATES_H

#include "State.h"
#include "MenuLevelSettings.h"
#include "GameData.h"
#include "LevelBuilder.h"
#include "PlayerInput.h"

enum class game_level_state
{
	FIRST_UPDATE,
	SECOND_UPDATE,
	ACTIVE,
};

class GameLevel final : public State
{
private:
    GameData* _game_data = nullptr;
    MenuLevelSettings _settings = MenuLevelSettings();
    std::unique_ptr<Level> _level = nullptr;
    std::unique_ptr<LevelBuilder> _level_builder = nullptr;
    std::unique_ptr<PlayerInput> _player_input = nullptr;
    game_level_state _state = game_level_state::FIRST_UPDATE;
    GameData* get_data() const;
public:
    GameLevel(GameData* game_data, const MenuLevelSettings& settings) :
        _game_data(game_data), _settings(settings) {}
    void update() override;
    void draw() override;
    void init() override;
};

#endif // !GAMELEVEL_H
