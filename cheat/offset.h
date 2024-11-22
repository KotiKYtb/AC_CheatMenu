#pragma once

#include <stdint.h>

// Lists
constexpr auto localPlayer = 0x109B74;
constexpr auto entityList = 0x10F4F8;

constexpr auto m_iHealth = 0x0000F8;
constexpr auto m_iName = 0x205;
constexpr auto m_Armor = 0x03112D64;
constexpr auto m_XCoord = 0x28;
constexpr auto m_YCoord = 0x2C;	
constexpr auto m_ZCoord = 0x30;
constexpr auto m_ViewangleY = 0x44;
constexpr auto m_ViewAngleX = 0x40;
constexpr auto m_iShotAmount = 0x180;

constexpr auto m_vecOrigin = 0x28;
constexpr auto vec3_head = 0x4;
constexpr auto iTeamNum = 0x30C;
constexpr auto dwViewMatrix = 0x501AE8;

// ammo nade function recoil
constexpr auto m_Nades = 0x158;
constexpr auto m_Ammo = 0x150;
constexpr auto m_SecAmmo = 0x13C;
constexpr auto m_recoil1 = 0x44;
constexpr auto m_shield = 0xFC;
constexpr auto m_Speed = 0x80;

// Hacks
constexpr auto rapidFire = 0x164;

constexpr auto h_ShowSpeed = 0x50F288;