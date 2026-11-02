#pragma once
#include "npc_entity.hpp"

class NpcSystem {
public:
    void update(NpcEntity& npc, const Position& playerPos, int tick);

private:
    static int distanceSq(const Position& a, const Position& b);

    void handleIdle(NpcEntity& npc, const Position& playerPos);
    void handlePatrol(NpcEntity& npc);
    void handleChase(NpcEntity& npc, const Position& playerPos);
    void handleAttack(NpcEntity& npc, const Position& playerPos);
    void handleFlee(NpcEntity& npc);
};
