#pragma once
#include "position.hpp"
#include "state.hpp"
#include <vector>
#include <cmath>
#include "npc_entity.hpp"

// Фиктивный игрок
struct Player {
    Position pos;
};

struct NpcConfig {
    double patrol_speed = 2.5;
    double patrol_range = 10.0;
    bool patrol_loop = true;
    double chase_speed = 4.0;
    double detection_radius = 15.0; // Радиус, на котором NPC замечает игрока
    int attack_damage = 10;
    int attack_cooldown_ms = 1000;
};

class NpcSystem {
public:
    NpcSystem();
    explicit NpcSystem(const std::string& config_path);

    const NpcConfig& config() const { return config_; }
    size_t npc_count() const { return npcs_.size(); }

    void update(double dt, const Player& player); // Теперь update знает про игрока
    void add_npc(NpcEntity entity);

    const std::vector<NpcEntity>& get_npcs_vector() const { return npcs_; }

private:
    NpcConfig config_;
    std::vector<NpcEntity> npcs_;
};
