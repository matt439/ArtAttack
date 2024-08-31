#include "pch.h"
#include "Game.h"
#include "ResolutionManager.h"
#include "GameData.h"
#include "GameStates.h"
#include "MattMath.h"
#include "MenuLevelSettings.h"

constexpr bool FULLSCREEN = false;

using namespace DirectX;

#ifdef __clang__
#pragma clang diagnostic ignored "-Wcovered-switch-default"
#pragma clang diagnostic ignored "-Wswitch-enum"
#endif

#pragma warning(disable : 4061)

namespace
{
    std::unique_ptr<Game> g_game = nullptr;
    std::unique_ptr<ResolutionManager> g_resolution_manager = nullptr;
    std::unique_ptr<GameData> g_game_data = nullptr;
}

LPCWSTR g_szAppName = L"Colour Wars";

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void ExitGame() noexcept;

// Indicates to hybrid graphics systems to prefer the discrete part by default
extern "C"
{
    __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
    __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}

// Entry point
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    if (!XMVerifyCPUSupport())
        return 1;

    HRESULT hr = CoInitializeEx(nullptr, COINITBASE_MULTITHREADED);
    if (FAILED(hr))
        return 1;

    g_resolution_manager = std::make_unique<ResolutionManager>();
    g_resolution_manager->set_resolution(screen_resolution::S_1920_1080);

    g_game_data = std::make_unique<GameData>();
    g_game_data->set_resolution_manager(g_resolution_manager.get());

    g_game = std::make_unique<Game>();
    g_game->set_game_data(g_game_data.get());

    // Register class and create window
    {
        // Register class
        WNDCLASSEXW wcex = {};
        wcex.cbSize = sizeof(WNDCLASSEXW);
        wcex.style = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc = WndProc;
        wcex.hInstance = hInstance;
        wcex.hIcon = LoadIconW(hInstance, L"IDI_ICON");
        wcex.hCursor = LoadCursorW(nullptr, IDC_ARROW);
        wcex.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
        wcex.lpszClassName = L"ChromaClashWindowClass";
        wcex.hIconSm = LoadIconW(wcex.hInstance, L"IDI_ICON");
        if (!RegisterClassExW(&wcex))
            return 1;

        MattMath::Vector2I res_ivec2 =
            g_resolution_manager->get_resolution_ivec();
        RECT rc = { 0, 0, static_cast<LONG>(res_ivec2.x), static_cast<LONG>(res_ivec2.y) };

        AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

        HWND hwnd;

        if (FULLSCREEN)
        {
            hwnd = CreateWindowExW(WS_EX_TOPMOST, L"ChromaClashWindowClass", g_szAppName, WS_POPUP,
                CW_USEDEFAULT, CW_USEDEFAULT, res_ivec2.x, res_ivec2.y,
                nullptr, nullptr, hInstance, g_game.get());
        }
        else //windowed
        {
            hwnd = CreateWindowExW(0, L"ChromaClashWindowClass", g_szAppName, WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT, CW_USEDEFAULT, res_ivec2.x, res_ivec2.y,
                nullptr, nullptr, hInstance, g_game.get());
        }

        if (!hwnd)
            return 1;

        if (FULLSCREEN)
        {
            ShowWindow(hwnd, SW_SHOWMAXIMIZED);
        }
        else //windowed
        {
            ShowWindow(hwnd, nCmdShow);
        }

        GetClientRect(hwnd, &rc);

        g_game_data->set_window(hwnd);

        g_game->initialize(g_game_data.get());

		MenuPlayerSettings player_1_settings = { player_team::A, wep_type::SPRAYER, 0 };
		MenuPlayerSettings player_2_settings = { player_team::A, wep_type::MISTER, 1 };
		MenuPlayerSettings player_3_settings = { player_team::B, wep_type::SPRAYER, 2 };
		MenuPlayerSettings player_4_settings = { player_team::B, wep_type::MISTER, 3 };

        MenuLevelSettings level_settings;
        level_settings.set_player_count(4);
        level_settings.set_game_mode(level_mode::STANDARD_MODE);
        level_settings.set_stage(level_stage::SIT315);
        level_settings.set_screen_layout(screen_layout::FOUR_PLAYER);

		level_settings.set_player_setting(0, player_1_settings);
		level_settings.set_player_setting(1, player_2_settings);
		level_settings.set_player_setting(2, player_3_settings);
		level_settings.set_player_setting(3, player_4_settings);

		g_game->transition_to(std::make_unique<GameLevel>(g_game_data.get(), level_settings));
    }

	constexpr double GAME_RUN_TIME = 5.0;
	std::chrono::high_resolution_clock::time_point start_time = std::chrono::high_resolution_clock::now();

    // Main message loop
    MSG msg = {};
    while (WM_QUIT != msg.message)
    {
		if (GAME_RUN_TIME > 0.0)
		{
			std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(now - start_time);
			if (time_span.count() > GAME_RUN_TIME)
			{
				break;
			}
		}
        
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            g_game->tick();
        }
    }

    g_game.reset();

    CoUninitialize();

    return static_cast<int>(msg.wParam);
}

// Windows procedure
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static bool s_in_sizemove = false;
    static bool s_in_suspend = false;
    static bool s_minimized = false;
    static bool s_fullscreen = FULLSCREEN;

    auto game = reinterpret_cast<Game*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

    switch (message)
    {
    case WM_CREATE:
        if (lParam)
        {
            auto params = reinterpret_cast<LPCREATESTRUCTW>(lParam);
            SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(params->lpCreateParams));
        }
        break;

    case WM_PAINT:
        if (s_in_sizemove && game)
        {
            game->tick();
        }
        else
        {
            PAINTSTRUCT ps;
            std::ignore = BeginPaint(hWnd, &ps);
            EndPaint(hWnd, &ps);
        }
        break;

    case WM_DISPLAYCHANGE:
        if (game)
        {
            game->on_display_change();
        }
        break;

    case WM_MOVE:
        if (game)
        {
            game->on_window_moved();
        }
        break;

    case WM_SIZE:
        if (wParam == SIZE_MINIMIZED)
        {
            if (!s_minimized)
            {
                s_minimized = true;
                if (!s_in_suspend && game)
                    game->on_suspending();
                s_in_suspend = true;
            }
        }
        else if (s_minimized)
        {
            s_minimized = false;
            if (s_in_suspend && game)
                game->on_resuming();
            s_in_suspend = false;
        }
        else if (!s_in_sizemove && game)
        {
            game->on_window_size_changed(LOWORD(lParam), HIWORD(lParam));
        }
        break;

    case WM_ENTERSIZEMOVE:
        s_in_sizemove = true;
        break;

    case WM_EXITSIZEMOVE:
        s_in_sizemove = false;
        if (game)
        {
            RECT rc;
            GetClientRect(hWnd, &rc);

            game->on_window_size_changed(rc.right - rc.left, rc.bottom - rc.top);
        }
        break;

    case WM_GETMINMAXINFO:
        if (lParam)
        {
            auto info = reinterpret_cast<MINMAXINFO*>(lParam);
            info->ptMinTrackSize.x = 320;
            info->ptMinTrackSize.y = 200;
        }
        break;

    case WM_ACTIVATEAPP:
        if (game)
        {
            if (wParam)
            {
                game->on_activated();
            }
            else
            {
                game->on_deactivated();
            }
        }
        break;

    case WM_POWERBROADCAST:
        switch (wParam)
        {
        case PBT_APMQUERYSUSPEND:
            if (!s_in_suspend && game)
                game->on_suspending();
            s_in_suspend = true;
            return TRUE;

        case PBT_APMRESUMESUSPEND:
            if (!s_minimized)
            {
                if (s_in_suspend && game)
                    game->on_resuming();
                s_in_suspend = false;
            }
            return TRUE;
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_SYSKEYDOWN:
        break;

    case WM_MENUCHAR:
        // A menu is active and the user presses a key that does not correspond
        // to any mnemonic or accelerator key. Ignore so we don't produce an error beep.
        return MAKELRESULT(0, MNC_CLOSE);
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}

// Exit helper
void ExitGame() noexcept
{
    PostQuitMessage(0);
}