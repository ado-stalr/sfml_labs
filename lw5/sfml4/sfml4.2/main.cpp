#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <cstdint>
#include <iostream>

const float MAX_ROTATION_SPEED_PER_SECOND = 90.0;
const float MAX_MOVING_SPEED_PER_SECOND = 20.0;

// Инициализирует фигуру-стрелку
void initArrow(sf::ConvexShape &arrow)
{
    arrow.setPosition({400, 300});
    arrow.setPointCount(8);
    arrow.setPoint(0, {-50, -25});
    arrow.setPoint(1, {0, -25});
    arrow.setPoint(2, {0, -50});
    arrow.setPoint(3, {50, 0});
    arrow.setPoint(4, {0, 50});
    arrow.setPoint(5, {0, 25});
    arrow.setPoint(6, {-50, 25});
    arrow.setPoint(7, {-50, -25});
    arrow.setFillColor(sf::Color(0xFF, 0xFF, 0));
    arrow.setOutlineColor(sf::Color(0, 0, 0));
    arrow.setOutlineThickness(2);
}

int findRotateDirection(float angle1, float angle2)
{
    // 1   по    часовой
    // 0           равны
    // -1 против часовой
    float deltaAngle = angle2 - angle1;
    if (deltaAngle > 180.0)
        deltaAngle -= 360.0;
    else if (deltaAngle <= -180.0)
        deltaAngle += 360.0;

    if (deltaAngle > 0)
        return 1;
    else if (deltaAngle < 0)
        return -1;
    else
        return 0;
}

// Переводит радианы в градусы
float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

// Переводит градусы в радианы
double toRadians(float degrees)
{
    return double(degrees * M_PI / 180.0);
}

// Обрабатывается событие MouseMove, обновляя позицию мыши
void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    mousePosition = {float(event.x), float(event.y)};
}

float getDeltaTime(sf::Clock &clock)
{
    return clock.restart().asSeconds();
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
        case sf::Event::MouseMoved:
            onMouseMove(event.mouseMove, mousePosition);
            break;
        default:
            break;
        }
    }
}

// Обновляет фигуру, указывающую на мышь
void update(const sf::Vector2f &mousePosition, sf::ConvexShape &arrow, float deltaTime)
{
    const sf::Vector2f arrowPosition = arrow.getPosition();
    const sf::Vector2f delta = mousePosition - arrowPosition;
    const float angle = atan2(delta.y, delta.x);
    float angleInDegrees = toDegrees(angle);
    if (angleInDegrees < 0)
    {
        angleInDegrees = 360.0 + angleInDegrees;
    }
    const float pointerAngle = arrow.getRotation();
    float newAngle = pointerAngle;
    float maxAngle = deltaTime * MAX_ROTATION_SPEED_PER_SECOND;

    int direction = findRotateDirection(pointerAngle, angleInDegrees);

    switch (direction)
    {
    case 1:
        newAngle = pointerAngle + maxAngle;
        break;
    case -1:
        newAngle = pointerAngle - maxAngle;
        break;
    }
    arrow.setRotation(newAngle);

    if (sqrt((delta.x * delta.x) + (delta.y * delta.y)) > MAX_MOVING_SPEED_PER_SECOND * deltaTime)
    {
        float newX = arrowPosition.x + std::cos(toRadians(newAngle)) * MAX_MOVING_SPEED_PER_SECOND * deltaTime;
        float newY = arrowPosition.y + std::sin(toRadians(newAngle)) * MAX_MOVING_SPEED_PER_SECOND * deltaTime;

        arrow.setPosition({newX, newY});
    }
}

// Рисует и выводит один кадр
void redrawFrame(sf::RenderWindow &window, sf::ConvexShape &arrow)
{
    window.clear(sf::Color(0xFF, 0xFF, 0xFF));
    window.draw(arrow);
    window.display();
}

// Программа рисует в окне стрелку, которая поворачивается вслед за курсором мыши.
int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;
    sf::Clock clock;
    sf::ConvexShape arrow;
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Arrow follows mouse", sf::Style::Default, settings);

    sf::Vector2f mousePosition;
    initArrow(arrow);

    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        update(mousePosition, arrow, getDeltaTime(clock));
        redrawFrame(window, arrow);
    }
}