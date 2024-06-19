#include "move.h"
#include "../../functions/AnsiPrint/AnsiPrint.h"
#include "../../controller/enviroment.h"

using namespace DirectionState;

Move::Move(Player *player, Room *room) {
    this->player = player;
    this->room = room;
}

Move::~Move() {
}

Direction InputStateToDirection(InputState input) {
    switch(input) {
    case ACTION_UP:
        return UP;
    case ACTION_DOWN:
        return DOWN;
    case ACTION_LEFT:
        return LEFT;
    case ACTION_RIGHT:
        return RIGHT;
    default:
        return NONE;
    }
}

ProcessInfo Move::run(InputState action) {
    if(action == ACTION_PAUSE) {
        return MOVE_FINISH_PAUSE;
    }
    ProcessInfo nextProcess = CONTINUE;
    Direction direction = InputStateToDirection(action);
    bool moveable = room->walkable(player->getPosition() + direction);
    if(moveable) {
        PlayerState::MoveState playerState = player->move(direction);

        switch(playerState) {
        case LEFTROOM:
            nextProcess = MOVE_FINISH_ROOMCHANGE_LEFT;
            break;
        case RIGHTROOM:
            nextProcess = MOVE_FINISH_ROOMCHANGE_RIGHT;
            break;
        default:
            break;
        }
    }
    for(auto enemy : room->getEnemies()) {
        Direction enemyDirection = enemy->nextPosition();
        bool enemyMoveable = room->walkable(enemy->getPosition() + enemyDirection);
        if(enemyMoveable) {
            enemy->move(enemyDirection);
        }
    }

    for(auto enemy : room->getEnemies()) {
        if(enemy->getPosition() == player->getPosition()) {
            nextProcess = MOVE_FINISH_BATTLE;
            break;
        }
    }
    return nextProcess;
}

void Move::render() {
    for (int y = 0; y < GAME_WINDOW_SIZE_Y; y++) {
        for (int x = 0; x < GAME_WINDOW_SIZE_X; x++) {
            if(player->getPosition() == Position(x, y)) {
                player->render();
                continue;
            }
            bool flag = false;
            for(auto enemy : room->getEnemies()) {
                if(enemy->getPosition() == Position(x, y)) {
                    enemy->render();
                    flag = true;
                    continue;
                }
            }
            if(flag) continue;
            room->render(Position(x, y));
        }
        AnsiPrint("\n", nochange, nochange);
        }
}