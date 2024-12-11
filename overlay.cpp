#include "overlay.h"
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_dx9.h"
#include "../imgui/imgui_impl_win32.h"

void overlay::Initialize(const char* windowName) noexcept
{
    // Recherche la fenêtre du jeu
    gameWindow = FindWindowA(nullptr, "AssaultCube");
    if (!gameWindow) return;

    // Création de la fenêtre de l'overlay
    if (!CreateOverlayWindow(windowName)) return;

    // Initialisation DirectX
    d3d = Direct3DCreate9(D3D_SDK_VERSION);
    if (!d3d) return;

    ZeroMemory(&presentParameters, sizeof(presentParameters));
    presentParameters.Windowed = TRUE;
    presentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
    presentParameters.BackBufferFormat = D3DFMT_A8R8G8B8;
    presentParameters.EnableAutoDepthStencil = TRUE;
    presentParameters.AutoDepthStencilFormat = D3DFMT_D16;

    if (d3d->CreateDevice(
        D3DADAPTER_DEFAULT,
        D3DDEVTYPE_HAL,
        overlayWindow,
        D3DCREATE_HARDWARE_VERTEXPROCESSING,
        &presentParameters,
        &device) < 0)
    {
        Cleanup();
        return;
    }

    // Initialisation ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplWin32_Init(overlayWindow);
    ImGui_ImplDX9_Init(device);
}

bool overlay::CreateOverlayWindow(const char* overlayName) noexcept
{
    overlayWindowClass.cbSize = sizeof(WNDCLASSEX);
    overlayWindowClass.style = CS_CLASSDC;
    overlayWindowClass.lpfnWndProc = WindowProc;
    overlayWindowClass.cbClsExtra = 0;
    overlayWindowClass.cbWndExtra = 0;
    overlayWindowClass.hInstance = GetModuleHandleA(nullptr);
    overlayWindowClass.hIcon = 0;
    overlayWindowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
    overlayWindowClass.hbrBackground = nullptr;
    overlayWindowClass.lpszMenuName = nullptr;
    overlayWindowClass.lpszClassName = "OverlayClass";
    overlayWindowClass.hIconSm = 0;

    RegisterClassEx(&overlayWindowClass);

    overlayWindow = CreateWindowExA(
        WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TRANSPARENT,
        overlayWindowClass.lpszClassName,
        overlayName,
        WS_POPUP,
        0, 0, 1920, 1080, // Taille initiale arbitraire
        nullptr,
        nullptr,
        overlayWindowClass.hInstance,
        nullptr
    );

    SetLayeredWindowAttributes(overlayWindow, RGB(0, 0, 0), 0, LWA_COLORKEY);
    ShowWindow(overlayWindow, SW_SHOWDEFAULT);

    return true;
}

void overlay::UpdateOverlayPosition() noexcept
{
    RECT rect;
    GetWindowRect(gameWindow, &rect);

    SetWindowPos(
        overlayWindow,
        HWND_TOPMOST,
        rect.left,
        rect.top,
        rect.right - rect.left,
        rect.bottom - rect.top,
        SWP_NOREDRAW
    );
}

void overlay::Render() noexcept
{
    UpdateOverlayPosition(); // Synchronise avec le jeu

    // Gestion DirectX et ImGui
    ImGui_ImplDX9_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    // Exemple : ESP Box
    ImGui::Begin("ESP Overlay", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::Text("Overlay en cours...");
    ImGui::End();

    ImGui::EndFrame();

    device->SetRenderState(D3DRS_ZENABLE, FALSE);
    device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
    device->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);

    device->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);
    if (device->BeginScene() >= 0)
    {
        ImGui::Render();
        ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
        device->EndScene();
    }
    device->Present(nullptr, nullptr, nullptr, nullptr);
}

void overlay::Cleanup() noexcept
{
    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    if (device) { device->Release(); device = nullptr; }
    if (d3d) { d3d->Release(); d3d = nullptr; }

    DestroyWindow(overlayWindow);
    UnregisterClass(overlayWindowClass.lpszClassName, overlayWindowClass.hInstance);
}

LRESULT CALLBACK overlay::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam))
        return true;

    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}
