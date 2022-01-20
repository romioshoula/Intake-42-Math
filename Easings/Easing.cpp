//Easing.cpp Rami Wail Shoula
//all easing exmples are obtained from the lec. link (http://robertpenner.com/easing/) Robert Penner's easing equations;//

#include <SFML/Graphics.hpp>

//Kindly uncomment the easing method u want to try and comment the other two 
//I implemented Cubic, Expo, ad Quad easings, respectively

//Cubic easing ofPennerEasing
/*float easeIn(float t, float b, float c, float d) {
    return c * (t /= d) * t * t + b;
}
float easeOut(float t, float b, float c, float d) {
    return c * ((t = t / d - 1) * t * t + 1) + b;
}

float easeInOut(float t, float b, float c, float d) {
    if ((t /= d / 2) < 1) return c / 2 * t * t * t + b;
    return c / 2 * ((t -= 2) * t * t + 2) + b;
}
*/

//Expo easing ofPennerEasing
/*float easeIn(float t, float b, float c, float d) {
    return (t == 0) ? b : c * pow(2, 10 * (t / d - 1)) + b;
}
float easeOut(float t, float b, float c, float d) {
    return (t == d) ? b + c : c * (-pow(2, -10 * t / d) + 1) + b;
}

float easeInOut(float t, float b, float c, float d) {
    if (t == 0) return b;
    if (t == d) return b + c;
    if ((t /= d / 2) < 1) return c / 2 * pow(2, 10 * (t - 1)) + b;
    return c / 2 * (-pow(2, -10 * --t) + 2) + b;
}
*/

//Quad easing ofPennerEasing
float easeIn(float t, float b, float c, float d) {
    return c * (t /= d) * t + b;
}
float easeOut(float t, float b, float c, float d) {
    return -c * (t /= d) * (t - 2) + b;
}

float easeInOut(float t, float b, float c, float d) {
    if ((t /= d / 2) < 1) return ((c / 2) * (t * t)) + b;
    return -c / 2 * (((t - 2) * (--t)) - 1) + b;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Easing Example");
    sf::CircleShape shape(15);

    shape.setOrigin(15, 15);

    shape.setFillColor(sf::Color::Green);

    sf::Clock clock;
    float t = 0;

    sf::Vector2f startPosition(15, 500);
    sf::Vector2f endPosition(800 - 15, 500);

    sf::Vector2f position = startPosition;

    sf::Vector2f deltaPosition = endPosition - startPosition;

    float d = 1;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                clock.restart();
                endPosition = (sf::Vector2f)sf::Mouse::getPosition(window);
                startPosition = shape.getPosition();
                deltaPosition = endPosition - startPosition;
            }
        }

        t = clock.getElapsedTime().asSeconds();

        if (t <= d)
        {
            position.x = easeInOut(t, startPosition.x, deltaPosition.x, d);
            position.y = easeInOut(t, startPosition.y, deltaPosition.y, d);
        }

        shape.setPosition(position);

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}