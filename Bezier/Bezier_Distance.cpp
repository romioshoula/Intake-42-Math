//Bezier_Distance.cpp Rami Wail Shoula
//Line with two vertices showing the shortest distance in 2D space, Line can be rotated
//program closes on esc key or press x

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

//Class to handle dragging func, vertices and line
class Point
{
public:
    bool isDrag = false;

    CircleShape shape;

    Point()
    {
        shape = CircleShape(15);
        shape.setOrigin(15, 15);
    }

    void setPosition(Vector2f position)
    {
        shape.setPosition(position);
    }

    bool isMouseOver(Vector2f cPos)
    {
        return shape.getGlobalBounds().contains(cPos);
    }

    void beginDrag(Vector2f cPos)
    {
        isDrag = isMouseOver(cPos);
    }

    void drag(Vector2f cPos)
    {
        if (isDrag)
        {
            shape.setPosition(cPos);
        }
    }

    void endDrag()
    {
        isDrag = false;
    }
};


float lerp(float start, float end, float t)
{
    return t * (end - start) + start;
}

Color lerpColor(Color start, Color end, float t)
{
    Color color;

    color.r = lerp(start.r, end.r, t);
    color.g = lerp(start.g, end.g, t);
    color.b = lerp(start.b, end.b, t);

    return color;
}

Vector2f lerpPosition(Vector2f start, Vector2f end, float t)
{
    Vector2f position;

    position.x = lerp(start.x, end.x, t);
    position.y = lerp(start.y, end.y, t);

    return position;
}

VertexArray getBezierCurve(Vector2f p0, Vector2f p1, Vector2f p2, Vector2f p3)
{
    int points = 100; //No. of points on lerp line

    float delta = 1.0f / points;

    float t = 0;

    VertexArray curve(LineStrip, points);

    for (size_t i = 0; i < points; i++)
    {
        Vector2f p01 = lerpPosition(p0, p1, t);
        Vector2f p12 = lerpPosition(p1, p2, t);
        Vector2f p23 = lerpPosition(p2, p3, t);

        curve[i].position = lerpPosition(p01, p23, t);

        curve[i].color = lerpColor(Color(255, 0, 0), Color(255, 255, 0) , t); //lerp color from Decimal Code (R,G,B) Red to yellow color 

        t += delta;
    }

    return curve;
}

int main()
{
    RenderWindow window(VideoMode(700, 700), "Bezier Distance xd");

    Vector2f p0(30, 700 - 60);
    Vector2f p1(100, 60);
    Vector2f p2(600, 60);
    Vector2f p3(700 - 60, 700 - 60);

    VertexArray lines(LineStrip, 4);

    lines[0].position = p0;
    lines[1].position = p1;
    lines[2].position = p2;
    lines[3].position = p3;

    Point c0;
    c0.setPosition(p0);

    Point c1;
    c1.setPosition(p1);

    Point c2;
    c2.setPosition(p2);

    Point c3;
    c3.setPosition(p3);

    bool mouseDown = false;

    while (window.isOpen())
    {
        Vector2f cPos = (Vector2f)Mouse::getPosition(window);

        if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) { //closes on esc key
            window.close();
        }

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonPressed)
            {
                mouseDown = true;

                c0.beginDrag(cPos);
                c1.beginDrag(cPos);
                c2.beginDrag(cPos);
                c3.beginDrag(cPos);
            }

            if (event.type == Event::MouseButtonReleased)
            {
                mouseDown = false;
                c0.endDrag();
                c1.endDrag();
                c2.endDrag();
                c3.endDrag();
            }
        }

        if (mouseDown)
        {
            //dragging on mouse hold
            c0.drag(cPos);
            c1.drag(cPos);
            c2.drag(cPos);
            c3.drag(cPos);

            //getting positions
            p0 = c0.shape.getPosition();
            p1 = c1.shape.getPosition();
            p2 = c2.shape.getPosition();
            p3 = c3.shape.getPosition();

            //resetting positions in array
            lines[0].position = p0;
            lines[1].position = p1;
            lines[2].position = p2;
            lines[3].position = p3;

        }
        //Updating window objects
        window.clear(Color(135, 206, 235)); //Decimal Code (R,G,B) for skyblue screen
        window.draw(lines);
        window.draw(getBezierCurve(p0, p1, p2, p3));
        window.draw(c0.shape);
        window.draw(c1.shape);
        window.draw(c2.shape);
        window.draw(c3.shape);
        window.display();
    }
    return EXIT_SUCCESS;
}