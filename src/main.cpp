#include <iostream>
#include "npc_system.hpp"

int main() {
    try {
        // Вариант 1 (демо): быстрый запуск без JSON
        // NpcSystem system;

        // Вариант 2 (с конфигом): раскомментируй, если папка data и json на месте
        NpcSystem system("data/npc_config.json");

        Player player{Position{15.0, 15.0}};

        NpcEntity npc1;
        npc1.id = 1;
        npc1.pos = Position{0.0, 0.0};
        npc1.state = NpcState::PATROL;
        npc1.patrol_target = Position{50.0, 50.0};
        system.add_npc(npc1);

        NpcEntity npc2;
        npc2.id = 2;
        npc2.pos = Position{-10.0, -10.0};
        npc2.state = NpcState::PATROL;
        npc2.patrol_target = Position{-30.0, -30.0};
        system.add_npc(npc2);

        std::cout << "Demo started. Player at (" << player.pos.x << ", " << player.pos.y << ")\n";
        std::cout << "Config patrol_speed: " << system.config().patrol_speed << "\n\n";

        for (int i = 0; i < 100; ++i) {
            double dt = 0.1;
            system.update(dt, player);

            // Вывод позиции NPC для наглядности
            if (!system.get_npcs_vector().empty()) {
                for(auto& npc : system.get_npcs_vector()) {
                    std::cout << "[NPC #" << npc.id << "] Pos=(" << npc.pos.x << "," << npc.pos.y
                        << ") | State=" << to_cstr(npc.state) << "\n";
                }
                
            }

            std::cout << "--- Frame " << i + 1 << " ---\n";
        }


        std::cout << "\nDemo finished successfully.\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
