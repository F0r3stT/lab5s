#include "c_app.h"
#include "input_man.h"
#include <iostream>
#include <SFML/Graphics.hpp>

CaveApp::CaveApp() : simWidth(0), simHeight(0), birthRule(0), deathRule(0), startChance(0) {}

void CaveApp::setupParams() {
    std::cout << "=== Генератор Пещер (Многофайловый проект) ===" << std::endl;
    simWidth = InputManager::askInteger("Ширина поля", 10, 500);
    simHeight = InputManager::askInteger("Высота поля", 10, 500);
    startChance = InputManager::askInteger("Шанс стен %", 0, 100);
    deathRule = InputManager::askInteger("Предел смерти", 0, 8);
    birthRule = InputManager::askInteger("Предел рождения", 0, 8);

    caveSystem.initialize(simWidth, simHeight);
    caveSystem.randomize(startChance);
}

void CaveApp::run() {
    float cellSize = 20.0f;
    if (simWidth * cellSize > 1200) cellSize = 1200.0f / simWidth;

    int winW = static_cast<int>(simWidth * cellSize);
    int winH = static_cast<int>(simHeight * cellSize);
    
    if (winW < 300) winW = 300;
    if (winH < 300) winH = 300;

    int uiOffset = 60;

    sf::RenderWindow window(sf::VideoMode(winW, winH + uiOffset), "Cave OOP Multi-file");
    window.setFramerateLimit(60);

    sf::RectangleShape btnNext(sf::Vector2f(140.0f, 40.0f));
    btnNext.setFillColor(sf::Color(50, 50, 50));
    btnNext.setOutlineColor(sf::Color::White);
    btnNext.setOutlineThickness(1.0f);
    btnNext.setPosition((winW - 140.0f) / 2.0f, winH + 10.0f);

    while (window.isOpen()) {
        sf::Event appEvent;
        while (window.pollEvent(appEvent)) {
            if (appEvent.type == sf::Event::Closed) {
                window.close();
            }

            if (appEvent.type == sf::Event::MouseButtonPressed) {
                if (appEvent.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mPos((float)appEvent.mouseButton.x, (float)appEvent.mouseButton.y);
                    
                    if (btnNext.getGlobalBounds().contains(mPos)) {
                        caveSystem.updateSimulation(birthRule, deathRule);
                        std::cout << "Симуляция обновлена." << std::endl;
                    }
                }
            }
        }

        window.clear(sf::Color::White);
        caveSystem.drawToWindow(window, cellSize);
        window.draw(btnNext);
        window.display();
    }
}