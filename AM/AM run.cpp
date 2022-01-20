//AM_run.cpp Rami Wail Shoula
//Make a circle move between two points using cos(t)sin(f*t) function.
//program closes on esc key or press x


#include <SFML/Graphics.hpp>
using namespace sf;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 500), "AM run");

    sf::CircleShape shape;
    shape.setRadius(50);
    shape.setOrigin(25, 25);
    shape.setFillColor(sf::Color::Magenta);

    sf::Vector2f startPosition(500, 200);
    sf::Vector2f position;

    float A = (900 - 100) / 2.0f;
    float F = 5;

    sf::Clock clock;
    float t;

    position = startPosition;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) { //closes on esc key
            window.close();
        }

        t = clock.getElapsedTime().asSeconds();
        position.x = startPosition.x + A * cos(t)*sin(F * t); //cos(t)sin(f*t) function.
        shape.setPosition(position);

        //Displaying
        window.clear();
        window.clear(Color(135, 206, 235)); //Decimal Code (R,G,B) for skyblue screen
        window.draw(shape);
        window.display();
    }
    return 0;
}