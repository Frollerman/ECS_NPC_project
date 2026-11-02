#include <gtest/gtest.h>
#include "../src/npc_entity.hpp"
#include "../src/npc_system.hpp"

// Вспомогательная функция для сравнения позиций
bool posEqual(const Position& a, const Position& b) {
    return a.x == b.x && a.y == b.y;
}

TEST(NpcStateTransitions, IdleToChaseWhenPlayerClose) {
    NpcEntity npc;
    Position player{3, 0}; // близко (в пределах detectionDistSq = 25)
    NpcSystem system;

    // Изначально IDLE
    EXPECT_EQ(npc.state, NpcState::IDLE);

    system.update(npc, player, 0);

    // Должен перейти в CHASE
    EXPECT_EQ(npc.state, NpcState::CHASE);
}

TEST(NpcStateTransitions, ChaseToAttackWhenCloseEnough) {
    NpcEntity npc;
    npc.state = NpcState::CHASE;
    npc.pos = {0, 0};

    Position player{1, 1}; // дистанция ~1.4, квадрат = 2, меньше attackDistSq=4
    NpcSystem system;

    system.update(npc, player, 0);

    EXPECT_EQ(npc.state, NpcState::ATTACK);
}

TEST(NpcMovement, ChaseMovesTowardPlayer) {
    NpcEntity npc;
    npc.state = NpcState::CHASE;
    npc.pos = {0, 0};

    Position player{3, 4}; // игрок справа-вверху
    NpcSystem system;

    system.update(npc, player, 0);

    // После одного тика NPC должен сделать шаг: x+1 и/или y+1
    EXPECT_TRUE(npc.pos.x == 1 || npc.pos.x == 0); // может остаться, если dx=0
    EXPECT_TRUE(npc.pos.y == 1 || npc.pos.y == 0);
    
    // Но в нашем коде dx!=0 и dy!=0, поэтому он точно сделает шаг по обеим осям
    EXPECT_EQ(npc.pos.x, 1);
    EXPECT_EQ(npc.pos.y, 1);
}

TEST(NpcMovement, PatrolMovesWithinRange) {
    NpcEntity npc;
    npc.state = NpcState::PATROL;
    npc.patrolRange = 4;
    npc.pos = {3, 0}; // почти на границе

    Position dummyPlayer{10, 10}; // далеко, чтобы не триггерить CHASE
    NpcSystem system;

    system.update(npc, dummyPlayer, 0);

    // По нашей логике: если x < patrolRange, то x++, иначе x=0.
    // Здесь x=3 < 4 → x станет 4
    EXPECT_EQ(npc.pos.x, 4);
}

TEST(NpcMovement, PatrolWrapsAround) {
    NpcEntity npc;
    npc.state = NpcState::PATROL;
    npc.patrolRange = 4;
    npc.pos = {4, 0}; // ровно на границе (или чуть больше)

    Position dummyPlayer{10, 10};
    NpcSystem system;

    system.update(npc, dummyPlayer, 0);

    // В нашей реализации: если x >= patrolRange, сбрасываем в 0
    EXPECT_EQ(npc.pos.x, 0);
}

TEST(NpcStateTransitions, AttackReturnsToChaseIfPlayerRunsAway) {
    NpcEntity npc;
    npc.state = NpcState::ATTACK;
    npc.pos = {2, 2};

    Position player{10, 10}; // очень далеко
    NpcSystem system;

    system.update(npc, player, 0);

    EXPECT_EQ(npc.state, NpcState::CHASE);
}
