#include<SFML/Graphics.hpp>
#include<bits/stdc++.h>
#include<SFML/Audio.hpp>

using namespace sf;
using namespace std;

int j=1,flagwalk=1,i=1,flagidle=1,idlef=1, upperPunchAnim = 6, punchanim = 5,jumpanim=7;

char idle [50], walk[50] ;
RenderWindow rw(VideoMode(800,600),"VS-first",Style::Close|Style::Resize);
RectangleShape player (Vector2f(100.0f,100.0f));
Texture playtxt,BackgroundTexture,guli,example;

Music backgroundmusic;

Sprite background;
Vector2u TextureSize;
Vector2u WindowSize;

#include"player.hpp"
#include"punching.hpp"

float velocityY = 0.0;
bool isjumping = false;

///Menu screen
#include"menu.hpp"

///Menu End


///Eenemy

void enemy(RenderWindow window)
{

}

class bullet
{
public:
    Sprite shape;
    bullet(Texture *texture,Vector2f pos)
    {
        pos.y=pos.y+20;
        shape.setTexture(*texture);
        shape.setScale(0.8,0.8f);
        shape.setPosition(pos);
    }

};


int main()
{
    rw.setFramerateLimit(100);
    playtxt.loadFromFile("hulk animation/idle-1.png");
    player.setPosition(0,rw.getSize().y-158);
    player.setScale(1.3,1.3);
    Clock clock,btime;
    ///Music
    backgroundmusic.openFromFile("Music samples/backgroundmusic.ogg");
    backgroundmusic.setVolume(50.f);
    backgroundmusic.play();
    backgroundmusic.setLoop(true);
    float time=0.0;
    ///
    vector<bullet> magazine;

    ///background image
    BackgroundTexture.loadFromFile("background.png");
    Sprite exmp(example);

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
            }
        }
        while(IsMenuStarted) menuscreen(rw);
        if(Keyboard::isKeyPressed(Keyboard::Escape)) IsMenuStarted = true;


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

        if(Keyboard::isKeyPressed(Keyboard::L))
            punchanim = 1;

        if(punchanim < 5)
        {
            if(idlef==1)
                animationpunch();
            else
                animationrepunch();

            punchanim++;
        }

        if(Keyboard::isKeyPressed(Keyboard::U))
            upperPunchAnim=1;
        if(upperPunchAnim < 6)
        {
            if(idlef==1)
                animationupperpunch();
            else
                animationreupperpunch();
            upperPunchAnim++;
        }

        ///jumping logic
        if(Keyboard::isKeyPressed(Keyboard::W) && player.getPosition().y >= rw.getSize().y-158)
        {
            isjumping = true;
        }
        if(isjumping)
        {
            velocityY=-20;
            isjumping=false;
        }
        player.move(0, velocityY);

        if(player.getPosition().y >= rw.getSize().y-158)
        {
            velocityY=0;
        }
        else
        {
            velocityY++;
            if(Keyboard::isKeyPressed(Keyboard::D))
                player.move(2, 0);
            if(Keyboard::isKeyPressed(Keyboard::A))
                player.move(-2, 0);

        }
        ///END
        ///bullet
        guli.loadFromFile("fire_blue.png");
        example.loadFromFile("idle-4.png");

        time=btime.getElapsedTime().asSeconds();
        exmp.setPosition(150.f,150.f);

        if(time > 1.0)
        {
            magazine.push_back(bullet(&guli,Vector2f(exmp.getPosition())));
            time=0.0;
            btime.restart();
        }

        for(int kl=0;kl < magazine.size();kl++)
        {
            magazine[kl].shape.move(2.f,0.f);
            if(magazine[kl].shape.getPosition().x > rw.getSize().x)
            {
                magazine.erase(magazine.begin()+kl);
            }
        }



        ///end

        if(clock.getElapsedTime().asMilliseconds()>250.f)
            clock.restart();

        playtxt.setSmooth(true);
        player.setTexture(&playtxt);
        playtxt.setSmooth(true);
        rw.clear(Color::Black);
        rw.draw(background);
        rw.draw(player);
        rw.draw(exmp);
//        for(int kl=0;kl < magazine.size() ;kl++)
//        {
//            rw.draw(magazine[kl].shape);
//        }
        rw.display();
    }
    return 0;
}

