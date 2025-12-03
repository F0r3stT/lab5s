#ifndef BASE_APP_H
#define BASE_APP_H

#include <SFML/Graphics.hpp>

class BaseApp {
protected:
    sf::RenderWindow window; //окно в котором всё рисуется
    int winWidth; 
    int winHeight;
    const char* winTitle;

public:
    BaseApp() : winWidth(800), winHeight(600), winTitle("Base App") {}
    virtual ~BaseApp() {}

    //чисто виртуальные функции - наследник обязан их реализовать
    virtual void setup() = 0; 
    virtual void update() = 0;
    virtual void render() = 0;  
    virtual void handleInput(const sf::Event& event) = 0; //обработка событий

    void run() {
        setup();

        window.create(sf::VideoMode(winWidth, winHeight), winTitle);
        window.setFramerateLimit(60);

        //цикл закртия окна
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
                
                //передаем события наследнику
                handleInput(event); 
            }
            update();
            window.clear(sf::Color::White);
            render(); //отрисовка конкретной сцены наследника
            window.display();
        }
    }
};

#endif