//Field of View FOV.cpp Rami Wail Shoula
//Field of view programm in C++ SFML where FOV changes color from Green (0, 255, 0) to red (255, 0, 0) upon detecting enemy
//Program works with WASD keys or arrow keys (UP,DOWN,LEFT,RIGHT)
//program closes on esc key or press x

//#includes
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

//namespaces
using namespace std;
using namespace sf;

//definitions
#define PI 22/7.0f

//functions
ConvexShape getCircle(Vector2f center, float radius, float Mouse_Angle, float Rotation_Angle)
{
    int No_Of_Points = 100;
    float Detla_Angle = (2.0f * PI - (2 * PI / Mouse_Angle)) / (No_Of_Points-3);
    float angle = Rotation_Angle;
    ConvexShape circle(100);
    circle.setPoint(0, Vector2f(center.x, center.y));

    for (size_t i = 1; i < No_Of_Points; i++)
    {
        float x = radius * cos(angle + (PI / Mouse_Angle)) + center.x;
        float y = radius * sin(angle + (PI / Mouse_Angle)) + center.y;
        circle.setPoint(i, Vector2f(x, y));
        angle += Detla_Angle;
    }
    return circle;
}

float getMagnitude(Vector2f p0, Vector2f p1) {
    return sqrt(((p0.x - p1.x) * (p0.x - p1.x)) + ((p0.y - p1.y) * (p0.y - p1.y)));
}

//driving function
int main()
{
    srand((unsigned)time(NULL));
    RenderWindow window(VideoMode(900, 900), "Field of View FOV (Beware of enemy)");
    CircleShape circle1(40);
    circle1.setOrigin(40, 40);
    circle1.setPosition(3 * window.getSize().x / 4, window.getSize().y / 2);
    circle1.setFillColor(Color::Magenta);

    ConvexShape shape = getCircle((Vector2f)circle1.getPosition(), 150, 10, 0);
    shape.setFillColor(Color::Transparent);

    CircleShape circle2(40);
    circle2.setPosition(((circle1.getPosition().x - 300) * ((float)rand() / RAND_MAX)), ((window.getSize().y - 300) * ((float)rand() / RAND_MAX)));
    circle2.setFillColor(Color::Yellow);

    while (window.isOpen())
    {
        if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) { //closes on esc key
            window.close();
        }
        float circle_distance = getMagnitude(circle1.getPosition(), (Vector2f)Mouse::getPosition(window));
        float x_loc_mouse = circle1.getPosition().x - Mouse::getPosition(window).x;
        float angle = acos(x_loc_mouse / circle_distance);
        if (Mouse::getPosition(window).y > circle1.getPosition().y) angle = -angle;
        shape = getCircle((Vector2f)circle1.getPosition(), 130, 1.3, angle);
        shape.setFillColor(Color::Cyan);
        Event event;
        float x1 = circle2.getPosition().x + circle2.getRadius();
        float y1 = circle2.getPosition().y + circle2.getRadius();

        if (shape.getGlobalBounds().contains(Vector2f(x1, y1))) {
            shape.setFillColor(Color::Red);
        }
        else
        {
            shape.setFillColor(Color::Green);
        }
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed)
            {

                switch (event.key.code)
                {
                case Keyboard::Right:
                    circle1.setPosition(circle1.getPosition() + Vector2f(5.0f, 0));
                    break;
                case Keyboard::D:
                    circle1.setPosition(circle1.getPosition() + Vector2f(5.0f, 0));
                    break;
                case  Keyboard::Left:
                    circle1.setPosition(circle1.getPosition() + Vector2f(-5.0f, 0));
                    break;
                case  Keyboard::A:
                    circle1.setPosition(circle1.getPosition() + Vector2f(-5.0f, 0));
                    break;
                case  Keyboard::Down:
                    circle1.setPosition(circle1.getPosition() + Vector2f(0, 5.0f));
                    break;
                case  Keyboard::S:
                    circle1.setPosition(circle1.getPosition() + Vector2f(0, 5.0f));
                    break;
                case  Keyboard::Up:
                    circle1.setPosition(circle1.getPosition() + Vector2f(0, -5.0f));
                    break;
                case  Keyboard::W:
                    circle1.setPosition(circle1.getPosition() + Vector2f(0, -5.0f));
                    break;
                default:
                    break;
                }
            }
        }
        //window.clear(Color(255, 255, 255, 255)); //Decimal Code (R,G,B) for black screen
        window.clear(Color(135, 206, 235)); //Decimal Code (R,G,B) for skyblue screen
        window.draw(circle2);
        window.draw(shape);
        window.draw(circle1);
        window.display();
    }
    return EXIT_SUCCESS;
}