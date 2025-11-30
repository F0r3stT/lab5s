#ifndef C_APP_H
#define C_APP_H

#include "c_Auto.h"

class CaveApp {
private:
    CaveAutomata caveSystem;
    int simWidth;
    int simHeight;
    int birthRule;
    int deathRule;
    int startChance;

public:
    CaveApp();
    void setupParams();
    void run();
};

#endif // CAVE_APP_H