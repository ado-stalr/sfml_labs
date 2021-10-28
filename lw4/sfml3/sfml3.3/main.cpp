#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <cstdint>
#include <iostream>

constexpr int pointCount = 50;
const sf::Vector2f eyeRadius = {40.f, 90.f};
const sf::Vector2f pupilRadius = {10.f, 20.f};
const sf::Vector2f centerRightEye = {450, 300};
const sf::Vector2f centerLeftEye = {350, 300};
const float radiusEyeMoving = 30;

//инициализирует зрачок
void initPupil(sf::ConvexShape &ellipse, sf::Vector2f centerEye)
{
    constexpr int pointCount = 50;
    ellipse.setPosition(centerEye);
    ellipse.setFillColor(sf::Color(0x0, 0x0, 0x0));
    ellipse.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = {
            pupilRadius.x * std::sin(angle),
            pupilRadius.y * std::cos(angle),
        };
        ellipse.setPoint(pointNo, point);
    }
}

//инициализирует глаз
void initEye(sf::ConvexShape &ellipse, sf::Vector2f centerEye)
{
    ellipse.setPosition(centerEye);
    ellipse.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));

    ellipse.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = {
            eyeRadius.x * std::sin(angle),
            eyeRadius.y * std::cos(angle)};
        ellipse.setPoint(pointNo, point);
    }
}

// Обрабатывается событие MouseMove, обновляя позицию мыши
void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    mousePosition = {float(event.x), float(event.y)};
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

void updatePupil(sf::Vector2f &mousePosition, sf::ConvexShape &pupil, sf::Vector2f centerEye)
{
    const sf::Vector2f delta = mousePosition - centerEye;
    float newXL;
    float newYL;

    if (std::sqrt(delta.x * delta.x + delta.y * delta.y) <= radiusEyeMoving)
    {
        newXL = centerEye.x + delta.x;
        newYL = centerEye.y + delta.y;
    }
    else
    {
        const float angle = atan2(delta.y, delta.x);
        newXL = centerEye.x + radiusEyeMoving * std::cos(angle);
        newYL = centerEye.y + radiusEyeMoving * std::sin(angle);
    }
    pupil.setPosition({
        newXL,
        newYL,
    });
}

// Обновляет фигуру, указывающую на мышь
void update(sf::Vector2f &mousePosition, sf::ConvexShape &pupilLeft, sf::ConvexShape &pupilRight)
{
    updatePupil(mousePosition, pupilLeft, centerLeftEye);
    updatePupil(mousePosition, pupilRight, centerRightEye);
}

// Рисует и выводит один кадр
void redrawFrame(sf::RenderWindow &window, sf::ConvexShape &eyeRight, sf::ConvexShape &eyeLeft, sf::ConvexShape &pupilRight, sf::ConvexShape &pupilLeft)
{
    window.clear();
    window.draw(eyeRight);
    window.draw(eyeLeft);
    window.draw(pupilRight);
    window.draw(pupilLeft);
    window.display();
}

int main()
{
    //содаем окно с параметрами сглаживания
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Ellipse", sf::Style::Default, settings);

    sf::ConvexShape pupilRight;
    initPupil(pupilRight, centerRightEye);

    sf::ConvexShape pupilLeft;
    initPupil(pupilLeft, centerLeftEye);

    sf::ConvexShape eyeLeft;
    initEye(eyeLeft, centerLeftEye);

    sf::ConvexShape eyeRight;
    initEye(eyeRight, centerRightEye);

    sf::ConvexShape pointer;
    sf::Vector2f mousePosition;

    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        update(mousePosition, pupilLeft, pupilRight);
        redrawFrame(window, eyeRight, eyeLeft, pupilRight, pupilLeft);
    }
}