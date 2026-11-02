#pragma once
#include "position.hpp"
#include "state.hpp"

struct NpcEntity {
    Position pos;
    NpcState state = NpcState::IDLE;

    // Поведенческие параметры
    int patrolRange = 4;
    int detectionDistSq = 25; // 5^2
    int attackDistSq = 4;     // 2^2

    // Вспомогательные флаги/счётчики (можно вынести в отдельный компонент)
    int patrolCounter = 0;
};
