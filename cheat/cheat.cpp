    #include <Windows.h>
    #include <vector>
    #include <iostream>
    #include <CommCtrl.h>
    #include <thread>
    #include <chrono>
    #include <string>
    #include <sstream>
    #include <fstream>
    #include <cmath>

    #include "../cheat/offset.h"
    #include "../cheat/memory.h"
    #include "../cheat/cheat.h"
    #include "../cheat/gui.h"
    #include "../imgui/imgui.h"

    int initialHealth = 0;
    int initialNade = 0;
    int initialAmmo = 0;
    int initialSecAmmo = 0;
    int initialAmmosniper = 0;
    int initialAmmomachinegun = 0;
    int initialAmmoshotgun = 0;
    int initialAmmocarabine = 0;
    int initialShield = 0;
    int initialSpeed = 0;
    int initialjump = 0;

    std::atomic<bool> isNoRecoilOn = false;
    std::thread norecoilThread;
    std::atomic<bool> isInfNadeOn = false;
    std::thread infnadeThread;
    std::atomic<bool> isInfAmmoOn = false;
    std::thread infammoThread;
    std::atomic<bool> isInfShieldOn = false;
    std::thread infshieldThread;
    std::atomic<bool> isGodModeOn = false;
    std::thread godmodeThread;
    std::atomic<bool> isSpeedHackOn = false;
    std::thread speedhackThread;
    std::atomic<bool> isWallHackOn = false;
    std::thread wallhackThread;
    std::atomic<bool> isFlyOn = false;
    std::thread flyThread;
    std::atomic<bool> isNoclipOn = false;
    std::thread noclipThread;
    std::atomic<bool> isAimbotOn = false;
    std::thread aimbotThread;
    std::atomic<bool> isAutoShootOn = false;
    std::thread autoshootThread;
    std::atomic<bool> isOneShotOn = false;
    std::thread oneshotThread;

    void cheat::godmodeon() noexcept
    {
        if (isGodModeOn)
            return;

        auto& memory = getMemory();
        const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
        const auto localPlayerPtr = memory.Read<std::uintptr_t>(moduleBase + localPlayer);
        const auto healthAddress = localPlayerPtr + m_iHealth;

        isGodModeOn = true;

        godmodeThread = std::thread([&memory, healthAddress]() {
            while (isGodModeOn) {
                if (!isGodModeOn) {
                    break;
                }
                memory.Write<int>(healthAddress, 100);
            }
            });
    }

    void cheat::godmodeoff() noexcept
    {
        if (!isGodModeOn)
            return;

        isGodModeOn = false;

        if (godmodeThread.joinable())
            godmodeThread.join();
    }

    void cheat::infnadeon() noexcept
    {
        if (isInfNadeOn)
            return;

        auto& memory = getMemory();
        const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
        const auto localPlayerPtr = memory.Read<std::uintptr_t>(moduleBase + localPlayer);
        const auto nadesAddress = localPlayerPtr + m_Nades;

        isInfNadeOn = true;

        infnadeThread = std::thread([&memory, nadesAddress]() {
            while (isInfNadeOn) {
                if (!isInfNadeOn) {
                    break;
                }
                memory.Write<int>(nadesAddress, 10);
            }
            });
    }

    void cheat::infnadeoff() noexcept
    {
        if (!isInfNadeOn)
            return;

        isInfNadeOn = false;

        if (infnadeThread.joinable())
            infnadeThread.join();
    }

    void cheat::infammoon() noexcept
    {
        if (isInfAmmoOn)
            return;

        auto& memory = getMemory();
        const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
        const auto localPlayerPtr = memory.Read<std::uintptr_t>(moduleBase + localPlayer);
        const auto ammoAddress = localPlayerPtr + m_Ammorifle;
        const auto secAmmoAddress = localPlayerPtr + m_SecAmmo;
        const auto sniperAmmoAddress = localPlayerPtr + m_Ammosniper;
        const auto machinegunAmmoAddress = localPlayerPtr + m_Ammomachinegun;
        const auto shotgunAmmoAddress = localPlayerPtr + m_Ammoshotgun;
        const auto carabineAmmoAddress = localPlayerPtr + m_Ammocarabine;

        isInfAmmoOn = true;

        infammoThread = std::thread([&memory, ammoAddress, secAmmoAddress, sniperAmmoAddress, machinegunAmmoAddress, shotgunAmmoAddress, carabineAmmoAddress]() {
            while (isInfAmmoOn) {
                if (!isInfAmmoOn) {
                    break;
                }
                memory.Write<int>(ammoAddress, 20);
                memory.Write<int>(secAmmoAddress, 20);
                memory.Write<int>(sniperAmmoAddress, 20);
                memory.Write<int>(machinegunAmmoAddress, 20);
                memory.Write<int>(shotgunAmmoAddress, 20);
                memory.Write<int>(carabineAmmoAddress, 20);
            }
            });
    }

    void cheat::infammooff() noexcept
    {
        if (!isInfAmmoOn)
            return;


        isInfAmmoOn = false;

        if (infammoThread.joinable())
            infammoThread.join();
    }

    void cheat::infshieldon() noexcept
    {
        if (isInfShieldOn)
            return;

        auto& memory = getMemory();
        const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
        const auto localPlayerPtr = memory.Read<std::uintptr_t>(moduleBase + localPlayer);
        const auto shieldAddress = localPlayerPtr + m_shield;

        isInfShieldOn = true;

        infshieldThread = std::thread([&memory, shieldAddress]() {
            while (isInfShieldOn) {
                if (!isInfShieldOn) {
                    break;
                }
                memory.Write<int>(shieldAddress, 100);
            }
            });
    }

    void cheat::infshieldoff() noexcept
    {
        if (!isInfShieldOn)
            return;

        isInfShieldOn = false;

        if (infshieldThread.joinable())
            infshieldThread.join();
    }

    void cheat::speedhackon() noexcept
    {
        if (isSpeedHackOn)
            return;

        auto& memory = getMemory();
        const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
        const auto localPlayerPtr = memory.Read<std::uintptr_t>(moduleBase + localPlayer);
        const auto speedAddress = localPlayerPtr + m_Speed;

        isSpeedHackOn = true;

        speedhackThread = std::thread([&memory, speedAddress]() {
            while (isSpeedHackOn) {
                if (!isSpeedHackOn) {
                    break;
                }
                if (GetAsyncKeyState('Z') & 0x8000) {
                    memory.Write<int>(speedAddress, 3);
                }
            }
            });
    }

    void cheat::speedhackoff() noexcept {
        if (!isSpeedHackOn)
            return;

        isSpeedHackOn = false;

        if (speedhackThread.joinable())
            speedhackThread.join();

    }

    void cheat::norecoilon() noexcept
    {
        if (isNoRecoilOn)
            return;

        auto& memory = getMemory();
        const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
        const auto localPlayerPtr = memory.Read<std::uintptr_t>(moduleBase + localPlayer);
        const auto RecoilAddress = localPlayerPtr + m_NoRecoil;
        const int recoilValue = 100;

        isNoRecoilOn = true;

        norecoilThread = std::thread([&memory, RecoilAddress, recoilValue]() {
            while (isNoRecoilOn) {
                if (!isNoRecoilOn)
                    break;
                memory.Write(RecoilAddress, recoilValue);
            }
            });
    }

    void cheat::norecoiloff() noexcept
    {
        if (!isNoRecoilOn)
            return;

        isNoRecoilOn = false;

        if (norecoilThread.joinable())
            norecoilThread.join();
    }

    void cheat::flyon() noexcept {
        if (isFlyOn)
            return;
        auto& memory = getMemory();
        const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
        const auto localPlayerPtr = memory.Read<std::uintptr_t>(moduleBase + localPlayer);
        const auto jumpAddress = localPlayerPtr + m_superjump;

        isFlyOn = true;
        
        flyThread = std::thread([&memory, jumpAddress]() {
            while (isFlyOn) {
                if (!isFlyOn) {
                    break;
                }
                else if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
                    memory.Write<int>(jumpAddress, -600);
                }
                else if (GetAsyncKeyState(VK_LCONTROL) & 0x8000) {
                    memory.Write<int>(jumpAddress, 200);
                }
                else {
                    memory.Write<int>(jumpAddress, -290);
                }
            }
            });
    }

    void cheat::flyoff() noexcept {
        if (!isFlyOn)
            return;

        isFlyOn = false;
        
        if (flyThread.joinable())
            flyThread.join();
    }

    void cheat::noclipon() noexcept {
        if (isNoclipOn)
            return;
        auto& memory = getMemory();
        const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
        const auto localPlayerPtr = memory.Read<std::uintptr_t>(moduleBase + localPlayer);
        const auto collisionAddress = localPlayerPtr + m_Collision;
        isNoclipOn = true;
        noclipThread = std::thread([&memory, collisionAddress]() {
            while (isNoclipOn) {
                if (!isNoclipOn) {
                    break;
                }
                memory.Write<float>(collisionAddress, -1.0f);
            }
        });
    }

    void cheat::noclipoff() noexcept {
        if (!isNoclipOn)
            return;
        
        isNoclipOn = false;

        if (noclipThread.joinable())
            noclipThread.join();

        auto& memory = getMemory();
        const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
        const auto localPlayerPtr = memory.Read<std::uintptr_t>(moduleBase + localPlayer);
        const auto collisionAddress = localPlayerPtr + m_Collision;

        memory.Write<float>(collisionAddress, 1.1f);
    }

    void cheat::aimbot() noexcept {
        auto& memory = getMemory();
        const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
        const auto localPlayerPtr = memory.Read<std::uintptr_t>(moduleBase + localPlayer);

        float localPlayerPos[3];
        localPlayerPos[0] = memory.Read<float>(localPlayerPtr + playerHead_XPos);
        localPlayerPos[1] = memory.Read<float>(localPlayerPtr + playerBody_YPos);
        localPlayerPos[2] = memory.Read<float>(localPlayerPtr + playerBody_ZPos);

        float closestDistance = FLT_MAX;
        std::uintptr_t closestEnemy = 0;

        const auto entityListPtr = memory.Read<std::uintptr_t>(moduleBase + entityList);
        const auto NumberOfPlayer = memory.Read<std::uintptr_t>(numberOfPlayer);
        for (int i = 0; i < NumberOfPlayer; ++i) {
            const auto enemyPtr = memory.Read<std::uintptr_t>(entityListPtr + i * sizeof(std::uintptr_t));
            if (enemyPtr == 0 || enemyPtr == localPlayerPtr) continue;
            int TeamNum_Player = memory.Read<int>(localPlayerPtr + m_TeamNum);

            int playerAlive = memory.Read<int>(enemyPtr + playerIsAlive);
            int TeamNum_Enemy = memory.Read<int>(enemyPtr + m_TeamNum);

            if (playerAlive == 1) continue;
            if (TeamNum_Enemy == TeamNum_Player) continue;

            float enemyPos[3];
            enemyPos[0] = memory.Read<float>(enemyPtr + playerHead_XPos);
            enemyPos[1] = memory.Read<float>(enemyPtr + playerBody_YPos);
            enemyPos[2] = memory.Read<float>(enemyPtr + playerBody_ZPos);

            float deltaX = enemyPos[0] - localPlayerPos[0];
            float deltaY = enemyPos[1] - localPlayerPos[1];
            float deltaZ = enemyPos[2] - localPlayerPos[2];
            float distance = std::sqrt(deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ);

            if (distance < closestDistance) {
                closestDistance = distance;
                closestEnemy = enemyPtr;
            }
        }

        if (closestEnemy != 0) {
            float enemyPos[3];
            enemyPos[0] = memory.Read<float>(closestEnemy + playerHead_XPos);
            enemyPos[1] = memory.Read<float>(closestEnemy + playerBody_YPos);
            enemyPos[2] = memory.Read<float>(closestEnemy + playerBody_ZPos);

            float deltaX = enemyPos[0] - localPlayerPos[0];
            float deltaY = enemyPos[1] - localPlayerPos[1];
            float deltaZ = enemyPos[2] - localPlayerPos[2];

            float hypotenuse = std::sqrt(deltaX * deltaX + deltaY * deltaY);
            float pitch = std::atan2(deltaZ, hypotenuse) * (180.0f / 3.14159265358979323846f);
            float yaw = std::atan2(deltaY, -deltaX) * (180.0f / 3.14159265358979323846f);

            memory.Write<float>(localPlayerPtr + m_ViewAngleX, pitch);
            memory.Write<float>(localPlayerPtr + m_ViewAngleY, yaw);
        }
    }

    void cheat::aimboton() noexcept {
        if (isAimbotOn)
            return;

        isAimbotOn = true;

        aimbotThread = std::thread([&]() {
            while (isAimbotOn) {
                if (!isAimbotOn) {
                    break;
                }
                if (GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
                    aimbot();
                }
            }
            });
    }

    void cheat::aimbotoff() noexcept {
        if (!isAimbotOn)
            return;

        isAimbotOn = false;

        if (aimbotThread.joinable())
            aimbotThread.join();
    }

    void cheat::autoshooton() noexcept
    {
        if (isAutoShootOn)
            return;

        auto& memory = getMemory();
        const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
        const auto localPlayerPtr = memory.Read<std::uintptr_t>(moduleBase + localPlayer);
        const auto AutoShootAddress = localPlayerPtr + m_AutoShoot;

        isAutoShootOn = true;

        autoshootThread = std::thread([&memory, AutoShootAddress]() {
            while (isAutoShootOn) {
                if (!isAutoShootOn) {
                    break;
                }
                memory.Write<int>(AutoShootAddress, 1);
            }
            });
    }

    void cheat::autoshootoff() noexcept
    {
        if (!isAutoShootOn)
            return;

        isAutoShootOn = false;

    }

    // En suspend

    void cheat::wallhackon() noexcept
    {
        if (isWallHackOn)
            return;

        isWallHackOn = true;

        HWND targetWindow = FindWindow(NULL, "AssaultCube");
        if (!targetWindow) {
            isWallHackOn = false;
            return;
        }

        wallhackThread = std::thread([targetWindow]() {
            while (isWallHackOn) {
                overlay::Render(targetWindow);
            }
         });
    }

    void cheat::wallhackoff() noexcept
    {
        if (!isWallHackOn)
            overlay::BeginRender();
        isWallHackOn = false;

        if (wallhackThread.joinable()) {
            wallhackThread.join();
        }
    }

    void cheat::oneshotenemyon() noexcept
    {
        if (isOneShotOn)
            return;

        auto& memory = getMemory();
        const auto moduleBase = memory.GetModuleAddress("ac_client.exe");
        const auto localPlayerPtr = memory.Read<std::uintptr_t>(moduleBase + localPlayer);

        isOneShotOn = true;

        oneshotThread = std::thread([&memory, moduleBase, localPlayerPtr]() {
            const auto entityListPtr = memory.Read<std::uintptr_t>(moduleBase + entityList);
            const auto numberOfPlayers = memory.Read<std::uintptr_t>(numberOfPlayer);

            while (isOneShotOn) {
                for (int i = 0; i < numberOfPlayers; ++i) {
                    const auto enemyPtr = memory.Read<std::uintptr_t>(entityListPtr + i * sizeof(std::uintptr_t));
                    if (enemyPtr == 0 || enemyPtr == localPlayerPtr) continue;

                    const int playerAlive = memory.Read<int>(enemyPtr + playerIsAlive);
                    const int teamNumPlayer = memory.Read<int>(localPlayerPtr + m_TeamNum);
                    const int teamNumEnemy = memory.Read<int>(enemyPtr + m_TeamNum);

                    if (playerAlive == 1 || teamNumEnemy == teamNumPlayer) continue;

                    const auto healthAddr = enemyPtr + m_iHealth;
                    memory.Write<int>(healthAddr, 1);
                }
            }
            });
    }

    void cheat::oneshotenemyoff() noexcept
    {
        if (!isOneShotOn)
            return;

        isOneShotOn = false;

        if (oneshotThread.joinable())
            oneshotThread.join();
    }