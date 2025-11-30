#ifndef C_AUTO_H
#define C_AUTO_H

#include <SFML/Graphics.hpp>
#include "pixel_buffer.h"

class CaveAutomata {
private:
    PixelBuffer<int> gridMap; 
    int widthCells;
    int heightCells;

    int getCellSafe(int x, int y) const;
    int countNeighbors(int x, int y) const;

public:
    CaveAutomata();
    void initialize(int w, int h);
    void randomize(int chancePercent);
    void updateSimulation(int birthLimit, int deathLimit);
    void drawToWindow(sf::RenderWindow& window, float cellSize) const;
};

#endif 