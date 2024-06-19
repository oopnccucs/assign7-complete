#ifndef SLIME_H
#define SLIME_H

#include "../enemy.h"

class Slime: public Enemy {
public:
    Slime(Position initialPosition);
    ~Slime();

    Direction nextPosition();

    void move(Direction direction);
    
    void render();
};

#endif