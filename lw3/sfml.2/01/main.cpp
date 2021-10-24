#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Moving ball");
    sf::Clock clock;

    sf::CircleShape shape(20);
    shape.setPosition({WINDOW_WIDTH / 2 - 20, WINDOW_HEIGHT / 2 - 20});
    shape.setFillColor(sf::Color(0xBF, 0xBF, 0xBF));

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

        const sf::Vector2f speed = {50.f, 100.f};
        const float deltaTime = clock.restart().asSeconds();

        sf::Vector2f position = shape.getPosition();
        position += speed * deltaTime;
        shape.setPosition(position);

        window.clear(sf::Color(0x0F, 0x0F, 0x0F));
        window.draw(shape);
        window.display();
    }
}