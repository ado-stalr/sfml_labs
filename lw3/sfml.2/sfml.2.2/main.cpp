#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>

int main()
{
    constexpr int pointCount = 200;

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
        sf::Vector2f point = sf::Vector2f{
            200 * sin(6 * angle) * std::sin(angle),
            200 * sin(6 * angle) * std::cos(angle)};
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

        movingAngle += 0.0005;

        shape.setRotation(rotationAngle += 0.1);

        shape.setPosition({
            pointOrigin.x + 200 * sin(6 * movingAngle),
            pointOrigin.y + 200 * cos(6 * movingAngle),
        });

        window.clear();
        window.draw(shape);
        window.display();
    }
}
