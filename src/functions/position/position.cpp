#include "position.h"
#include "../../controller/enviroment.h"

Position::Position(int initialPositionX, int initialPositionY) {
    if(initialPositionX < 0 || initialPositionX >= GAME_WINDOW_SIZE_X) {
        initialPositionX = 0;
    }
    if(initialPositionY < 0 || initialPositionY >= GAME_WINDOW_SIZE_Y) {
        initialPositionY = 0;
    }
    positionX = initialPositionX;
    positionY = initialPositionY;
}

Position::Position() {
    positionX = 0;
    positionY = 0;
}

Position::~Position() {
    
}

Position operator+(const Position& self, const Direction direction) {
    Position newPosition = Position(self.positionX, self.positionY);
    switch(direction) {
    case UP:
        if(newPosition.positionY > 0) {
            newPosition.positionY--;
        }
        break;
    case DOWN:
        if(newPosition.positionY < GAME_WINDOW_SIZE_Y - 1) {
            newPosition.positionY++;
        }
        break;
    case LEFT:
        if(newPosition.positionX > 0) {
            newPosition.positionX--;
        }
        break;
    case RIGHT:
        if(newPosition.positionX < GAME_WINDOW_SIZE_X - 1) {
            newPosition.positionX++;
        }
        break;
    default:
        break;
    }
    return newPosition;
}

bool Position::operator==(const Position& other) {
    return positionX == other.positionX && positionY == other.positionY;
}

int Position::getX() {
    return positionX;
}

int Position::getY() {
    return positionY;
}

bool Position::isLeftEdge() {
    return positionX == 0;
}

bool Position::isRightEdge() {
    return positionX == GAME_WINDOW_SIZE_X - 1;
}

bool Position::isTopEdge() {
    return positionY == 0;
}

bool Position::isBottomEdge() {
    return positionY == GAME_WINDOW_SIZE_Y - 1;
}

void Position::setX(int positionX) {
    if(positionX < 0 || positionX >= GAME_WINDOW_SIZE_X) {
        positionX = 0;
    }
    this->positionX = positionX;
}

void Position::setY(int positionY) {
    if(positionY < 0 || positionY >= GAME_WINDOW_SIZE_Y) {
        positionY = 0;
    }
    this->positionY = positionY;
}
