#ifndef POSITION_H
#define POSITION_H

#include "direction.h"

using namespace DirectionState;

class Position {
private:
    int positionX;
    int positionY;
public:
    Position(int initialPositionX, int initialPositionY);
    Position();
    ~Position();

    friend Position operator+(const Position& self, const Direction direction);
    bool operator==(const Position& other);

    int getX();
    int getY();

    bool isLeftEdge();
    bool isRightEdge();
    bool isTopEdge();
    bool isBottomEdge();

    void setX(int positionX);
    void setY(int positionY);
};

#endif