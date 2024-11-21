    #include <Windows.h>
    #include <vector>
    #include <iostream>
    #include <CommCtrl.h>
    #include <thread>
    #include <chrono>

    #include "../cheat/offset.h"
    #include "../cheat/memory.h"
    #include "../cheat/cheat.h"


    int cheat::updatedHealth = 100;
    int cheat::updatedNade = 10;
    int cheat::updatedAmmo = 20;
    int cheat::updatedSecAmmo = 20;
    int cheat::updatedShield = 25;
    int initialHealth = 0;
    int initialNade = 0;
    int initialAmmo = 0;
    int initialSecAmmo = 0;
    int initialShield = 0;
    int initialSpeed = 0;
    //float initialRecoil = 0.0f;
    bool cheat::isNoRecoilOn = false;
    bool cheat::isInfNadeOn = false;
    bool cheat::isInfAmmoOn = false;
    bool cheat::isInfShieldOn = false;
    bool cheat::isGodModeOn = false;
    bool cheat::isGetInfoOn = false;
    bool cheat::isSpeedHackOn = false;
    std::uintptr_t cheat::headPtr = 0;
    std::uintptr_t cheat::entityL = 0;
    std::uintptr_t cheat::entity = 0;
    float cheat::headValue = 0.0f;

    void cheat::godmodeon() noexcept
    {
        if (isGodModeOn)
            return;

        auto& memory = getMemory();
        const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
        const auto localPlayerPtr = memory.Read<std::uintptr_t>(moduleBase + localPlayer);
        const auto healthAddress = localPlayerPtr + m_iHealth;

        initialHealth = memory.Read<int>(healthAddress);
        isGodModeOn = true;

        std::thread([&memory, healthAddress]() {
            while (isGodModeOn) {
                memory.Write<int>(healthAddress, 100);
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }
            }).detach();
    }

    void cheat::godmodeoff() noexcept
    {
        if (!isGodModeOn)
            return;

        auto& memory = getMemory();
        const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
        const auto localPlayerPtr = memory.Read<std::uintptr_t>(moduleBase + localPlayer);
        const auto healthAddress = localPlayerPtr + m_iHealth;

        isGodModeOn = false;

        memory.Write<int>(healthAddress, initialHealth);
    }

    void cheat::infnadeon() noexcept
    {
        if (isInfNadeOn)
            return;

        auto& memory = getMemory();
        const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
        const auto localPlayerPtr = memory.Read<std::uintptr_t>(moduleBase + localPlayer);
        const auto nadesAddress = localPlayerPtr + m_Nades;

        initialNade = memory.Read<int>(nadesAddress);
        isInfNadeOn = true;

        std::thread([&memory, nadesAddress]() {
            while (isInfNadeOn) {
                memory.Write<int>(nadesAddress, 10);
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }
            }).detach();
    }

    void cheat::infnadeoff() noexcept
    {
        if (!isInfNadeOn)
            return;

        auto& memory = getMemory();
        const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
        const auto localPlayerPtr = memory.Read<std::uintptr_t>(moduleBase + localPlayer);
        const auto nadesAddress = localPlayerPtr + m_Nades;

        isInfNadeOn = false;

        memory.Write<int>(nadesAddress, initialNade);
    }

    void cheat::infammoon() noexcept
    {
        if (isInfAmmoOn)
            return;

        auto& memory = getMemory();
        const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
        const auto localPlayerPtr = memory.Read<std::uintptr_t>(moduleBase + localPlayer);
        const auto ammoAddress = localPlayerPtr + m_Ammo;
        const auto secAmmoAddress = localPlayerPtr + m_SecAmmo;

        initialAmmo = memory.Read<int>(ammoAddress);
        initialSecAmmo = memory.Read<int>(secAmmoAddress);
        isInfAmmoOn = true;

        std::thread([&memory, ammoAddress, secAmmoAddress]() {
            while (isInfAmmoOn) {
                memory.Write<int>(ammoAddress, 20);      // Munitions principales infinies
                memory.Write<int>(secAmmoAddress, 20);  // Munitions secondaires infinies
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }
            }).detach();
    }

    void cheat::infammooff() noexcept
    {
        if (!isInfAmmoOn)
            return;

        auto& memory = getMemory();
        const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
        const auto localPlayerPtr = memory.Read<std::uintptr_t>(moduleBase + localPlayer);
        const auto ammoAddress = localPlayerPtr + m_Ammo;
        const auto secAmmoAddress = localPlayerPtr + m_SecAmmo;

        isInfAmmoOn = false;

        // Rétablir les valeurs originales des munitions
        memory.Write<int>(ammoAddress, initialAmmo);
        memory.Write<int>(secAmmoAddress, initialSecAmmo);
    }

    void cheat::infshieldon() noexcept
    {
        if (isInfShieldOn)
            return;

        auto& memory = getMemory();
        const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
        const auto localPlayerPtr = memory.Read<std::uintptr_t>(moduleBase + localPlayer);
        const auto shieldAddress = localPlayerPtr + m_shield;

        int shieldValue = memory.Read<int>(shieldAddress);

        initialShield = memory.Read<int>(shieldAddress);
        isInfShieldOn = true;

        std::thread([&memory, shieldAddress]() {
            while (isInfShieldOn) {
                memory.Write<int>(shieldAddress, 20);
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }
            }).detach();

        /*char buffer[100];
        sprintf_s(buffer, sizeof(buffer), "shieldAddress: %p\nValue at address: %d",
            (void*)TestAdress, testvalue);

        MessageBoxA(NULL, buffer, "Debug", MB_OK);*/
    }

    void cheat::infshieldoff() noexcept
    {
        if (!isInfShieldOn)
            return;

        auto& memory = getMemory();
        const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
        const auto localPlayerPtr = memory.Read<std::uintptr_t>(moduleBase + localPlayer);
        const auto shieldAddress = localPlayerPtr + m_shield;

        isInfShieldOn = false;

        memory.Write<int>(shieldAddress, initialShield);
    }

    void cheat::speedhackon() noexcept
    {
        if (isSpeedHackOn)
            return;

        auto& memory = getMemory();
        const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
        const auto localPlayerPtr = memory.Read<std::uintptr_t>(moduleBase + localPlayer);
        const auto speedAddress = localPlayerPtr + m_Speed;

        initialSpeed = memory.Read<int>(speedAddress);
        isSpeedHackOn = true;

        std::thread([&memory, speedAddress]() {
            while (isSpeedHackOn) {
                if (GetAsyncKeyState('Z') & 0x8000) {
                    memory.Write<int>(speedAddress, 3);
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                }
            }
        }).detach();
    }

    void cheat::speedhackoff() noexcept
    {
        if (!isSpeedHackOn)
            return;

        auto& memory = getMemory();
        const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
        const auto localPlayerPtr = memory.Read<std::uintptr_t>(moduleBase + localPlayer);
        const auto speedAddress = localPlayerPtr + m_Speed;

        isSpeedHackOn = false;

        std::thread([&memory, speedAddress]() {
            while (isSpeedHackOn) {
                if (GetAsyncKeyState('Z') & 0x8000) {
                    memory.Write<int>(speedAddress, 1);
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                }
            }
        }).detach();
    }

    void cheat::norecoilon() noexcept
    {
        if (isNoRecoilOn)
            return;

        /*auto& memory = getMemory();
        const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
        const auto localPlayerPtr = memory.Read<std::uintptr_t>(moduleBase + localPlayer);
        const auto recoilAddress = localPlayerPtr + m_ViewAngleHeight;

        initialRecoil = memory.Read<float>(recoilAddress);
        isNoRecoilOn = true;

        std::thread([&memory, recoilAddress]() {
            while (isNoRecoilOn) {
                memory.Write<float>(recoilAddress, initialRecoil - 1.0f);
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }
            }).detach();*/
    }

    void cheat::norecoiloff() noexcept
    {
        if (!isNoRecoilOn)
            return;

        isNoRecoilOn = false;
    }

    void cheat::getinfoon() noexcept {
        // Implémentation pour get info
    }