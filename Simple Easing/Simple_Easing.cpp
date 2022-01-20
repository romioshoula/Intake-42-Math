//Simple_Easing.cpp Rami Wail Shoula
//program closes on esc key or press x
//Create a group of circles. The first circle follows the mouse and other circles follow each other using simple easing.


//#include<iostream>
#include <SFML/Graphics.hpp>
//#include <string>
//#include <assert.h>
//#include <sstream>
//#include <array>
//#include<math.h>

using namespace sf;
//using namespace std;

int main()
{
    RenderWindow window(sf::VideoMode(1100, 1100), "Simple Easing (made simple by SFML)");
    CircleShape shape[8];
    Vector2f position[8];
    Vector2f destination[8];
    for (int i = 0; i < 8; i++)
    {
        shape[i].setRadius(20);
        shape[i].setOrigin(15, 15);
        shape[i].setFillColor(Color::Magenta);
    }

    float ease = 0.01;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) { //closes on esc key
                window.close();
            }
        }

        //Position handling
        Vector2f deltaPosition[8];
        destination[0] = (Vector2f)Mouse::getPosition(window);
        deltaPosition[0] = ease * (destination[0] - shape[0].getPosition());
        position[0] += deltaPosition[0];
        shape[0].setPosition(position[0]);

        //Position Updating
        for (int i = 1; i < 8; i++)
        {
            destination[i] = shape[i - 1].getPosition();
            deltaPosition[i] = ease * (destination[i] - shape[i].getPosition());
            position[i] += deltaPosition[i];
            shape[i].setPosition(position[i]);
        }
        window.clear();
        window.clear(Color(135, 206, 235)); //Decimal Code (R,G,B) for skyblue screen
        for (int i = 0; i < 8; i++)
        {
            window.draw(shape[i]);
        }
        window.display();
    }
    return EXIT_SUCCESS;
}