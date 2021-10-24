#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;
    constexpr float BALL_SIZE = 20;

    sf::Vector2f speed = {1500.f, 2400.f};

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Moving ball with jumps by walls");
    sf::Clock clock;

    sf::CircleShape shape(BALL_SIZE);
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

        const float deltaTime = clock.restart().asSeconds();

        sf::Vector2f position = shape.getPosition();
        position += speed * deltaTime;
        if ((position.x + 2 * BALL_SIZE >= WINDOW_WIDTH) && (speed.x > 0))
        {
            speed.x = -speed.x;
        }
        if ((position.x < 0) && (speed.x < 0))
        {
            speed.x = -speed.x;
        }
        if ((position.y + 2 * BALL_SIZE >= WINDOW_HEIGHT) && (speed.y > 0))
        {
            speed.y = -speed.y;
        }
        if ((position.y < 0) && (speed.y < 0))
        {
            speed.y = -speed.y;
        }

        shape.setPosition(position);

        window.clear(sf::Color(0x0F, 0x0F, 0x0F));
        window.draw(shape);
        window.display();
    }
}