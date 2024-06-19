#include "controller.h"
#include "../gameobjects/room/roomdata.h"
#include "../functions/position/position.h"
#include "../functions/position/direction.h"
#include "../functions/AnsiPrint/AnsiPrint.h"

#include "../gameprocess/allgameprocess.h"

Controller::Controller() {
    const int defaultRoomIndex = 0;
    RoomData roomData = ROOM_DATA[defaultRoomIndex];
    Room *room = new Room(roomData);
    rooms.insert(std::pair<int, Room *>(defaultRoomIndex, room));
    currentRoomIndex = defaultRoomIndex;
    player = new Player(roomData.playerInitialPosition);

    state = PROCESS_MOVEMENT;
    currentProcess = new Move(player, room);
}

Controller::~Controller() {
    for (size_t i = 0; i < rooms.size(); i++) {
        delete rooms[i];
    }
    delete player;
}

RunningState Controller::run(InputState action) {

    if(state == PROCESS_GAMEOVER) {
        return EXIT;
    }

    if(state == PROCESS_GAMECLEAR) {
        return EXIT;
    }

    ProcessInfo info = currentProcess->run(action);

    switch (state) {
    case PROCESS_MOVEMENT: {
        if(info == MOVE_FINISH_ROOMCHANGE_LEFT) {
            if(currentRoomIndex > 0) {
                roomChange(currentRoomIndex - 1);
                stateChange(PROCESS_MOVEMENT);
                player->setPosition(Position(GAME_WINDOW_SIZE_X - 1, player->getPosition().getY()));
            }
        } else if(info == MOVE_FINISH_ROOMCHANGE_RIGHT) {
            if(currentRoomIndex < (std::end(ROOM_DATA) - std::begin(ROOM_DATA) - 1)) {
                roomChange(currentRoomIndex + 1);
                stateChange(PROCESS_MOVEMENT);
                player->setPosition(Position(0, player->getPosition().getY()));
            }
        } else if(info == MOVE_FINISH_BATTLE) {
            stateChange(PROCESS_BATTLE);
        } else if(info == MOVE_FINISH_PAUSE) {
            stateChange(PROCESS_PAUSE);
        }
        break;
    }

    case PROCESS_BATTLE: {
        if(info == BATTLE_FINISH_PLAYER_WIN) {
            stateChange(PROCESS_MOVEMENT);
            for(auto enemy : rooms[currentRoomIndex]->getEnemies()) {
                if(enemy->getPosition() == player->getPosition()) {
                    rooms[currentRoomIndex]->destroyEnemy(enemy);
                    if(enemy->isLastBoss()) {
                        stateChange(PROCESS_GAMECLEAR);
                    }
                    break;
                }
            }
        } else if(info == BATTLE_FINISH_PLAYER_DEAD) {
            stateChange(PROCESS_GAMEOVER);
        } 
        break;
    }

    case PROCESS_PAUSE: {
        if(info == PAUSE_FINISH) {
            stateChange(PROCESS_MOVEMENT);
        }
        break;
    }

    default:
        break;
    }

    this->render();

    return PLAY;
}

void Controller::stateChange(GameProcessState newState) {
    state = newState;
    delete currentProcess;
    switch (state) {
        case PROCESS_MOVEMENT:
            currentProcess = new Move(player, rooms[currentRoomIndex]);
            break;
        case PROCESS_PAUSE:
            currentProcess = new Pause();
            break;
        case PROCESS_BATTLE:
            for(auto enemy : rooms[currentRoomIndex]->getEnemies()) {
                if(enemy->getPosition() == player->getPosition()) {
                    currentProcess = new Battle(player, enemy);
                    state = PROCESS_BATTLE;
                    break;
                }
            }
            break;
        case PROCESS_GAMEOVER:
            currentProcess = new GameOver();
            break;
        case PROCESS_GAMECLEAR:
            currentProcess = new GameClear();
            break;
        default:
            break;
    }
}

void Controller::roomChange(int roomIndex) {
    if(roomIndex < 0 || roomIndex > (std::end(ROOM_DATA) - std::begin(ROOM_DATA) - 1))
        return;

    if(rooms.find(roomIndex) == rooms.end()) {
        RoomData roomData = ROOM_DATA[roomIndex];
        Room *room = new Room(roomData);
        rooms.insert(std::pair<int, Room *>(roomIndex, room));
    }
    currentRoomIndex = roomIndex;
}

void Controller::render() {
    currentProcess->render();
    output();
}