#include <iostream>
#include <thread>
#include <chrono>
#include "npc_entity.hpp"
#include "npc_system.hpp"
#include "state.hpp"

int main() {
    NpcEntity npc;
    Position player{5, 5}; // Игрок далеко

    NpcSystem system;

    std::cout << "Starting NPC demo (component-style architecture)...\n\n";

    for (int tick = 0; tick < 35; ++tick) {
        // Эмуляция движения игрока
        if (tick == 8)  player = {3, 0};   // Подходит ближе
        if (tick == 14) player = {0, 10};  // Резко уходит
        if (tick == 22) player = {2, 2};    // Снова приближается

        system.update(npc, player, tick);

        std::cout << "Tick " << tick
                  << ": NPC (" << npc.pos.x << ", " << npc.pos.y
                  << ") state=" << to_cstr(npc.state)
                  << " | Player (" << player.x << ", " << player.y << ")\n";

        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }

    return 0;
}
