#include<SFML/Graphics.hpp>
#include<bits/stdc++.h>
#include<SFML/Audio.hpp>

using namespace sf;
using namespace std;

int j=1,flagwalk=1,i=1,flagidle=1,idlef=1, upperPunchAnim = 6, punchanim = 5,jumpanim=7;

char idle [50], walk[50] ;
RenderWindow rw(VideoMode(640,480),"VS-first",Style::Close|Style::Resize);
RectangleShape player (Vector2f(100.0f,100.0f));
Texture playtxt,BackgroundTexture;
Music backgroundmusic;

Sprite background;
Vector2u TextureSize;
Vector2u WindowSize;

#include"player.hpp"
//#include"jump.hpp"
#include"punching.hpp"
#include"updatemovement.hpp"

float velocityY = 0;
bool isjumping = false;

int main()
{
    rw.setFramerateLimit(100);
    playtxt.loadFromFile("hulk animation/idle-1.png");
    player.setPosition(0,rw.getSize().y-158);
    Clock clock;
    ///Music
    backgroundmusic.openFromFile("Music samples/backgroundmusic.ogg");
    backgroundmusic.setVolume(50.f);
    backgroundmusic.play();
    backgroundmusic.setLoop(true);
    ///

    ///background image

    BackgroundTexture.loadFromFile("background.png");

    TextureSize = BackgroundTexture.getSize();
    WindowSize = rw.getSize();

    float ScaleX = (float) WindowSize.x / TextureSize.x;
    float ScaleY = (float) WindowSize.y / TextureSize.y;

    background.setTexture(BackgroundTexture);
    background.setScale(ScaleX, ScaleY);


    while (rw.isOpen())
    {
        Event evnt;
        while (rw.pollEvent(evnt))
        {
            switch (evnt.type)
            {
                case Event::Closed:
                    rw.close();
                    break;
                case Event::Resized:
                    break;
                case Event::TextEntered:
                    if(evnt.text.unicode<128)
                        printf("%c",evnt.text.unicode);
//                case Event::KeyReleased: isjumping = false;
//                    break;
            }
        }
        if(idlef==1)
            animationidle(clock);
        else
            animationreidle(clock);

        if(Keyboard::isKeyPressed(Keyboard::D))
        {
            idlef=1;
            animationwalk(clock);
            player.move(1.0f, 0.0f);
        }

        if(Keyboard::isKeyPressed(Keyboard::A))
        {
            idlef=0;
            animationrewalk(clock);
            player.move(-1.f, 0.0f);
       }

        if(Keyboard::isKeyPressed(Keyboard::L)) punchanim = 1;

        if(punchanim < 5)
        {
            if(idlef==1)    animationpunch();
            else    animationrepunch();

            punchanim++;
        }

        if(Keyboard::isKeyPressed(Keyboard::U))   upperPunchAnim=1;
            if(upperPunchAnim < 6)
            {
                if(idlef==1)    animationupperpunch();
                else    animationreupperpunch();
                upperPunchAnim++;
            }

        if(Keyboard::isKeyPressed(Keyboard::W) && player.getPosition().y >= rw.getSize().y-158)
        {
            isjumping = true;
        }
        if(isjumping){
            velocityY=-20;
            isjumping=false;
        }
        player.move(0, velocityY);

        if(player.getPosition().y >= rw.getSize().y-158){
            velocityY = 0;
        }
        else {
            velocityY++;
            if(Keyboard::isKeyPressed(Keyboard::D)) player.move(2, 0);
            if(Keyboard::isKeyPressed(Keyboard::A)) player.move(-2, 0);

        }

        if(clock.getElapsedTime().asMilliseconds()>250.f) clock.restart();
        playtxt.setSmooth(true);
        player.setTexture(&playtxt);
        playtxt.setSmooth(true);
        rw.clear(Color::Black);
        rw.draw(background);
        rw.draw(player);
        rw.display();
    }
}
