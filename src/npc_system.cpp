#include "npc_system.hpp"
#include <fstream>
#include <iostream>

#define USE_JSON

#ifdef USE_JSON
#include "../third_party/nlohmann/json.hpp"
using json = nlohmann::json;
#endif

NpcSystem::NpcSystem() {
    config_.patrol_speed = 2.5;
    config_.chase_speed = 4.0;
    config_.detection_radius = 15.0;
    config_.attack_damage = 10;
}

#ifdef USE_JSON
NpcSystem::NpcSystem(const std::string& config_path) {
    std::ifstream file(config_path);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open config file: " + config_path);
    }

    json j;
    file >> j;

    const auto& p = j["patrol"];
    const auto& c = j["chase"];
    const auto& a = j["attack"];

    config_.patrol_speed = p["speed"];
    config_.patrol_range = p["range"];
    config_.patrol_loop = p["loop"];
    config_.chase_speed = c["speed"];
    config_.detection_radius = c["detection_radius"];
    config_.attack_damage = a["damage"];
    config_.attack_cooldown_ms = a["cooldown_ms"];
}
#else
// Если JSON не подключён, этот конструктор не используется
NpcSystem::NpcSystem(const std::string&) {
    throw std::runtime_error("JSON support not compiled");
}
#endif

void NpcSystem::add_npc(NpcEntity entity) {
    npcs_.push_back(std::move(entity));
}

static double distance(const Position& a, const Position& b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return std::sqrt(dx * dx + dy * dy);
}

void NpcSystem::update(double dt, const Player& player) {
    for (auto& npc : npcs_) {
        double dist_to_player = distance(npc.pos, player.pos);

        if (npc.state == NpcState::PATROL) {
            // Патрулирование: двигаемся к patrol_target
            double dx = npc.patrol_target.x - npc.pos.x;
            double dy = npc.patrol_target.y - npc.pos.y;
            double dist_to_target = std::sqrt(dx*dx + dy*dy);

            if (dist_to_target < 1.0) {
                // Дошли до точки — разворачиваем цель для простого «туда-обратно»
                npc.patrol_target.x = -npc.patrol_target.x;
                npc.patrol_target.y = -npc.patrol_target.y;
            } else {
                double moveX = (dx / dist_to_target) * config_.patrol_speed * dt;
                double moveY = (dy / dist_to_target) * config_.patrol_speed * dt;
                npc.pos.x += moveX;
                npc.pos.y += moveY;
            }

            // Переход: если игрок близко — в CHASE
            if (dist_to_player < config_.detection_radius) {
                std::cout << "[NPC #" << npc.id << "] Noticed player (dist=" << dist_to_player
                          << ") -> Changing state to CHASE!\n";
                npc.state = NpcState::CHASE;
            }
        }
        else if (npc.state == NpcState::CHASE) {
            // Погоня: бежим к игроку
            if (dist_to_player > 0.001) { // защита от деления на ноль
                double moveX = ((player.pos.x - npc.pos.x) / dist_to_player) * config_.chase_speed * dt;
                double moveY = ((player.pos.y - npc.pos.y) / dist_to_player) * config_.chase_speed * dt;
                npc.pos.x += moveX;
                npc.pos.y += moveY;
            }

            // Переход: почти догнали — в ATTACK
            if (dist_to_player < 2.0) {
                std::cout << "[NPC #" << npc.id << "] Caught player (dist=" << dist_to_player
                          << ") -> Changing state to ATTACK!\n";
                npc.state = NpcState::ATTACK;
            }
        }
        else if (npc.state == NpcState::ATTACK) {
            npc.attack_timer += dt;

            // Наносим урон только раз в 1.0 сек
            if (npc.attack_timer >= 1.0) {
                std::cout << "[NPC #" << npc.id << "] Attacks player! Damage: "
                        << config_.attack_damage << "\n";
                npc.attack_timer -= 1.0;
            }
        }
    }
}
