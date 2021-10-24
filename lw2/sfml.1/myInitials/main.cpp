#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>

int main()
{
    float defaultHeight = 100;
    float defaultWidth = defaultHeight * 2;
    sf::RenderWindow window(sf::VideoMode({(unsigned int)defaultWidth, (unsigned int)defaultHeight}), "My Initials by primitive elements");

    window.clear();

    float circleDiameter = defaultHeight - defaultHeight * 0.2;
    float circleRadius = circleDiameter / 2;

    sf::CircleShape letterDCircle(circleRadius);
    letterDCircle.setPosition({-circleRadius / 2, (defaultHeight - circleDiameter) / 2});
    letterDCircle.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
    window.draw(letterDCircle);

    float circleClearDiameter = circleDiameter * 0.8;
    float circleClearRadius = circleClearDiameter / 2;

    sf::CircleShape letterDClearCircle(circleClearRadius);
    letterDClearCircle.setPosition({-circleRadius / 2 + (circleDiameter - circleClearDiameter) / 2, (defaultHeight - circleClearDiameter) / 2});
    letterDClearCircle.setFillColor(sf::Color(0x0, 0x0, 0x0));
    window.draw(letterDClearCircle);

    sf::RectangleShape letterDClearBlock;
    letterDClearBlock.setSize({circleRadius / 2, defaultHeight});
    letterDClearBlock.setPosition({0, 0});
    letterDClearBlock.setFillColor(sf::Color(0x00, 0x00, 0x00));
    window.draw(letterDClearBlock);

    float letterWeight = defaultHeight / 15;

    sf::RectangleShape letterDBlock;
    letterDBlock.setSize({letterWeight, circleDiameter});
    letterDBlock.setPosition({circleRadius / 2 - letterWeight, (defaultHeight - circleDiameter) / 2});
    letterDBlock.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
    window.draw(letterDBlock);

    float letterAAngle = 22;
    float letterABlockSize = circleDiameter / cos(letterAAngle * 3.14 / 180);
    std::printf("%f\n%f\n", letterABlockSize, cos(letterAAngle * 3.14 / 180));

    sf::RectangleShape letterABlock1;
    letterABlock1.setSize({letterWeight, letterABlockSize});
    letterABlock1.setRotation(letterAAngle);
    letterABlock1.setPosition({defaultWidth / 2 - 2 * letterWeight, (defaultHeight - circleDiameter) / 2});
    letterABlock1.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
    window.draw(letterABlock1);

    sf::RectangleShape letterABlock2;
    letterABlock2.setSize({letterWeight, letterABlockSize});
    letterABlock2.setRotation(-letterAAngle);
    letterABlock2.setPosition({defaultWidth / 2 - 2 * letterWeight, (defaultHeight - circleDiameter) / 2});
    letterABlock2.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
    window.draw(letterABlock2);

    sf::RectangleShape letterABlock3;
    float letterABlock3PositionX = defaultWidth / 2.4 - 2 * letterWeight;
    letterABlock3.setSize({letterABlockSize / 2, letterWeight});
    letterABlock3.setPosition({letterABlock3PositionX, defaultHeight / 2});
    letterABlock3.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
    window.draw(letterABlock3);

    sf::RectangleShape letterABlock4;
    letterABlock4.setSize({letterWeight, letterABlockSize});
    letterABlock4.setRotation(letterAAngle);
    letterABlock4.setPosition({defaultWidth - circleRadius, (defaultHeight - circleDiameter) / 2});
    letterABlock4.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
    window.draw(letterABlock4);

    sf::RectangleShape letterABlock5;
    letterABlock5.setSize({letterWeight, letterABlockSize});
    letterABlock5.setRotation(-letterAAngle);
    letterABlock5.setPosition({defaultWidth - circleRadius, (defaultHeight - circleDiameter) / 2});
    letterABlock5.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
    window.draw(letterABlock5);

    sf::RectangleShape letterABlock6;
    float letterABlock6PositionX = defaultWidth - circleRadius - letterABlockSize / 4 + letterWeight / 2;
    letterABlock6.setSize({letterABlockSize / 2, letterWeight});
    letterABlock6.setPosition({letterABlock6PositionX, defaultHeight / 2});
    letterABlock6.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
    window.draw(letterABlock6);

    window.display();

    sf::sleep(sf::seconds(5));
}