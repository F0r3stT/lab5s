#include "cave_Auto.h"
#include <cstdlib> 

CaveAutomata::CaveAutomata() : widthC(0), heightC(0) {}

//если координата вне поля, то возвращает 1(стена)
int CaveAutomata::getCellSafe(int x, int y) const {
    if (x < 0 || y < 0 || x >= widthC || y >= heightC) {
        return 1; //пример поля - окруженные стенами
    }
    return gridMap[y * widthC + x]; //если внутри считаем индекс и возвращаем значение
}

//подсчёт соседей стен
int CaveAutomata::countNeighbors(int x, int y) const {
    int count = 0;
    for (int dy = -1; dy <= 1; ++dy) { //смещение по Y
        for (int dx = -1; dx <= 1; ++dx) { //смещение по X
            if (dx == 0 && dy == 0) 
                continue; //пропуск самой клетки
            if (getCellSafe(x + dx, y + dy) == 1) 
            {
                count++;
            }
        }
    }
    return count;
}

//иниацилизация карты
void CaveAutomata::initialize(int w, int h) {
    widthC = w; //запоминаем размер карты
    heightC = h;
    gridMap.resize(w * h); //и меняем размер буфера
    for (auto& c : gridMap) {
        c = 0;
    }
}

//случайная генерация поля
void CaveAutomata::randomize(int chancePercent) {
//заполняем поле по проентам стен
    long long seedVal = reinterpret_cast<long long>(&chancePercent);
    std::srand(static_cast<unsigned int>(seedVal));

    for (auto& cell : gridMap) {
    int r = std::rand() % 100;  //случайное число от 0 до 99

    if (r < chancePercent) {
        cell = 1;  //ставим стену
    } else {
        cell = 0;  //оставляем пусто
    }
}
}


void CaveAutomata::updateSim(int birthLimit, int deathLimit) {
    PixelBuffer<int> nextState;
    nextState.resize(widthC * heightC);

    for (int y = 0; y < heightC; ++y) {
        for (int x = 0; x < widthC; ++x) {
            int neighbors = countNeighbors(x, y); //соседи вокруг стены
            int currentIdx = y * widthC + x; //индекс текущей клетки
            int currentState = gridMap[currentIdx]; //состояние клетки

            //если клетка стена
            if (currentState == 1) {
                if (neighbors < deathLimit) 
                    nextState[currentIdx] = 0; //если соседей стен меньше чем предел смерти, стена умирает
                else 
                    nextState[currentIdx] = 1; //иначе клетка остаётся стеной
            } else {
                //пустая клетка
                if (neighbors > birthLimit) //много стен вокруг рождается стена
                    nextState[currentIdx] = 1; //соседей больше чем предел рождения, стена появлияется
                else 
                    nextState[currentIdx] = 0;
            }
        }
    }

    for (int i = 0; i < gridMap.getSize(); ++i) {
        gridMap[i] = nextState[i]; //копируем из следующего шага в массив целых чисел
    }
}

void CaveAutomata::drawWindow(sf::RenderWindow& window, float cellSize) const {
    sf::RectangleShape shape(sf::Vector2f(cellSize, cellSize)); //прямоугольник заданного размера
    shape.setFillColor(sf::Color::Black); //клетка стена

    int index = 0;
    for (const auto& cellValue : gridMap) {
        if (cellValue == 1) { //стену
            int posX = index % widthC; //столбец = остаток от деления индекса на ширину
            int posY = index / widthC;
            shape.setPosition(posX * cellSize, posY * cellSize); //клетка попадает в пиксельную позицию
            window.draw(shape);
        }
        index++;
    }
}