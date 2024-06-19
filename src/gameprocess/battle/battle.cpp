#include "battle.h"
#include "../../functions/AnsiPrint/AnsiPrint.h"
#include "../../controller/enviroment.h"
#include <iostream>

Battle::Battle(Player* player, Enemy* enemy) {
    this->player = player;
    this->enemy = enemy;
    state = ACTION_SELECTING;
    actionPlayerSelected = ATTACK;
}

Battle::~Battle() {
}

BattleMenuInput Battle::InputStateToBattleMenuInput(InputState action) {
    switch(action) {
    case ACTION_UP:
        return MENU_UP;
    case ACTION_DOWN:
        return MENU_DOWN;
    case ACTION_CONFIRM:
        return MENU_CONFIRM;
    default:
        return MENU_NONE;
    }
}

ProcessInfo Battle::run(InputState action) {

    BattleMenuInput menuInput = InputStateToBattleMenuInput(action);
    if(menuInput == MENU_NONE) {
        return CONTINUE;
    }
    
    if (state == ENEMY_DEAD) {
        return BATTLE_FINISH_PLAYER_WIN;
    } else if (state == PLAYER_DEAD) {
        return BATTLE_FINISH_PLAYER_DEAD;
    }

    if(player->getHealth() <= 0) {
        state = PLAYER_DEAD;
    } else if(enemy->getHealth() <= 0) {
        state = ENEMY_DEAD;
    }

    if (state == TURN_END) {
        state = ACTION_SELECTING;
        return CONTINUE;
    }

    if(state == ACTION_SELECTING) {
        switch (menuInput) {
            case MENU_UP:
                actionPlayerSelected = BattleAction((actionPlayerSelected + (BATTLE_ACTION_COUNT_PLAYER - 1)) % BATTLE_ACTION_COUNT_PLAYER);
                break;
            case MENU_DOWN:
                actionPlayerSelected = BattleAction((actionPlayerSelected + 1) % BATTLE_ACTION_COUNT_PLAYER);
                break;
            case MENU_CONFIRM:
                state = TURN_END;
                break;
            default:
                break;
        }
    }

    if(state == TURN_END) {
        actionEnemySelected = BattleAction(rand() % BATTLE_ACTION_COUNT_ENEMY);
        DamageToEnemy = damageCalculate(actionPlayerSelected, actionEnemySelected, player->getAttack());
        DamageToPlayer = damageCalculate(actionEnemySelected, actionPlayerSelected, enemy->getAttack());
        if(actionPlayerSelected == HEAL) {
            player->heal(player->getHealPower());
        }
        enemy->hurt(DamageToEnemy);
        player->hurt(DamageToPlayer);
    }

    return CONTINUE;
}

int Battle::damageCalculate(BattleAction attackerAction, BattleAction targetAction, int damage) {
    if(attackerAction == FORCE_ATTACK) {
        damage *= FORCE_ATTACK_MULTIPLIER;
    } else if(attackerAction == ATTACK) {
        damage *= ATTACK_MULTIPLIER;
    } else if(attackerAction == DEFEND) {
        damage = 0;
    } else if(attackerAction == HEAL) {
        damage = 0;
    }

    if(targetAction == DEFEND) {
        damage /= DEFEND_MULTIPLIER;
    } else if(targetAction == FORCE_ATTACK) {
        damage *= FORCE_ATTACK_MULTIPLIER;
    } else if(targetAction == HEAL) {
        damage *= FORCE_ATTACK_MULTIPLIER;
    }

    return damage;
}

std::string Battle::BattleActionToString(BattleAction action) {
    switch(action) {
        case FORCE_ATTACK:
            return "force attack";
        case ATTACK:
            return "attack";
        case DEFEND:
            return "defend";
        case HEAL:
            return "heal";
        default:
            return "none";
    }
}

std::string repeat(const std::string& input, int num) {
    if(num < 0) return "";
    std::string s;
    s.reserve(input.size() * num);
    while (num--) s += input;
    return s;
}

void Battle::render() {
    // remember screen size is defined in controller/enviroment.h

    // line 1
    AnsiPrint("\n", black, black);

    // life bar and name
    const int windowEdge = 1;
    const int lifeBarWidth = GAME_WINDOW_SIZE_X - windowEdge * 2; // 2 means left and right edge

    int playerHealthBlocks = (int) double(player->getHealth()) / double(player->getMaxHealth()) * lifeBarWidth;
    int enemyHealthBlocks = (int) double(enemy->getHealth()) / double(enemy->getMaxHealth()) * lifeBarWidth;

    std::string playerLifeBar = repeat("██", playerHealthBlocks) + repeat("__", (lifeBarWidth - playerHealthBlocks));
    std::string enemyLifeBar = repeat("__", (lifeBarWidth - enemyHealthBlocks)) + repeat("██", enemyHealthBlocks);

    // line 2
    AnsiPrint("  ", black, black);
    AnsiPrint(playerLifeBar.c_str(), blue, black);
    AnsiPrint("\n", black, black);

    // line 3
    AnsiPrint("  ", black, black);
    AnsiPrint(player->getName().c_str(), blue, black);
    AnsiPrint("\n", black, black);

    // line 4
    AnsiPrint("  ", black, black);
    AnsiPrint(std::string((GAME_WINDOW_SIZE_X - windowEdge * 2) * GAME_WINDOW_ONEBLOCK_WIDTH - enemy->getName().size(), ' ').c_str(), black, black);
    AnsiPrint(enemy->getName().c_str(), red, black);
    AnsiPrint("\n", black, black);

    // line 5
    AnsiPrint("  ", black, black);
    AnsiPrint(enemyLifeBar.c_str(), red, black);
    AnsiPrint("\n", black, black);

    // line 6~12
    AnsiPrint("\n\n\n\n\n\n\n", black, black);

    switch (state) {
        case ACTION_SELECTING: {
            // line 13 ~ 20
            AnsiPrint("  Please select your action:\n\n", white, black);
            AnsiPrint("    1) Force Attack\n", (actionPlayerSelected == FORCE_ATTACK ? yellow : white), black);
            AnsiPrint("    2) Attack\n", (actionPlayerSelected == ATTACK ? yellow : white), black);
            AnsiPrint("    3) Defend\n", (actionPlayerSelected == DEFEND ? yellow : white), black);
            AnsiPrint("    4) Heal\n\n", (actionPlayerSelected == HEAL ? yellow : white), black);
            AnsiPrint("  Press Enter to confirm.\n\n", white, black);

            break;
        }

        case TURN_END: {
            // line 13
            AnsiPrint("  You ", blue, black);
            AnsiPrint("performed the ", white, black);
            AnsiPrint(BattleActionToString(actionPlayerSelected).c_str(), yellow, black);
            AnsiPrint(" on the ", white, black);
            AnsiPrint(enemy->getName().c_str(), red, black);
            AnsiPrint(".\n", white, black);

            // line 14 15
            AnsiPrint("  ", black, black);
            AnsiPrint(enemy->getName().c_str(), red, black);
            AnsiPrint(" performed the ", white, black);
            AnsiPrint(BattleActionToString(actionEnemySelected).c_str(), yellow, black);
            AnsiPrint(" on ", white, black);
            AnsiPrint("You", blue, black);
            AnsiPrint(".\n\n", white, black);

            // line 16
            AnsiPrint("  You ", blue, black);
            AnsiPrint("dealt ", white, black);
            AnsiPrint(std::to_string(DamageToEnemy).c_str(), yellow, black);
            AnsiPrint(" damage to ", white, black);
            AnsiPrint(enemy->getName().c_str(), red, black);
            AnsiPrint(".\n", white, black);

            // line 17 18
            AnsiPrint("  Enemy ", red, black);
            AnsiPrint("dealt ", white, black);
            AnsiPrint(std::to_string(DamageToPlayer).c_str(), yellow, black);
            AnsiPrint(" damage to ", white, black);
            AnsiPrint("You", blue, black);
            AnsiPrint(".\n\n", white, black);

            // line 19 20
            AnsiPrint("  Press any key to continue.\n\n", white, black);
            break;
        }

        case ENEMY_DEAD: {
            // line 13
            AnsiPrint("  You ", blue, black);
            AnsiPrint("defeated ", white, black);
            AnsiPrint(enemy->getName().c_str(), red, black);
            AnsiPrint("!\n", blue, black);

            // line 14 ~ 20
            AnsiPrint("\n\n\n\n\n\n\n", black, black);
            break;
        }

        case PLAYER_DEAD: {
            // line 13
            AnsiPrint("  You ", red, black);
            AnsiPrint("were defeated by ", white, black);
            AnsiPrint(enemy->getName().c_str(), red, black);
            AnsiPrint("!\n", red, black);

            // line 14 ~ 20
            AnsiPrint("\n\n\n\n\n\n\n", black, black);
            break;
        }
    }
}