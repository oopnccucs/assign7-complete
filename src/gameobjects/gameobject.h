#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "../functions/position/position.h"
#include "../functions/position/direction.h"
#include <string>

using namespace DirectionState;

class GameObject {
private:
    Position position;

    int health;
    int maxHealth;

    std::string name;

    int attack;
public:
    GameObject(Position initialPosition, int health, int attack, std::string name);

    virtual ~GameObject();

    Position getPosition();

    void setPosition(Position position);

    int getHealth();

    int getMaxHealth();

    int getAttack();

    void hurt(int damage);

    std::string getName();

    virtual void render() = 0;
};

#endif