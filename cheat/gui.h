#pragma once
#include <d3d9.h>

namespace gui
{
	// Déclarations pour GUI
	extern HWND g_hCheckbox;
	extern HWND g_hEdit;

	constexpr int WIDTH = 500;
	constexpr int HEIGHT = 300;

	inline bool isRunning = true;

	inline HWND window = nullptr;
	inline WNDCLASSEX windowClass = { };

	inline POINTS position = { };

	inline PDIRECT3D9 d3d = nullptr;
	inline LPDIRECT3DDEVICE9 device = nullptr;
	inline D3DPRESENT_PARAMETERS presentParameters = { };

	HWND GetHWindow() noexcept;

	void CreateHWindow(const char* windowName) noexcept;
	void DestroyHWindow() noexcept;

	bool CreateDevice() noexcept;
	void ResetDevice() noexcept;
	void DestroyDevice() noexcept;

	void CreateImGui() noexcept;
	void DestroyImGui() noexcept;

	void RenderESPTab() noexcept;
	void RenderAimbotTab() noexcept;
	void RenderTrainerTab() noexcept;

	void BeginRender() noexcept;
	void EndRender() noexcept;
	void Render() noexcept;

	// Déclarations pour les cheats
	extern void godmodeon() noexcept;
	extern void godmodeoff() noexcept;
	extern bool isGodModeOn;

	extern void infnadeon() noexcept;
	extern void infnadeoff() noexcept;
	extern bool isInfNadeOn;

	extern void infammoon() noexcept;
	extern void infammooff() noexcept;
	extern bool isInfAmmoOn;

	extern void infshieldoon() noexcept;
	extern void infshieldoff() noexcept;
	extern bool isInfShieldOn;

	extern void norecoilon() noexcept;
	extern void norecoiloff() noexcept;
	extern bool isNoRecoilOn;

	extern void speedhackon() noexcept;
	extern void speedhackoff() noexcept;
	extern bool isSpeedHackOn;

	extern void flyon() noexcept;
	extern void flyoff() noexcept;
	extern bool isFlyOn;

	extern void noclipon() noexcept;
	extern void noclipoff() noexcept;
	extern bool isNoclipOn;

	extern void aimboton() noexcept;
	extern void aimbotoff() noexcept;
	extern bool isAimbotOn;

	extern void wallhackon() noexcept;
	extern void wallhackoff() noexcept;
	extern bool isWallHackOn;

	extern void autoshooton() noexcept;
	extern void autoshootoff() noexcept;
	extern bool isAutoShootOn;
}

namespace overlay
{
	inline HWND window = nullptr;
	inline WNDCLASSEX windowClass = {};
	inline PDIRECT3D9 d3d = nullptr;
	inline LPDIRECT3DDEVICE9 device = nullptr;
	inline D3DPRESENT_PARAMETERS presentParameters = {};

	void CreateOverlayWindow(const char* windowName, HWND targetWindow) noexcept;
	void DestroyOverlayWindow() noexcept;

	bool CreateDevice() noexcept;
	void DestroyDevice() noexcept;

	void DrawTextOnOverlay(const char* text, int x, int y, D3DCOLOR color) noexcept;

	void BeginRender() noexcept;
	void EndRender() noexcept;
	void Render(HWND targetWindow) noexcept;
}