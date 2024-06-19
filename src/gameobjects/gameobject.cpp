#include "gameobject.h"

GameObject::GameObject(Position initialPosition, int health, int attack, std::string name) 
    : maxHealth(health), attack(attack) {
    position = initialPosition;
    this->health = health;
    this->name = name;
}

GameObject::~GameObject() {
}

Position GameObject::getPosition() {
    return position;
}

void GameObject::setPosition(Position position) {
    this->position = position;
}

int GameObject::getHealth() {
    return health;
}

int GameObject::getMaxHealth() {
    return maxHealth;
}

int GameObject::getAttack() {
    return attack;
}

void GameObject::hurt(int damage) {
    health = health - damage > 0 ? health - damage <= maxHealth ? health - damage : maxHealth : 0;
}

std::string GameObject::getName() {
    return name;
}