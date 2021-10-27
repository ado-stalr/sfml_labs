#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>

int main()
{
    constexpr int pointCount = 200;
    sf::Clock clock;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({800, 600}), "Ellipse",
        sf::Style::Default, settings);

    sf::ConvexShape shape;

    sf::Vector2f pointOrigin = sf::Vector2f{400, 320};
    float movingAngle = 0;
    float rotationAngle = 0;

    shape.setPosition(pointOrigin);
    shape.setFillColor(sf::Color(0xFF, 0x09, 0x80));

    shape.setPointCount(pointCount);

    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        float pointX = 200 * sin(6 * angle) * std::sin(angle);
        float pointY = 200 * sin(6 * angle) * std::cos(angle);

        sf::Vector2f point = sf::Vector2f{pointX, pointY};
        shape.setPoint(pointNo, point);
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        const float deltaTime = clock.restart().asSeconds();
        const float newX = pointOrigin.x + 200 * sin(6 * movingAngle);
        const float newY = pointOrigin.y + 200 * cos(6 * movingAngle);

        movingAngle += deltaTime * 0.5;
        rotationAngle += deltaTime * 150;

        shape.setRotation(rotationAngle);
        shape.setPosition({newX, newY});

        window.clear();
        window.draw(shape);
        window.display();
    }
}
