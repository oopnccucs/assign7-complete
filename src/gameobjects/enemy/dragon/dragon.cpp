#include "dragon.h"
#include <stdlib.h>

#include "../../../functions/AnsiPrint/AnsiPrint.h"

Dragon::Dragon(Position initialPosition, bool isLastboss): Enemy(initialPosition,30, 3, "Dragon", isLastboss) {
}

Dragon::~Dragon() {
}

Direction Dragon::nextPosition() {
    return NONE;
}

void Dragon::move(Direction direction) {
    setPosition(getPosition() + direction);
}

void Dragon::render() {
    AnsiPrint("Dn", black, red);
}
