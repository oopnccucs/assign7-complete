#include "slime.h"
#include <stdlib.h>

#include "../../../functions/AnsiPrint/AnsiPrint.h"

Slime::Slime(Position initialPosition): Enemy(initialPosition, 5, 1, "Slime") {
}

Slime::~Slime() {
}

Direction Slime::nextPosition() {
    int random = rand() % 4;
    switch (random) {
        case 0:
            return DOWN;
        case 1:
            return UP;
        case 2:
            return LEFT;
        case 3:
            return RIGHT;
    }
    return NONE;
}

void Slime::move(Direction direction) {
    setPosition(getPosition() + direction);
}

void Slime::render() {
    AnsiPrint("==", yellow, green);
}
