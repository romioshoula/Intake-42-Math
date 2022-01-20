//Triangle_Color_Picker.cpp Rami Wail Shoula
//Line with two vertices showing the shortest distance in 2D space, Line can be rotated
//program closes on esc key or press x

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

float lerp(float start, float end, float t) {
    return  t * (end - start) + start;
}
float invLerp(float start, float end, float v) {
    return (v - start) / (end - start);
}
Color lerpColor(Color start, Color end, float t)
{
    Color color;
    color.r = lerp(start.r, end.r, t);
    color.g = lerp(start.g, end.g, t);
    color.b = lerp(start.b, end.b, t);

    return color;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Full spectrum Triangular color picker");
    window.setVerticalSyncEnabled(true);

    //Creating Black box to print color in
    sf::RectangleShape Black_Box;
    Black_Box.setSize(Vector2f(200, 200));
    Black_Box.setFillColor(Color::Black);
    Black_Box.setOrigin(50, 50);
    Black_Box.setPosition(0, 0);

    //Creating Triangle
    VertexArray Triangular(Triangles, 3);
    Triangular[0].position = Vector2f(0, 800);//(400, 150);
    Triangular[0].color = Color::Red;
    Triangular[1].position = Vector2f(800, 800);//(150, 600);
    Triangular[1].color = Color::Blue;
    Triangular[2].position = Vector2f(400, 0);//(650, 600);
    Triangular[2].color = Color::Green;

    float left, right;
    Color color, color2, color3;
    Clock clock;
    Vector2f mousePosition;

    while (window.isOpen())
    {
        sf::Event event;
        mousePosition = (sf::Vector2f)sf::Mouse::getPosition(window);
        if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) { //closes on esc key
            window.close();
        }
       // if (event.type == Event::MouseButtonPressed) {
           // mousePosition = (Vector2f)Mouse::getPosition(window);
       // }
        while (window.pollEvent(event))
        {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            }
            if (event.type == event.MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left )//sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                cout << "Pressed";
                float il = invLerp(Triangular[0].position.y, Triangular[2].position.y, mousePosition.y);
                color = lerpColor(Color::Red, Color::Green, il);
                float il2 = invLerp(Triangular[1].position.y, Triangular[2].position.y, mousePosition.y);
                color2 = lerpColor(Color::Blue, Color::Green, il);

                left = lerp(Triangular[0].position.x, Triangular[2].position.x, il);
                right = lerp(Triangular[1].position.x, Triangular[2].position.x, il2);

                float il3 = invLerp(left, right, mousePosition.x);
                color3 = lerpColor(color, color2, il3);
                if (il3 >= 0 && il3 <= 1) {
                    Black_Box.setFillColor(color3);
                }
                //if (Mouse::getPosition(window) == (Vector2i)Triangular[0].texCoords) {
                   // Black_Box.setFillColor(Triangular[0].color);
                   // cout << "PFFFFFFFFFF";
                //}
                // Black_Box.setFillColor(Triangular[0].color);
                //mousePosition
            }
        }
        //Black_Box.setFillColor(Color(135, 206, 235));
        //updating screen
        window.clear(Color(135, 206, 235)); //Decimal Code (R,G,B) for skyblue screen
        window.draw(Triangular);
        window.draw(Black_Box);
        window.display();

    }
    return EXIT_SUCCESS;
}