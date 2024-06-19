#include "pause.h"
#include "../../functions/AnsiPrint/AnsiPrint.h"

Pause::Pause() {
}

Pause::~Pause() {
}

ProcessInfo Pause::run(InputState action) {
    if(action == ACTION_INIT) {
        return CONTINUE;
    } else {
        return PAUSE_FINISH;
    }
}

void Pause::render() {
    AnsiPrint("\n\n\n\n\n\n\n\n\n", black, black);
    AnsiPrint("                             -- Pause --\n\n", white, black);
    AnsiPrint("                      Press any key to continue.", white, black);
    AnsiPrint("\n\n\n\n\n\n\n\n", black, black);
}