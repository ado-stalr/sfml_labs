#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <algorithm>

const float MAX_ROTATION_SPEED_PER_SECOND = 15;

void init(sf::ConvexShape &pointer)
{
    pointer.setPointCount(3);
    pointer.setPoint(0, {40, 0});
    pointer.setPoint(1, {-20, -20});
    pointer.setPoint(2, {-20, 20});
    pointer.setPosition({400, 300});
    pointer.setFillColor(sf::Color(0xFF, 0x80, 0x00));
}

float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    mousePosition = {
        float(event.x),
        float(event.y),
    };
}

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

void update(const sf::Vector2f &mousePosition, sf::ConvexShape &pointer, float deltaTime)
{
    const sf::Vector2f delta = mousePosition - pointer.getPosition();
    const float angle = atan2(delta.y, delta.x);
    float angleInDegrees = toDegrees(angle);
    if (angleInDegrees < 0)
    {
        angleInDegrees = 360.0 + angleInDegrees;
    }
    const float pointerAngle = pointer.getRotation();
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

    pointer.setRotation(newAngle);
}

void redrawFrame(sf::RenderWindow &window, sf::ConvexShape &pointer)
{
    window.clear();
    window.draw(pointer);
    window.display();
}

float getDeltaTime(sf::Clock &clock)
{
    return clock.restart().asSeconds();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Pointer follows mouse",
        sf::Style::Default,
        settings);

    sf::Clock clock;
    sf::ConvexShape pointer;
    sf::Vector2f mousePosition;

    init(pointer);
    while (window.isOpen())
    {
        // 1, process events with nested loop
        pollEvents(window, mousePosition);
        // 2. update state
        update(mousePosition, pointer, getDeltaTime(clock));
        // 3. draw new frame
        redrawFrame(window, pointer);
    }
}