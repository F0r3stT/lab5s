#include "input_man.h"
#include <iostream>

int InputManager::askInteger(const char* message, int minVal, int maxVal) {
    int inputVal;
    while (true) {
        std::cout << message << " (" << minVal << " - " << maxVal << "): ";
        if (std::cin >> inputVal && inputVal >= minVal && inputVal <= maxVal) {
            return inputVal;
        } else {
            std::cout << "Ошибка: Введите число в заданном диапазоне.\n";
            std::cin.clear();
            while (std::cin.get() != '\n');
        }
    }
}