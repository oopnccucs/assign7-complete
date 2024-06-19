#include "player.h"
#include "../../controller/enviroment.h"
#include "../../functions/AnsiPrint/AnsiPrint.h"

Player::Player(Position initialPosition): GameObject(initialPosition, 20, 2, "Player") {
}

Player::~Player() {
    
}

MoveState Player::move(Direction direction) {
    if(getPosition().isLeftEdge() && direction == LEFT) {
        return LEFTROOM;
    }

    if(getPosition().isRightEdge() && direction == RIGHT) {
        return RIGHTROOM;
    }

    setPosition(getPosition() + direction);
    return MOVE;
}

int Player::getHealPower() {
    return healPower;
}

void Player::heal(int amount) {
    hurt(-amount);
}

void Player::render() {
    AnsiPrint("PL", green, blue);
}

