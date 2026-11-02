#pragma once
#include <string>

enum class NpcState {
    IDLE,
    PATROL,
    CHASE,
    ATTACK,
    FLEE
};

inline const char* to_cstr(NpcState s) {
    switch (s) {
        case NpcState::IDLE:   return "IDLE";
        case NpcState::PATROL: return "PATROL";
        case NpcState::CHASE:  return "CHASE";
        case NpcState::ATTACK: return "ATTACK";
        case NpcState::FLEE:   return "FLEE";
        default:               return "UNKNOWN";
    }
}
