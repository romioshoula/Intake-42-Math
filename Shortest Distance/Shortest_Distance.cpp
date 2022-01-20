//Shortest_Distance.cpp Rami Wail Shoula
//Line with two vertices showing the shortest distance in 2D space, Line can be rotated
//program closes on esc key or press x


#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

//Class to handle dragging func, vertices and line
class Point
{
    bool Drag_Func = false;
public:
    sf::CircleShape shape;
    Point()
    {
        shape = sf::CircleShape(15);
        shape.setOrigin(15, 15);
    }
    void setPosition(sf::Vector2f position)
    {
        shape.setPosition(position);
    }

    bool isMouseOver(sf::Vector2f mousePosition)
    {
        return shape.getGlobalBounds().contains(mousePosition);
    }

    void beginDrag(sf::Vector2f mousePosition)
    {
        Drag_Func = isMouseOver(mousePosition);
    }

    void drag(sf::Vector2f mousePosition)
    {
        if (Drag_Func)
        {
            shape.setPosition(mousePosition);
        }
    }

    void endDrag()
    {
        Drag_Func = false;
    }
};
int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Shortest distance (is always a straight line xd)");
    float m, b;
    Point c1;
    Point c0;

    sf::Vector2f p0(400, 700);
    sf::Vector2f p1(700, 400);
    sf::VertexArray lines(sf::LineStrip, 2);
    lines[0].position = p0;
    lines[1].position = p1;
    c0.setPosition(p0);
    c1.setPosition(p1);
    bool isMouseDown = false;

    sf::Vector2f Void_Shpere;
    sf::Vector2f Ending;

    sf::CircleShape shape(20);

    shape.setOrigin(20, 20);

    shape.setFillColor(sf::Color(255, 255, 0)); //Decimal Code (R,G,B) for yellow color

    while (window.isOpen())
    {
        sf::Vector2f mousePosition = (sf::Vector2f)sf::Mouse::getPosition(window);
        if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) { //closes on esc key
            window.close();
        }
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                isMouseDown = true;

                c0.beginDrag(mousePosition);
                c1.beginDrag(mousePosition);
            }

            if (event.type == sf::Event::MouseButtonReleased)
            {
                isMouseDown = false;
                c0.endDrag();
                c1.endDrag();

            }
        }

        if (isMouseDown)
        {

            c0.drag(mousePosition);
            c1.drag(mousePosition);
            p0 = c0.shape.getPosition();
            p1 = c1.shape.getPosition();
            lines[0].position = p0;
            lines[1].position = p1;
        }

        m = (p1.y - p0.y) / (p1.x - p0.x); //slope
        b = p0.y - (p0.x * ((p1.y - p0.y) / (p1.x - p0.x))); // b
        Ending = (sf::Vector2f)sf::Mouse::getPosition(window);
        Void_Shpere.x = (Ending.x + m * (Ending.y - b)) / ((m * m) + 1);
        Void_Shpere.y = ((m * (Ending.x + m * Ending.y)) + b) / ((m * m) + 1);

        shape.setPosition(Void_Shpere);

        window.clear(Color(135, 206, 235)); //Decimal Code (R,G,B) for skyblue screen
        window.draw(lines);
        window.draw(c0.shape);
        window.draw(c1.shape);
        window.draw(shape);
        window.display();
    }
    return EXIT_SUCCESS;
}