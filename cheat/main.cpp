#include "gui.h"
#include "cheat.h"
#include "../cheat/memory.h"
#include <thread>
#include "windows.h"

int __stdcall wWinMain(HINSTANCE instance, HINSTANCE prevInstance, PWSTR args, int cmdShow)
{
    HWND targetWindow = FindWindow(NULL, "AssaultCube");
    if (!targetWindow)
        return EXIT_FAILURE;

    gui::CreateHWindow("Cheat Menu");
    gui::CreateDevice();
    gui::CreateImGui();

    overlay::CreateOverlayWindow("Overlay", targetWindow);
    overlay::CreateDevice();

    while (gui::isRunning)
    {
        gui::BeginRender();
        gui::Render();
        gui::EndRender();

        overlay::Render(targetWindow);

        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }

    overlay::DestroyDevice();
    overlay::DestroyOverlayWindow();

    gui::DestroyImGui();
    gui::DestroyDevice();
    gui::DestroyHWindow();

    return EXIT_SUCCESS;
}