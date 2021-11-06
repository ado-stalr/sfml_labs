#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <cstdint>
#include <iostream>

// Инициализирует котика
void initKitty(sf::Sprite &kitty, sf::Texture &kittyTexture)
{
    kittyTexture.loadFromFile("sfml4.3/images/cat.png");
    kitty.setTexture(kittyTexture);
    kitty.setPosition(400, 300);
}

// Опрашивает и обрабатывает доступные события в цикле
void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        default:
            break;
        }
    }
}

// Обновляет фигуру, указывающую на мышь
void update(const sf::Vector2f &mousePosition, sf::Sprite &kitty)
{
}

// Рисует и выводит один кадр
void redrawFrame(sf::RenderWindow &window, sf::Sprite &kitty)
{
    window.clear(sf::Color(0xFF, 0xFF, 0xFF));
    window.draw(kitty);
    window.display();
}

// Программа рисует в окне стрелку, которая поворачивается вслед за курсором мыши.
int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;
    sf::Vector2f mousePosition;

    sf::Sprite kitty;
    sf::Texture kittyTexture;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Arrow follows mouse", sf::Style::Default, settings);

    initKitty(kitty, kittyTexture);

    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        update(mousePosition, kitty);
        redrawFrame(window, kitty);
    }
}