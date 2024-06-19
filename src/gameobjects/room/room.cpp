#include "room.h"
#include "roomdata.h"
#include "../../functions/AnsiPrint/AnsiPrint.h"

Room::Room(RoomData data) {
    this->roomID = data.id;
    this->roomName = data.name;
    this->roomDescription = data.description;

    this->playerInitialPosition = data.playerInitialPosition;

    for(auto enemy : data.enemies) {
        this->enemies.push_back(enemy);
    }

    for (int y = 0; y < GAME_WINDOW_SIZE_Y; y++) {
        for (int x = 0; x < GAME_WINDOW_SIZE_X; x++) {
            this->defaultRoomObjectMap[y][x] = RoomObject(data.defaultRoomObjectMap[y][x]);
        }
    }
}

Room::~Room() {
    for(auto enemy : this->enemies) {
        delete enemy;
    }
}

bool Room::walkable(Position position) {
    if(this->defaultRoomObjectMap[position.getY()][position.getX()] == OBJECT_WALL) {
        return false;
    }
    if(this->defaultRoomObjectMap[position.getY()][position.getX()] == OBJECT_ROCK) {
        return false;
    }
    if(this->defaultRoomObjectMap[position.getY()][position.getX()] == OBJECT_WATER) {
        return false;
    }
    return true;
}

const std::vector<Enemy *> & Room::getEnemies() {
    return this->enemies;
}

void Room::destroyEnemy(Enemy *enemy) {
    for(auto it = this->enemies.begin(); it != this->enemies.end(); it++) {
        if(*it == enemy) {
            delete enemy;
            this->enemies.erase(it);
            return;
        }
    }
}

void Room::render(Position position) {
    switch(this->defaultRoomObjectMap[position.getY()][position.getX()]) {
        case OBJECT_NONE:
            AnsiPrint("  ", black, black);
            break;
        case OBJECT_DOOR:
            AnsiPrint("DR", yellow, black);
            break;
        case OBJECT_WALL:
            AnsiPrint("██", white, black);
            break;
        case OBJECT_GRASS:
            AnsiPrint("WW", green, black);
            break;
        case OBJECT_ROCK:
            AnsiPrint("▲▲", yellow, black);
            break;
        case OBJECT_WATER:
            if(rand() % 2 == 0) {
                AnsiPrint("~~", cyan, blue);
            } else {
                AnsiPrint("……", cyan, blue);
            }
            break;
    }
}