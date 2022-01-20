//Parallax_Scaling.cpp Rami Wail Shoula

//#include<iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <assert.h>
#include <sstream>
//#include <array>
//#include<math.h>

using namespace sf;
using namespace std;

//all the textures we need
struct Textures
{
    //give each texture an ID
    typedef enum {
        BACK0 = 0, //large backdrop sprites
        BACK1 = 1,
        BACK2 = 2,
        BACK3 = 3
    } Tex;
    static const int MAX_TEXTURES = 4;
    sf::Texture tex[MAX_TEXTURES];					//a variable to hold each texture
    float bgndSpds[MAX_TEXTURES] = { 0,0,0,0 };	//keep track of the scroll position of each bgnd layer

    //given a texture ID, get the actual texture
    sf::Texture& Get(Tex id) {
        return tex[static_cast<int>(id)];
    }

    void LoadTextures();

    void ScrollBgnd(Tex texId, sf::RenderWindow& window, int inc);

    void DrawBgnd(float elapsed, sf::RenderWindow& window);

};

namespace GC
{
    //background
    const float BACK_SPEED = 10;		//start speed for scrolling
    const float BACK_LAYER_SPEEDINC = 7;//each layer is a bit faster towards the front

    const char ESCAPE_KEY{ 27 };
}

//using namespace GC;

void Textures::LoadTextures()
{
    stringstream ss;
    for (int i = 0; i < MAX_TEXTURES; ++i)
    {
        ss.str("");
        ss << "parallax-demon-woods-" << i << ".png";

        Texture& t = Get(static_cast<Tex>(i));
        if (!t.loadFromFile(ss.str()))
            assert(false);
        t.setRepeated(true);
    }
}

void Textures::ScrollBgnd(Tex texId, sf::RenderWindow& window, int inc)
{
    sf::Sprite spr(Get(texId));
    sf::IntRect scroll = spr.getTextureRect();
    scroll.left += inc;
    spr.setTextureRect(scroll);
    spr.setScale(window.getSize().x / (float)scroll.width, window.getSize().y / (float)scroll.height);
    spr.setPosition(0, 0);
    window.draw(spr);
}

void Textures::DrawBgnd(float elapsed, sf::RenderWindow& window)
{
    //background order of sprites
    Textures::Tex ids[MAX_TEXTURES]{
        Textures::BACK3,
        Textures::BACK2,
        Textures::BACK0,
        Textures::BACK1,
    };

    float spd = GC::BACK_SPEED * elapsed;
    for (int i = 0; i < MAX_TEXTURES; ++i)
    {
        bgndSpds[i] += spd;
        ScrollBgnd(ids[i], window, (int)bgndSpds[i]);
        spd += GC::BACK_LAYER_SPEEDINC * elapsed;
    }
}

//"parallax-demon-woods-[].png"
int main()
{
    //(1920, 1080)
    sf::RenderWindow window(sf::VideoMode(480, 272), "Parallax Scaling");
    window.setVerticalSyncEnabled(true);

    Textures tex;
    tex.LoadTextures();

    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event event;
        //while (window.pollEvent(event))
        //{
        //    switch (event.type) {
        //    case sf::Event::Closed:
        //        window.close();
        //        break;
        //    }
        //}

        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::TextEntered)
            {
                if (event.text.unicode == GC::ESCAPE_KEY) //so window closes on escape key
                    window.close();
            }
        }
        
        float elapsed = clock.getElapsedTime().asSeconds();
        clock.restart();

        // Clear screen
        window.clear();

        tex.DrawBgnd(elapsed, window);

        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}
