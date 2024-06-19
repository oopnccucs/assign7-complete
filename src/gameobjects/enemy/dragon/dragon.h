#ifndef DRAGON_H
#define DRAGON_H

#include "../enemy.h"

class Dragon: public Enemy {
public:
    Dragon(Position initialPosition, bool isLastBoss = false);
    ~Dragon();

    Direction nextPosition();

    void move(Direction direction);
    
    void render();
};

#endif