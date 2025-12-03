#ifndef C_AUTO_H
#define C_AUTO_H

#include <SFML/Graphics.hpp>
#include "pixel_buffer.h"

class CaveAutomata {
private:
    PixelBuffer<int> gridMap; //буфер для хранения карты пещеры
    int widthC;
    int heightC;

    int getCellSafe(int x, int y) const; //безопасное чтение клеток
    int countNeighbors(int x, int y) const;

public:
    CaveAutomata();
    void initialize(int w, int h);
    void randomize(int chancePercent);
    void updateSim(int birthLimit, int deathLimit); 
    void drawWindow(sf::RenderWindow& window, float cellSize) const;
};

#endif 