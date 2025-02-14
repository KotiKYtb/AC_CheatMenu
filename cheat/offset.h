#pragma once

#include <stdint.h>

constexpr auto playerBody_XPos = 0x000038;
constexpr auto playerBody_YPos = 0x000034;
constexpr auto playerBody_ZPos = 0x00003C;
constexpr auto playerHead_XPos = 0x000008;
constexpr auto playerHead_YPos = 0x000004;
constexpr auto playerHead_ZPos = 0x00000C;

constexpr auto m_Nades = 0x000158;
constexpr auto m_Ammorifle = 0x000150;
constexpr auto m_SecAmmo = 0x00013C;
constexpr auto m_Ammosniper = 0x00014C;
constexpr auto m_Ammomachinegun = 0x000148;
constexpr auto m_Ammoshotgun = 0x000144;
constexpr auto m_Ammocarabine = 0x000140;
constexpr auto m_NoRecoil = 0x00004C;
constexpr auto m_AutoShoot = 0x000224;

constexpr auto m_shield = 0x0000FC;
constexpr auto m_Speed = 0x000080;
constexpr auto m_superjump = 0x000054;
constexpr auto m_Collision = 0x000058;

constexpr auto localPlayer = 0x10F4F4;
constexpr auto entityList = 0x10F4F8;

constexpr auto m_iHealth = 0x0000F8;
constexpr auto m_iName = 0x000225;
constexpr auto m_TeamNum = 0x00032C;

constexpr auto m_ViewAngleY = 0x000040;
constexpr auto m_ViewAngleX = 0x000044;

constexpr auto numberOfPlayer = 0x50f500;
constexpr auto playerIsAlive = 0x000338;

constexpr auto viewMatrixOff = 0x57DFD0;
