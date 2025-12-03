#include "app.h"
#include <iostream>

using namespace std;

CaveApp::CaveApp() : simWidth(0), simHeight(0), birthRule(0), deathRule(0), startChance(0), cellSize(20.0f) {
    winTitle = "Генератор Пещер";

    //настройка кнопки
    btnNext.setSize(sf::Vector2f(140.0f, 40.0f));
    btnNext.setFillColor(sf::Color(50, 50, 50));
    btnNext.setOutlineColor(sf::Color::White);
    btnNext.setOutlineThickness(1.0f);
}

//ввод числа в заданном диапазоне с значением
int InputManager::askInt(const char* message, int minVal, int maxVal) {
    int inputVal;
    while (true) {
        cout << message << " (" << minVal << " - " << maxVal << "): ";
        if (cin >> inputVal && inputVal >= minVal && inputVal <= maxVal) {
            return inputVal;
        } else {
            cout << "Ошибка: Введите число в заданном диапазоне.\n";
            cin.clear();
            while (cin.get() != '\n');
        }
    }
}

void CaveApp::setup() {
    cout << "--- Настройка симуляции ---" << endl;
    simWidth = InputManager::askInt("Ширина поля", 10, 500); 
    simHeight = InputManager::askInt("Высота поля", 10, 500);
    startChance = InputManager::askInt("Шанс стен %", 0, 100);
    deathRule = InputManager::askInt("Предел смерти", 0, 8);
    birthRule = InputManager::askInt("Предел рождения", 0, 8);

    caveSystem.initialize(simWidth, simHeight);
    
    caveSystem.randomize(startChance); 

    if (simWidth * cellSize > 1200) 
        cellSize = 1200.0f / simWidth;

    int w = static_cast<int>(simWidth * cellSize); 
    int h = static_cast<int>(simHeight * cellSize);
    
    if (w < 300) 
        w = 300;
    if (h < 300) 
        h = 300;

    this->winWidth = w;
    this->winHeight = h + 60; 

    //позиция кнопки по центру внизу
    btnNext.setPosition((w - 140.0f) / 2.0f, h + 10.0f);
}

void CaveApp::handleInput(const sf::Event& appEvent) {
    if (appEvent.type == sf::Event::MouseButtonPressed) { 
        if (appEvent.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mPos((float)appEvent.mouseButton.x, (float)appEvent.mouseButton.y);
            
            if (btnNext.getGlobalBounds().contains(mPos)) {
                caveSystem.updateSim(birthRule, deathRule); //обновляем шаг при помощи заданных параметров рождения
                cout << "Симуляция обновлена" << endl;
            }
        }
    }
}

void CaveApp::update() {
}

//Отрисовка сцены
void CaveApp::render() {
    caveSystem.drawWindow(window, cellSize); 
    window.draw(btnNext);
}