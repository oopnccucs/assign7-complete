#ifndef ENEMY_H
#define ENEMY_H

#include "../../gamecore/gamestate.h"
#include "../gameobject.h"
#include <string>

class Enemy: public GameObject {
private:
    bool lastBoss = false;
public:
    Enemy(Position initialPosition, int health, int attack, std::string name);
    Enemy(Position initialPosition, int health, int attack, std::string name, bool isLastBoss);
    virtual ~Enemy();

    virtual Direction nextPosition() = 0;

    virtual void move(Direction direction) = 0;

    bool isLastBoss();
    
    virtual void render() = 0;
};

#endif