#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    float defaultWidth = 150;
    float defaultHeight = defaultWidth * 3.3;
    sf::RenderWindow window(sf::VideoMode({(unsigned int)defaultWidth, (unsigned int)defaultHeight}), "Rectangle + circle = traffic lights");

    window.clear();

    sf::RectangleShape shape1;
    shape1.setSize({defaultWidth, defaultHeight});
    shape1.setPosition({0, 0});
    shape1.setFillColor(sf::Color(0x09, 0x09, 0x09));
    window.draw(shape1);

    float circleDiameter = defaultWidth - defaultWidth * 0.1;
    float circleRadius = circleDiameter / 2;

    sf::CircleShape redCircle(circleRadius);
    redCircle.setPosition({(defaultWidth - circleDiameter) / 2, (defaultHeight - 3 * circleDiameter) / 4});
    redCircle.setFillColor(sf::Color(0xFF, 0x00, 0x0));
    window.draw(redCircle);

    sf::CircleShape yellowCircle(circleRadius);
    yellowCircle.setPosition({(defaultWidth - circleDiameter) / 2, (defaultHeight - 3 * circleDiameter) / 4 * 2 + circleDiameter});
    yellowCircle.setFillColor(sf::Color(0xFF, 0xFF, 0x00));
    window.draw(yellowCircle);

    sf::CircleShape greenCircle(circleRadius);
    greenCircle.setPosition({(defaultWidth - circleDiameter) / 2, (defaultHeight - 3 * circleDiameter) / 4 * 3 + circleDiameter * 2});
    greenCircle.setFillColor(sf::Color(0x0, 0xFF, 0x0));
    window.draw(greenCircle);

    window.display();

    sf::sleep(sf::seconds(5));
}