#include "c_Auto.h"
#include <cstdlib> 

CaveAutomata::CaveAutomata() : widthCells(0), heightCells(0) {}

int CaveAutomata::getCellSafe(int x, int y) const {
    if (x < 0 || y < 0 || x >= widthCells || y >= heightCells) {
        return 1;
    }
    return gridMap[y * widthCells + x];
}

int CaveAutomata::countNeighbors(int x, int y) const {
    int count = 0;
    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            if (dx == 0 && dy == 0) continue;
            if (getCellSafe(x + dx, y + dy) == 1) {
                count++;
            }
        }
    }
    return count;
}

void CaveAutomata::initialize(int w, int h) {
    widthCells = w;
    heightCells = h;
    gridMap.resize(w * h);
    for (auto& cell : gridMap) {
        cell = 0;
    }
}

void CaveAutomata::randomize(int chancePercent) {
    long long seedValue = reinterpret_cast<long long>(&chancePercent);
    std::srand(static_cast<unsigned int>(seedValue));

    for (auto& cell : gridMap) {
        cell = (std::rand() % 100 < chancePercent) ? 1 : 0;
    }
}

void CaveAutomata::updateSimulation(int birthLimit, int deathLimit) {
    PixelBuffer<int> nextState;
    nextState.resize(widthCells * heightCells);

    for (int y = 0; y < heightCells; ++y) {
        for (int x = 0; x < widthCells; ++x) {
            int neighbors = countNeighbors(x, y);
            int currentIdx = y * widthCells + x;
            int currentState = gridMap[currentIdx];

            if (currentState == 1) {
                if (neighbors < deathLimit) nextState[currentIdx] = 0;
                else nextState[currentIdx] = 1;
            } else {
                if (neighbors > birthLimit) nextState[currentIdx] = 1;
                else nextState[currentIdx] = 0;
            }
        }
    }

    for (int i = 0; i < gridMap.getSize(); ++i) {
        gridMap[i] = nextState[i];
    }
}

void CaveAutomata::drawToWindow(sf::RenderWindow& window, float cellSize) const {
    sf::RectangleShape shape(sf::Vector2f(cellSize, cellSize));
    shape.setFillColor(sf::Color::Black);

    int index = 0;
    for (const auto& cellValue : gridMap) {
        if (cellValue == 1) {
            int posX = index % widthCells;
            int posY = index / widthCells;
            shape.setPosition(posX * cellSize, posY * cellSize);
            window.draw(shape);
        }
        index++;
    }
}