#include "enemy.h"

Enemy::Enemy(Position initialPosition, int health, int attack, std::string name) 
    : GameObject(initialPosition, health, attack, name) {
}

Enemy::Enemy(Position initialPosition, int health, int attack, std::string name, bool isLastBoss) 
    : GameObject(initialPosition, health, attack, name), lastBoss(isLastBoss) {
}

bool Enemy::isLastBoss() {
    return lastBoss;
}

Enemy::~Enemy() {
}