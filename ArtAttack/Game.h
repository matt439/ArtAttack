#ifndef GAME_H
#define GAME_H

#include "DeviceResources.h"
#include "StepTimer.h"
#include "GameData.h"
#include "ResourceManager.h"
#include "StateContext.h"
#include <Audio.h>

class Game final : public DX::IDeviceNotify, public StateContext
{
public:
    Game() noexcept(false);
    ~Game();

    Game(Game&&) = default;
    Game& operator= (Game&&) = default;

    Game(Game const&) = delete;
    Game& operator= (Game const&) = delete;

    // Initialization and management
    void initialize(GameData* game_data);

    // Basic game loop
    void tick();

    // IDeviceNotify
    void OnDeviceLost() override;
    void OnDeviceRestored() override;

    // Messages
    void on_activated();
    void on_deactivated();
    void on_suspending();
    void on_resuming();
    void on_window_moved();
    void on_display_change();
    void on_window_size_changed(int width, int height);

    void set_game_data(GameData* game_data) { this->_data = game_data; }

private:
    void update(DX::StepTimer const& timer);
    void render();

    void clear();

    void create_device_dependent_resources();
    void create_window_size_dependent_resources();

    std::unique_ptr<DX::DeviceResources> _deviceResources = nullptr;
    DX::StepTimer m_timer = DX::StepTimer();
    std::unique_ptr<DirectX::SpriteBatch> _spriteBatch = nullptr;
    std::unique_ptr<DirectX::CommonStates> _states = nullptr;
    std::unique_ptr<ResourceLoader> _resource_loader = nullptr;
    std::unique_ptr<ResourceManager> _resource_manager = nullptr;
    std::unique_ptr<float> _dt = nullptr;
    std::unique_ptr<State> _state = nullptr;
    std::unique_ptr<DirectX::GamePad> _gamepad = nullptr;
    std::unique_ptr<ViewportManager> _viewport_manager = nullptr;
    GameData* _data = nullptr;
    std::unique_ptr<DirectX::AudioEngine> _audio_engine = nullptr;
};

#endif // !GAME_H