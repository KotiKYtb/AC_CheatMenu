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
        overlay::Render(targetWindow);
        gui::EndRender();

    }

    overlay::DestroyDevice();
    overlay::DestroyOverlayWindow();

    gui::DestroyImGui();
    gui::DestroyDevice();
    gui::DestroyHWindow();

    return EXIT_SUCCESS;
}