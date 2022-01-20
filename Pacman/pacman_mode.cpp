//pacman_mode.cpp Rami Wail Shoula
//W,S,A,D,Up,Down,Left,Right keys all control pac while he always goes to right by default
//program closes on esc key or press x

#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;
#define PI 3.14
#define RAD PI/180 //convertion

ConvexShape Pacman(Vector2f center, float radius, float startpoint, int rotatecon) {
    float angle = startpoint;
    float pointscount = 360 - startpoint;
    float DeltaAngle = (pointscount - angle) / 30;
    float theta = 0;
    float offset = 90 * RAD;
    ConvexShape circle;
    circle.setPointCount(31);
    for (float i = 0; i < 30; i++)
    {
        Vector2f point;
        theta = angle * RAD;
        offset = 90 * RAD;
        point.x = center.x + radius * cos(theta + rotatecon * offset);
        point.y = center.y + radius * sin(theta + rotatecon * offset);
        angle += DeltaAngle;
        circle.setPoint(i, point);
    }
    return circle;
}
int main() {
    RenderWindow window(VideoMode(800, 800), "PacMan mode", Style::Default);
    sf::Clock clock;
    float t;
    ConvexShape shape;
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
        //Original is to the right _ default case
        t = clock.getElapsedTime().asSeconds();
        shape = Pacman(Vector2f(0, 0), 300, 30 * abs(sin(15 * t)), 0);
        shape.setOrigin(-400, -400);

        if ( Keyboard::isKeyPressed(Keyboard::Key::Escape) ) { //closes on esc key
            window.close();
        }
        else if ( ( Keyboard::isKeyPressed(Keyboard::Key::Down) ) || (Keyboard::isKeyPressed(Keyboard::Key::S)) ){
            shape.rotate(90);
            shape.setOrigin(-400, 400); //S_Down
        }
        else if ((Keyboard::isKeyPressed(Keyboard::Key::Right)) || (Keyboard::isKeyPressed(Keyboard::Key::D))) {
            shape.rotate(0);
            shape.setOrigin(-400, -400); //D_Right
        }
        else if ((Keyboard::isKeyPressed(Keyboard::Key::Up)) || (Keyboard::isKeyPressed(Keyboard::Key::W))) {
            shape.rotate(-90);
            shape.setOrigin(400, -400); //W_Up
        }
        else if ((Keyboard::isKeyPressed(Keyboard::Key::Left)) || (Keyboard::isKeyPressed(Keyboard::Key::A))) {
            shape.rotate(-180);
            shape.setOrigin(400, 400); //W_Up
        }
        shape.setFillColor(Color(255, 255, 0)); //Decimal Code (R,G,B) for yellow color for pacman
        window.clear(Color(135, 206, 235)); //Decimal Code (R,G,B) for skyblue screen
        window.draw(shape);
        window.display();
    }
}