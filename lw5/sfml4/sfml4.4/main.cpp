#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <cstdint>
#include <iostream>

const float MAX_MOVING_SPEED_PER_SECOND = 160.0;
bool isStarting = false;

// Инициализирует котика
void initKitty(sf::Sprite &kitty, sf::Texture &kittyTexture)
{
    kittyTexture.loadFromFile("sfml4.3/images/cat.png");
    kitty.setTexture(kittyTexture);
    sf::FloatRect boundingRect = kitty.getLocalBounds();
    kitty.setOrigin(boundingRect.width / 2, boundingRect.height / 2);
    kitty.setPosition(400, 300);
}

// Инициализует указку
void initPointer(sf::Sprite &pointer, sf::Texture &pointerTexture)
{
    pointerTexture.loadFromFile("sfml4.3/images/red_pointer.png");
    pointer.setTexture(pointerTexture);
    sf::FloatRect boundingRect = pointer.getLocalBounds();
    pointer.setOrigin(boundingRect.width / 2, boundingRect.height / 2);
    pointer.setPosition(-50, 0);
}

// Переводит радианы в градусы
float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

// Обрабатывается событие MouseMove, обновляя позицию мыши
void onMouseClick(const sf::Event &event, sf::Sprite &pointer)
{
    if (event.mouseButton.button == sf::Mouse::Left)
    {
        isStarting = true;
        std::cout << "the left button was pressed" << std::endl;
        std::cout << "mouse x: " << event.mouseButton.x << std::endl;
        std::cout << "mouse y: " << event.mouseButton.y << std::endl;
        pointer.setPosition({float(event.mouseButton.x), float(event.mouseButton.y)});
    }
}

float getDeltaTime(sf::Clock &clock)
{
    return clock.restart().asSeconds();
}

// Опрашивает и обрабатывает доступные события в цикле
void pollEvents(sf::RenderWindow &window, sf::Sprite &pointer)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseButtonPressed:
            onMouseClick(event, pointer);
            break;
        default:
            break;
        }
    }
}

float moduleVectora(float x, float y)
{
    return sqrt((x * x) + (y * y));
}

// Обновляет фигуру, указывающую на мышь
void update(const sf::Sprite &pointer, sf::Sprite &kitty, float deltaTime)
{
    const sf::Vector2f kittyPosition = kitty.getPosition();
    const sf::Vector2f pointerPosition = pointer.getPosition();
    const sf::Vector2f delta = pointerPosition - kittyPosition;
    const float moduleDelta = moduleVectora(delta.x, delta.y);
    if (!moduleDelta)
        return;

    const float directionX = (delta.x / moduleDelta) * MAX_MOVING_SPEED_PER_SECOND * deltaTime;
    const float directionY = (delta.y / moduleDelta) * MAX_MOVING_SPEED_PER_SECOND * deltaTime;

    if (moduleVectora(directionX, directionY) < moduleDelta)
    {
        float newX = kittyPosition.x + directionX;
        float newY = kittyPosition.y + directionY;

        kitty.setPosition({newX, newY});
    }
    else
    {
        kitty.setPosition(pointerPosition);
    }

    const float angle = toDegrees(atan2(delta.y, delta.x));
    if (abs(angle) > 90)
        kitty.setScale(-1, 1);
    else
        kitty.setScale(1, 1);
}

// Рисует и выводит один кадр
void redrawFrame(sf::RenderWindow &window, sf::Sprite &kitty, sf::Sprite &pointer)
{
    window.clear(sf::Color(0xFF, 0xFF, 0xFF));
    window.draw(pointer);
    window.draw(kitty);
    window.display();
}

// Программа рисует в окне стрелку, которая поворачивается вслед за курсором мыши.
int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;
    sf::Clock clock;
    sf::Vector2f mousePosition;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Arrow follows mouse", sf::Style::Default, settings);

    sf::Sprite kitty;
    sf::Texture kittyTexture;
    sf::Sprite pointer;
    sf::Texture pointerTexture;

    initKitty(kitty, kittyTexture);
    initPointer(pointer, pointerTexture);

    while (window.isOpen())
    {
        float deltaTime = getDeltaTime(clock);

        pollEvents(window, pointer);
        if (isStarting)
            update(pointer, kitty, deltaTime);
        redrawFrame(window, kitty, pointer);
    }
}