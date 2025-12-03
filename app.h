#ifndef APP_H
#define APP_H

#include "b_app.h" 
#include "cave_Auto.h"

class CaveApp : public BaseApp {
private:
    CaveAutomata caveSystem;
    
    int simWidth;
    int simHeight;
    int birthRule;
    int deathRule;
    int startChance;

    sf::RectangleShape btnNext;
    float cellSize;

public:
    CaveApp();

    void setup() override;          
    void update() override;         
    void render() override;        
    void handleInput(const sf::Event& event) override; // Обработка кликов
};

class InputManager {
public:
    static int askInt(const char* message, int minVal, int maxVal);
};

#endif