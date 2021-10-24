#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;
constexpr float BALL_SIZE = 20;

int main()
{
    sf::Vector2f speed = {1500.f, 2400.f};

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Moving ball with jumps by walls");
    sf::Clock clock;

    const sf::Vector2f position = {10, 350};

    sf::CircleShape shape(BALL_SIZE);
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

        constexpr float speedX = 100.f;
        constexpr float amplitudeY = 80.f;
        constexpr float periodY = 2;

        const float time = clock.getElapsedTime().asSeconds();
        const float wavePhase = time * float(2 * M_PI);
        const float x = speedX * time;
        const float y = amplitudeY * std::sin(wavePhase / periodY);
        const sf::Vector2f offset = {x, y};

        shape.setPosition(position + offset);

        window.clear(sf::Color(0x0F, 0x0F, 0x0F));
        window.draw(shape);
        window.display();
    }
}