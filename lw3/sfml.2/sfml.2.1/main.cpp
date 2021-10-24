#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;
constexpr float BALL_SIZE = 20;

int main()
{
    sf::Vector2f speed = {150.f, 0};
    float defaultPositionY = 300;

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Moving ball with jumps by walls");
    sf::Clock clock;

    const sf::Vector2f position = {0, defaultPositionY};
    float wavePhase = 0;

    sf::CircleShape shape(BALL_SIZE);
    shape.setFillColor(sf::Color(0xBF, 0xBF, 0xBF));
    shape.setPosition(position);

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
        constexpr float amplitudeSpeadY = 280.f;
        constexpr float periodY = 1;

        wavePhase = wavePhase + deltaTime * float(2 * M_PI);
        if (wavePhase >= (2 * M_PI) * periodY)
        {
            wavePhase = wavePhase - (2 * M_PI) * periodY;
        }

        std::printf("%f\n", wavePhase);
        speed.y = amplitudeSpeadY * std::cos(wavePhase / periodY);

        sf::Vector2f position = shape.getPosition();
        position = position + speed * deltaTime;

        if ((position.x + 2 * BALL_SIZE >= WINDOW_WIDTH) && (speed.x > 0))
        {
            speed.x = -speed.x;
        }
        if ((position.x < 0) && (speed.x < 0))
        {
            speed.x = -speed.x;
        }

        shape.setPosition(position);

        window.clear(sf::Color(0x0F, 0x0F, 0x0F));
        window.draw(shape);
        window.display();
    }
}