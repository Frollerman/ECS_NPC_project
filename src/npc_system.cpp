#include "npc_system.hpp"

int NpcSystem::distanceSq(const Position& a, const Position& b) {
    const int dx = a.x - b.x;
    const int dy = a.y - b.y;
    return dx * dx + dy * dy;
}

void NpcSystem::handleIdle(NpcEntity& npc, const Position& playerPos) {
    if (distanceSq(npc.pos, playerPos) <= npc.detectionDistSq) {
        npc.state = NpcState::CHASE;
        return;
    }
    // Иногда начинаем патрулировать
    if ((npc.patrolCounter++ % 12) == 0) {
        npc.state = NpcState::PATROL;
    }
}

void NpcSystem::handlePatrol(NpcEntity& npc) {
    // Простой «зигзаг» по X в пределах patrolRange
    if (npc.pos.x < npc.patrolRange) {
        ++npc.pos.x;
    } else {
        npc.pos.x = 0;
    }

    // Если игрок близко — переключаемся
    // (в реальном коде проверка должна быть в update, но для наглядности продублируем)
}

void NpcSystem::handleChase(NpcEntity& npc, const Position& playerPos) {
    const int dx = playerPos.x - npc.pos.x;
    const int dy = playerPos.y - npc.pos.y;

    if (dx != 0) npc.pos.x += (dx > 0 ? 1 : -1);
    if (dy != 0) npc.pos.y += (dy > 0 ? 1 : -1);

    const int distSq = distanceSq(npc.pos, playerPos);
    if (distSq <= npc.attackDistSq) {
        npc.state = NpcState::ATTACK;
    }
}

void NpcSystem::handleAttack(NpcEntity& npc, const Position& playerPos) {
    const int distSq = distanceSq(npc.pos, playerPos);
    // Если игрок убежал — снова в CHASE
    if (distSq > npc.detectionDistSq) {
        npc.state = NpcState::CHASE;
    }
    // Иначе держим состояние ATTACK
}

void NpcSystem::handleFlee(NpcEntity& npc) {
    // Можно добавить логику убегания, пока оставим заглушкой
}

void NpcSystem::update(NpcEntity& npc, const Position& playerPos, int /*tick*/) {
    switch (npc.state) {
        case NpcState::IDLE:
            handleIdle(npc, playerPos);
            break;
        case NpcState::PATROL:
            handlePatrol(npc);
            if (distanceSq(npc.pos, playerPos) <= npc.detectionDistSq) {
                npc.state = NpcState::CHASE;
            }
            break;
        case NpcState::CHASE:
            handleChase(npc, playerPos);
            break;
        case NpcState::ATTACK:
            handleAttack(npc, playerPos);
            break;
        case NpcState::FLEE:
            handleFlee(npc);
            break;
    }
}
