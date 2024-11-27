#include "gui.h"
#include "cheat.h"
#include "memory.h"
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_dx9.h"
#include "../imgui/imgui_impl_win32.h"

bool gui::isGodModeOn = false;
bool gui::isInfNadeOn = false;
bool gui::isInfAmmoOn = false;
bool gui::isNoRecoilOn = false;
bool gui::isInfShieldOn = false;
bool gui::isSpeedHackOn = false;
bool gui::isWallHackOn = false;
bool gui::isFlyOn = false;
bool gui::isNoclipOn = false;
int gui::updatedHealth = 0;
int gui::updatedNade = 0;
int gui::updatedAmmo = 0;
int gui::updatedShield = 0;
Memory memory("ac_client.exe");

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(
	HWND window,
	UINT message,
	WPARAM wideParameter,
	LPARAM longParameter
);

long __stdcall WindowProcess(
	HWND window,
	UINT message,
	WPARAM wideParameter,
	LPARAM longParameter)
{
	if (ImGui_ImplWin32_WndProcHandler(window, message, wideParameter, longParameter))
		return true;

	switch (message)
	{
	case WM_SIZE: {
		if (gui::device && wideParameter != SIZE_MINIMIZED)
		{
			gui::presentParameters.BackBufferWidth = LOWORD(longParameter);
			gui::presentParameters.BackBufferHeight = HIWORD(longParameter);
			gui::ResetDevice();
		}
	}return 0;

	case WM_SYSCOMMAND: {
		if ((wideParameter & 0xfff0) == SC_KEYMENU)
			return 0;
	}break;

	case WM_DESTROY: {
		PostQuitMessage(0);
	}return 0;

	case WM_LBUTTONDOWN: {
		gui::position = MAKEPOINTS(longParameter);
	}return 0;

	case WM_MOUSEMOVE: {
		if (wideParameter == MK_LBUTTON)
		{
			const auto points = MAKEPOINTS(longParameter);
			auto rect = ::RECT{ };

			GetWindowRect(gui::window, &rect);

			rect.left += points.x - gui::position.x;
			rect.top += points.y - gui::position.y;

			if (gui::position.x >= 0 &&
				gui::position.x <= gui::WIDTH &&
				gui::position.y >= 0 && gui::position.y <= 19)
				SetWindowPos(
					gui::window,
					HWND_TOPMOST,
					rect.left,
					rect.top,
					0, 0,
					SWP_SHOWWINDOW | SWP_NOSIZE | SWP_NOZORDER
				);
		}

	}return 0;

	}

	return DefWindowProc(window, message, wideParameter, longParameter);
}

void gui::CreateHWindow(const char* windowName) noexcept
{
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_CLASSDC;
	windowClass.lpfnWndProc = WindowProcess;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = GetModuleHandleA(0);
	windowClass.hIcon = 0;
	windowClass.hCursor = 0;
	windowClass.hbrBackground = 0;
	windowClass.lpszMenuName = 0;
	windowClass.lpszClassName = "class001";
	windowClass.hIconSm = 0;

	RegisterClassEx(&windowClass);

	window = CreateWindowEx(
		0,
		"class001",
		windowName,
		WS_POPUP,
		100,
		100,
		WIDTH,
		HEIGHT,
		0,
		0,
		windowClass.hInstance,
		0
	);

	ShowWindow(window, SW_SHOWDEFAULT);
	UpdateWindow(window);
}

void gui::DestroyHWindow() noexcept
{
	DestroyWindow(window);
	UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
}

bool gui::CreateDevice() noexcept
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);

	if (!d3d)
		return false;

	ZeroMemory(&presentParameters, sizeof(presentParameters));

	presentParameters.Windowed = TRUE;
	presentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	presentParameters.BackBufferFormat = D3DFMT_UNKNOWN;
	presentParameters.EnableAutoDepthStencil = TRUE;
	presentParameters.AutoDepthStencilFormat = D3DFMT_D16;
	presentParameters.PresentationInterval = D3DPRESENT_INTERVAL_ONE;

	if (d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		window,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&presentParameters,
		&device) < 0)
		return false;

	return true;
}

void gui::ResetDevice() noexcept
{
	ImGui_ImplDX9_InvalidateDeviceObjects();

	const auto result = device->Reset(&presentParameters);

	if (result == D3DERR_INVALIDCALL)
		IM_ASSERT(0);

	ImGui_ImplDX9_CreateDeviceObjects();
}

void gui::DestroyDevice() noexcept
{
	if (device)
	{
		device->Release();
		device = nullptr;
	}

	if (d3d)
	{
		d3d->Release();
		d3d = nullptr;
	}
}

void gui::CreateImGui() noexcept
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ::ImGui::GetIO();
	io.IniFilename = NULL;

	ImGui::StyleColorsDark(); // Th�me de base sombre
	ImGuiStyle& style = ImGui::GetStyle(); // R�cup�rer le style

	// Modifications du style
	style.WindowRounding = 5.0f;
	style.FrameRounding = 50.0f;
	style.ScrollbarRounding = 3.0f;

	// Couleurs personnalis�es
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.05f, 0.05f, 1.0f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.72f, 0.20f, 0.20f, 1.0f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.90f, 0.30f, 0.30f, 1.0f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.60f, 0.10f, 0.10f, 1.0f);

	// Couleurs des Checkboxes
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.30f, 0.05f, 0.05f, 1.0f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.60f, 0.10f, 0.10f, 1.0f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.80f, 0.20f, 0.20f, 1.0f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.90f, 0.30f, 0.30f, 1.0f);



	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX9_Init(device);
}

void gui::DestroyImGui() noexcept
{
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void gui::BeginRender() noexcept
{
	MSG message;
	while (PeekMessage(&message, 0, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);

		if (message.message == WM_QUIT)
		{
			isRunning = !isRunning;
			return;
		}
	}

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void gui::EndRender() noexcept
{
	ImGui::EndFrame();

	device->SetRenderState(D3DRS_ZENABLE, FALSE);
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	device->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);

	device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);

	if (device->BeginScene() >= 0)
	{
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		device->EndScene();
	}

	const auto result = device->Present(0, 0, 0, 0);

	if (result == D3DERR_DEVICELOST && device->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
		ResetDevice();
}

void gui::RenderTrainerTab() noexcept
{
	if (ImGui::Checkbox("GodMode##Checkbox", &isGodModeOn))
	{
		if (isGodModeOn)
			cheat::godmodeon();
		else
			cheat::godmodeoff();
	}

	if (ImGui::Checkbox("Infinite Nade##Checkbox", &isInfNadeOn))
	{
		if (isInfNadeOn)
			cheat::infnadeon();
		else
			cheat::infnadeoff();
	}

	if (ImGui::Checkbox("Infinite Ammo##Checkbox", &isInfAmmoOn))
	{
		if (isInfAmmoOn)
			cheat::infammoon();
		else
			cheat::infammooff();
	}

	if (ImGui::Checkbox("No Recoil##Checkbox", &isNoRecoilOn))
	{
		if (isNoRecoilOn)
			cheat::norecoilon();
		else
			cheat::norecoiloff();
	}

	if (ImGui::Checkbox("Infinite Shield##Checkbox", &isInfShieldOn))
	{
		if (isInfShieldOn)
			cheat::infshieldon();
		else
			cheat::infshieldoff();
	}

	if (ImGui::Checkbox("Speed Hack##Checkbox", &isSpeedHackOn))
	{
		if (isSpeedHackOn)
			cheat::speedhackon();
		else
			cheat::speedhackoff();
	}

	if (ImGui::Checkbox("Fly##Checkbox", &isFlyOn))
	{
		if (isFlyOn)
		{
			cheat::flyon();
		}
		else
		{
			cheat::flyoff();
			cheat::noclipoff();

		}
	}

	if (isFlyOn)
	{
		ImGui::Indent();
		if (ImGui::Checkbox("Noclip##Checkbox", &isNoclipOn))
		{
			if (isNoclipOn)
			{
				cheat::noclipon();
			}
			else
			{
				cheat::noclipoff();
			}
		}
		ImGui::Unindent();
	}
}

void gui::RenderAimbotTab() noexcept {
	//if (ImGui::Checkbox("Show Info##Checkbox", &cheat::isWallHackOn)) {
	//	// Pas besoin de condition suppl�mentaire ici si getinfoon g�re d�j� isGetInfoOn
	//}

	//if (cheat::isWallHackOn) {
	//	ImGui::Begin("Entity Info", nullptr);
	//	ImGui::Text("EntityList : 0x%p", reinterpret_cast<void*>(cheat::entityL));
	//	ImGui::Text("entity: 0x%p", reinterpret_cast<void*>(cheat::entity));
	//	ImGui::Text("Head Value: %f", cheat::headValue); // Pour un int
	//	ImGui::End();
	//}
}

void gui::RenderESPTab() noexcept
{
	if (ImGui::Checkbox("Wallhack##Checkbox", &isWallHackOn))
	{
		if (isWallHackOn)
			cheat::wallhackon();
		else
			cheat::wallhackoff();
	}
}

void gui::Render() noexcept
{
	ImGui::SetNextWindowPos({ 0, 0 });
	ImGui::SetNextWindowSize({ WIDTH, HEIGHT });
	ImGui::Begin(
		"Assault cube cheat menu BY Th�o/Louis/Benjamin/Martial/Doriska",
		&isRunning,
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoSavedSettings |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoMove
	);

	if (ImGui::BeginTabBar("##Onglets", ImGuiTabBarFlags_None))
	{
		if (ImGui::BeginTabItem("Trainer"))
		{
			RenderTrainerTab();
			ImGui::EndTabItem();
		}

		/*if (ImGui::BeginTabItem("Aimbot"))
		{
			RenderAimbotTab();
			ImGui::EndTabItem();
		}*/

		if (ImGui::BeginTabItem("ESP"))
		{
			RenderESPTab();
			ImGui::EndTabItem();
		}

		ImGui::EndTabBar();
	}

	ImGui::End();

}