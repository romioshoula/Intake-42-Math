//Parallax_Scaling_Jump.cpp Rami Wail Shoula
//program closes on esc key or press x
//jump with spacebar

//Use quadratic function f(t)=at^2+bt+c to simulate jumping. Jump duration should be 1 second.
//Get the values of a, band cand use them to make a circle or a sprite jump when you press the spacebar.
//Use jump and idle sprite sheets

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

//Jump tasks
float jump(float t) {
    float i = 0;
    i = (240 * t * t) - (240 * t) + 150;
    return i;
}

//Animating jump sequence
class Animation
{
public:
    Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
    ~Animation();
    void update(int row, float deltaTime);
public:
    sf::IntRect uvRect;
private:
    sf::Vector2u imageCount;
    sf::Vector2u currentImage;
    float totalTime;
    float switchTime;
};

Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
{
    this->imageCount = imageCount;
    this->switchTime = switchTime;
    totalTime = 0.0f;
    currentImage.x = 0;
    uvRect.width = texture->getSize().x / float(imageCount.x);
    uvRect.height = texture->getSize().y / float(imageCount.y);
}

Animation::~Animation()
{
}

void Animation::update(int row, float deltaTime)
{
    currentImage.y = row;
    totalTime += deltaTime;
    if (totalTime >= switchTime)
    {
        totalTime -= switchTime;
        currentImage.x++;

        if (currentImage.x >= imageCount.x)
            currentImage.x = 0;
    }
    uvRect.left = currentImage.x * uvRect.width;
    uvRect.top = currentImage.y * uvRect.height;
}

//"parallax-demon-woods-[].png"
int main()
{
    //(1920, 1080)
    sf::RenderWindow window(sf::VideoMode(480, 272), "Parallax Scaling Jump");
    window.setVerticalSyncEnabled(true);

    Textures tex;
    tex.LoadTextures();

    sf::Clock clock;  //parralax clock
    sf::Clock clock1; //Jumping clock

    //Jump Tasks
    RectangleShape player(Vector2f(150, 150));
    player.setPosition(150, 150);
    sf::Texture playertext;
    playertext.loadFromFile("run.png");
    player.setTexture(&playertext);
    Animation animation(&playertext, Vector2u(8, 1), 0.05f);

    float deltatime = 0.0f;
    float t = 0.5f;

    deltatime = clock.restart().asSeconds(); //restarting jumping (limb movement) animation
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

        if (event.key.code == Keyboard::Space)
        {
            t = clock1.getElapsedTime().asSeconds();
            if (t <= 1) {
                player.setPosition(player.getPosition().x, jump(t));
            }
        }
        else {
            clock1.restart();
        }
        animation.update(0, deltatime);
        player.setTextureRect(animation.uvRect);
        float elapsed = clock.getElapsedTime().asSeconds();

        clock.restart();
        //clock1.restart();

        //Animating Jumping sequence

        // Clear screen
        window.clear();

        tex.DrawBgnd(elapsed, window);

        //the jumping player
        window.draw(player);

        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}
