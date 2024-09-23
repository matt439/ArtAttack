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

    _deviceResources->RegisterDeviceNotify(this);
}

Game::~Game()
{
    if (_audio_engine)
    {
        _audio_engine->Suspend();
    }

	this->_performance_statistics->write_statistics_to_file(STATS_FILE);
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

    // create deferred contexts
    _deviceResources->create_deferred_contexts(NUM_THREADS_MAX);

    create_device_dependent_resources();

    _deviceResources->CreateWindowSizeDependentResources();
    create_window_size_dependent_resources();
   
    this->_gamepad = std::make_unique<GamePad>();
    this->_data->set_gamepad(this->_gamepad.get());

    m_timer.SetFixedTimeStep(true);
    m_timer.SetTargetElapsedSeconds(1.0 / TARGET_FPS);
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
	auto deferred_contexts = _deviceResources->get_deferred_contexts();
    auto renderTarget = _deviceResources->GetRenderTargetView();

    context->ClearRenderTargetView(renderTarget, Colors::Black);

    context->OMSetRenderTargets(1, &renderTarget, nullptr);

	for (auto& deferred_context : *deferred_contexts)
	{
		deferred_context->OMSetRenderTargets(1, &renderTarget, nullptr);
	}

    // Set the viewport.
    auto const viewport = _deviceResources->GetScreenViewport();
    context->RSSetViewports(1, &viewport);

	for (auto& deferred_context : *deferred_contexts)
	{
		deferred_context->RSSetViewports(1, &viewport);
	}

    _deviceResources->PIXEndEvent();
}
#pragma endregion

#pragma region Message Handlers
// Message handlers
void Game::on_activated()
{
    if (this->_gamepad)
        this->_gamepad->Resume();
}

void Game::on_deactivated()
{
    this->_gamepad->Suspend();
}

void Game::on_suspending()
{
    this->_gamepad->Suspend();
    _audio_engine->Suspend();
}

void Game::on_resuming()
{
    m_timer.ResetElapsedTime();
    this->_gamepad->Resume();
    _audio_engine->Resume();
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
}

#pragma endregion

#pragma region Direct3D Resources
// These are the resources that depend on the device.
void Game::create_device_dependent_resources()
{
    auto device = _deviceResources->GetD3DDevice();

    auto context = _deviceResources->GetD3DDeviceContext();

	this->_sprite_batches.resize(NUM_THREADS_MAX);
	this->_sprite_batches_ptrs.resize(NUM_THREADS_MAX);
	for (int i = 0; i < NUM_THREADS_MAX; i++)
	{
		this->_sprite_batches[i] = std::move(
			std::make_unique<SpriteBatch>(this->_deviceResources->get_deferred_context(i)));

		this->_sprite_batches_ptrs[i] = this->_sprite_batches[i].get();
	}

	this->_data->set_sprite_batches(&this->_sprite_batches_ptrs);

    this->_performance_statistics =
        std::make_unique<PerformanceStatistics>(TARGET_FPS, NUM_THREADS_MAX);

	this->_thread_pool = std::make_unique<ThreadPool>(NUM_THREADS_MIN, NUM_THREADS_MAX);
	this->_data->set_thread_pool(this->_thread_pool.get());

    this->_resource_manager = std::make_unique<ResourceManager>();
    this->_data->set_resource_manager(this->_resource_manager.get());
    this->_resource_loader = std::make_unique<ResourceLoader>(
        this->_resource_manager.get(), device, this->_audio_engine.get());
    this->_data->set_resource_loader(this->_resource_loader.get());
    this->_dt = std::make_unique<float>(0.f);
    this->_data->set_dt(this->_dt.get());

    this->_viewport_manager = std::make_unique<ViewportManager>(
		this->_data->get_resolution_manager(), this->_data->get_sprite_batches()->at(0), // TODO: Fix this
        this->_data->get_device_resources());
    this->_data->set_viewport_manager(this->_viewport_manager.get());

    _states = std::make_unique<CommonStates>(device);
    this->_data->set_common_states(_states.get());

    this->_resource_loader->load_all_resources();
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::create_window_size_dependent_resources()
{
}

void Game::on_device_lost()
{
	for (auto& sprite_batch : this->_sprite_batches)
	{
		sprite_batch.reset();
	}

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
