#pragma once
#include "memory.h"

namespace cheat
{
    extern int updatedHealth;
    void godmodeon() noexcept;
    void godmodeoff() noexcept;
    extern bool isGodModeOn;


    extern int updatedNade;
    void infnadeon() noexcept;
    void infnadeoff() noexcept;
    extern bool isInfNadeOn;

    extern int updatedAmmo;
    extern int updatedSecAmmo;
    void infammoon() noexcept;
    void infammooff() noexcept;
    extern bool isInfAmmoOn;

    extern int updatedShield;
    void infshieldon() noexcept;
    void infshieldoff() noexcept;
    extern bool isInfShieldOn;

    void norecoilon() noexcept;
    void norecoiloff() noexcept;
    extern bool isNoRecoilOn;

    void speedhackon() noexcept;
    void speedhackoff() noexcept;
    extern bool isSpeedHackOn;

    void flyon() noexcept;
    void flyoff() noexcept;
    extern bool isFlyOn;

    void noclipon() noexcept;
    void noclipoff() noexcept;
    extern bool isNoclipOn;

    void aimboton() noexcept;
    void aimbotoff() noexcept;
    void aimbot() noexcept;
    extern bool isAimbotOn;

    void wallhackon() noexcept;
    void wallhackoff() noexcept;
    extern bool isWallHackOn;
    extern std::uintptr_t headPtr;
    extern std::uintptr_t entityL;
    extern std::uintptr_t entity;
    extern float headValue;
}