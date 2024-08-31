#include "pch.h"
#include "Game.h"

extern void ExitGame() noexcept;

using namespace DirectX;
using namespace std::chrono;

using Microsoft::WRL::ComPtr;

Game::Game() noexcept(false)
{
    // Renders only 2D, so no need for a depth buffer.
    _deviceResources = std::make_unique<DX::DeviceResources>(
        DXGI_FORMAT_B8G8R8A8_UNORM, DXGI_FORMAT_UNKNOWN);

    //m_deviceResources = std::make_unique<DX::DeviceResources>();
    // TODO: Provide parameters for swapchain format, depth/stencil format, and backbuffer count.
    //   Add DX::DeviceResources::c_AllowTearing to opt-in to variable rate displays.
    //   Add DX::DeviceResources::c_EnableHDR for HDR10 display.

    _deviceResources->RegisterDeviceNotify(this);
}

Game::~Game()
{
    if (_audio_engine)
    {
        _audio_engine->Suspend();
    }

	auto stats = this->_performance_statistics->calculate_statistics();
	auto game_stats = this->_performance_statistics->calculate_game_statistics(stats);
	int x = 0;
}

// Initialize the Direct3D resources required to run.
void Game::initialize(GameData* game_data)
{
    this->_data = game_data;

    this->_data->set_device_resources(_deviceResources.get());

    MattMath::Vector2I window_size = this->_data->get_resolution_manager()->get_resolution_ivec();
    _deviceResources->SetWindow(this->_data->get_window(),
        window_size.x, window_size.y);

    AUDIO_ENGINE_FLAGS eflags = AudioEngine_Default;
#ifdef _DEBUG
    eflags |= AudioEngine_Debug;
#endif
    _audio_engine = std::make_unique<AudioEngine>(eflags);

    _deviceResources->CreateDeviceResources();
    create_device_dependent_resources();

    _deviceResources->CreateWindowSizeDependentResources();
    create_window_size_dependent_resources();

    this->_gamepad = std::make_unique<GamePad>();
    this->_data->set_gamepad(this->_gamepad.get());

    m_timer.SetFixedTimeStep(true);
    m_timer.SetTargetElapsedSeconds(1.0 / 75);
}

#pragma region Frame Update
void Game::tick()
{
    m_timer.Tick([&]()
        {
            update(m_timer);
        });

	high_resolution_clock::time_point now = high_resolution_clock::now();
	duration<double> time_span = duration_cast<duration<double>>(now - _last_time);

	if (this->_stats_start_countdown > 0)
	{
		this->_stats_start_countdown--;
	}
	else
	{
		this->_performance_statistics->add_frame_time(time_span.count());
	}
	_last_time = now;

    render();
}

// Updates the world.
void Game::update(DX::StepTimer const& timer) const
{
    float elapsedTime = static_cast<float>(timer.GetElapsedSeconds());
    *this->_dt = elapsedTime;
	this->StateContext::update();
    if (!_audio_engine->Update())
    {
    }
}
#pragma endregion

#pragma region Frame Render
// Draws the scene.
void Game::render()
{
    // Don't try to render anything before the first Update.
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }

    clear();

    _deviceResources->PIXBeginEvent(L"Render");

    this->draw();

    _deviceResources->PIXEndEvent();

    // Show the new frame.
    _deviceResources->Present();
}

// Helper method to clear the back buffers.
void Game::clear() const
{
    _deviceResources->PIXBeginEvent(L"Clear");

    // Clear the views.
    auto context = _deviceResources->GetD3DDeviceContext();
    auto renderTarget = _deviceResources->GetRenderTargetView();

    context->ClearRenderTargetView(renderTarget, Colors::Black);
    context->OMSetRenderTargets(1, &renderTarget, nullptr);

    // Set the viewport.
    auto const viewport = _deviceResources->GetScreenViewport();
    context->RSSetViewports(1, &viewport);

    _deviceResources->PIXEndEvent();
}
#pragma endregion

#pragma region Message Handlers
// Message handlers
void Game::on_activated()
{
    // TODO: Game is becoming active window.

    if (this->_gamepad)
        this->_gamepad->Resume();
}

void Game::on_deactivated()
{
    // TODO: Game is becoming background window.
    this->_gamepad->Suspend();
}

void Game::on_suspending()
{
    // TODO: Game is being power-suspended (or minimized).
    this->_gamepad->Suspend();
    _audio_engine->Suspend();
}

void Game::on_resuming()
{
    m_timer.ResetElapsedTime();
    this->_gamepad->Resume();
    _audio_engine->Resume();
    // TODO: Game is being power-resumed (or returning from minimize).
}

void Game::on_window_moved()
{
    auto const r = _deviceResources->GetOutputSize();
    _deviceResources->WindowSizeChanged(r.right, r.bottom);
}

void Game::on_display_change()
{
    _deviceResources->UpdateColorSpace();
}

void Game::on_window_size_changed(int width, int height)
{
    if (!_deviceResources->WindowSizeChanged(width, height))
        return;

    create_window_size_dependent_resources();

    // TODO: Game window is being resized.
}

#pragma endregion

#pragma region Direct3D Resources
// These are the resources that depend on the device.
void Game::create_device_dependent_resources()
{
    auto device = _deviceResources->GetD3DDevice();

    // TODO: Initialize device dependent objects here (independent of window size).
    auto context = _deviceResources->GetD3DDeviceContext();
    _spriteBatch = std::make_unique<SpriteBatch>(context);
    this->_data->set_sprite_batch(_spriteBatch.get());

    this->_performance_statistics = std::make_unique<PerformanceStatistics>();

    this->_resource_manager = std::make_unique<ResourceManager>();
    this->_data->set_resource_manager(this->_resource_manager.get());
    this->_resource_loader = std::make_unique<ResourceLoader>(
        this->_resource_manager.get(), device, this->_audio_engine.get());
    this->_data->set_resource_loader(this->_resource_loader.get());
    this->_dt = std::make_unique<float>(0.f);
    this->_data->set_dt(this->_dt.get());

    this->_viewport_manager = std::make_unique<ViewportManager>(
        this->_data->get_resolution_manager(), this->_data->get_sprite_batch(),
        this->_data->get_device_resources());
    this->_data->set_viewport_manager(this->_viewport_manager.get());

    _states = std::make_unique<CommonStates>(device);
    this->_data->set_common_states(_states.get());

    this->_resource_loader->load_all_resources();
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::create_window_size_dependent_resources()
{
    //auto size = _deviceResources->GetOutputSize();
}

void Game::on_device_lost()
{
    // TODO: Add Direct3D resource cleanup here.
    _spriteBatch.reset();
    _states.reset();
    this->_resource_manager->reset_all_textures();
    this->_resource_manager->reset_all_sprite_fonts();
    this->_resource_manager->reset_all_sounds();
}

void Game::on_device_restored()
{
    create_device_dependent_resources();

    create_window_size_dependent_resources();
}

#pragma endregion
