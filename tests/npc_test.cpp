#include <gtest/gtest.h>
#include "../src/npc_system.hpp"
#include "../src/npc_entity.hpp"
#include "../src/position.hpp"
#include "../src/state.hpp"
#include <fstream>

TEST(NpcSystem, DefaultConfigValues) {
    NpcSystem system;
    EXPECT_NEAR(system.config().patrol_speed, 2.5, 1e-6);
    EXPECT_NEAR(system.config().chase_speed, 4.0, 1e-6);
    EXPECT_NEAR(system.config().detection_radius, 15.0, 1e-6);
}

TEST(NpcSystem, PatrolToChaseTransition) {
    NpcSystem system; // дефолтный конструктор
    Player player{Position{0.0, 0.0}}; // игрок прямо в точке старта

    NpcEntity npc;
    npc.id = 1;
    npc.pos = Position{0.0, 0.0};
    npc.state = NpcState::PATROL;
    npc.patrol_target = Position{10.0, 10.0};

    system.add_npc(npc);
    EXPECT_EQ(system.get_npcs_vector()[0].state, NpcState::PATROL);

    system.update(0.1, player); // дистанция 0 < detection_radius -> переход в CHASE
    EXPECT_EQ(system.get_npcs_vector()[0].state, NpcState::CHASE);
}

TEST(NpcSystem, ChaseToAttackTransition) {
    NpcSystem system;
    Player player{Position{1.0, 1.0}}; // очень близко

    NpcEntity npc;
    npc.id = 1;
    npc.pos = Position{0.0, 0.0};
    npc.state = NpcState::CHASE; // стартуем сразу в погоне
    system.add_npc(npc);

    system.update(0.1, player); // дистанция < 2.0 -> переход в ATTACK
    EXPECT_EQ(system.get_npcs_vector()[0].state, NpcState::ATTACK);
}

// Опциональный тест на JSON-конфиг (если json.hpp подключён)
TEST(NpcSystem, JsonConfigLoading) {
    // Создаём временный JSON для теста
    std::ofstream tmp("test_config.json");
    tmp << R"({"patrol":{"speed":3.5,"range":20,"loop":true},"chase":{"speed":5.0,"detection_radius":20},"attack":{"damage":15,"cooldown_ms":1000}})";
    tmp.close();

    try {
        NpcSystem system("test_config.json");
        EXPECT_NEAR(system.config().patrol_speed, 3.5, 1e-6);
        EXPECT_NEAR(system.config().detection_radius, 20.0, 1e-6);
    } catch (...) {
        FAIL() << "Failed to load JSON config";
    }

    std::remove("test_config.json"); // чистим за собой
}
