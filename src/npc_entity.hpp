#pragma once

#include "position.hpp"
#include "state.hpp"

struct NpcEntity {
    int id;
    Position pos;
    NpcState state;
    
    // точка, к которой патрулирует NPC
    Position patrol_target;
    double attack_timer = 0.0;
};