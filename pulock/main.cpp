#include<SFML/Graphics.hpp>
#include<bits/stdc++.h>

using namespace sf;
using namespace std;

int j=1,flagwalk=1,i=1,flagidle=1,idlef=1;

char idle [50], walk[50];
RenderWindow rw(VideoMode(640,480),"VS-first",Style::Close|Style::Resize);
RectangleShape player (Vector2f(100.0f,100.0f));
Texture playtxt;


void animationidle(Clock clock)
{
    if(clock.getElapsedTime().asMilliseconds()>250.f)
    {
        if(i>4)
        {
            flagidle=1;
            i=3;
        }
        if(i<1)
        {
            flagidle =0;
            i=2;
        }
        sprintf (idle,"hulk animation/idle-%d.png", i);
        playtxt.loadFromFile(idle);
        if(flagidle==1) i--;
        else i++;
    }
}

void animationreidle(Clock clock)
{
    if(clock.getElapsedTime().asMilliseconds()>250.f)
    {
        if(i>4)
        {
            flagidle=1;
            i=3;
        }
        if(i<1)
        {
            flagidle =0;
            i=2;
        }
        sprintf (idle,"hulk animation/reidle-%d.png", i);
        playtxt.loadFromFile(idle);
        if(flagidle==1) i--;
        else i++;
    }
}

void animationwalk(Clock clock)
{
    if(clock.getElapsedTime().asMilliseconds()>250.f)
    {
        if(j>6)
        {
            flagwalk=1;
            j=5;
        }
        if(j<1)
        {
            flagwalk=0;
            j=2;
        }
        sprintf (walk,"hulk animation/walk-%d.png", j);
        playtxt.loadFromFile(walk);
        if(flagwalk==1) j--;
        else j++;
    }
}

void animationrewalk(Clock clock)
{
    if(clock.getElapsedTime().asMilliseconds()>250.f)
    {
        if(j>6)
        {
            flagwalk=1;
            j=5;
        }
        if(j<1)
        {
            flagwalk=0;
            j=2;
        }
        sprintf (walk,"hulk animation/rewalk-%d.png", j);
        playtxt.loadFromFile(walk);
        if(flagwalk==1) j--;
        else j++;
    }
}

void animationpunch()
{
    char punch[50];

    Clock clock;

    for(int i=1; i<5; i++)
    {
        rw.clear(Color::Black);
        sprintf (punch,"hulk animation/punch-%d.png", i);
        playtxt.loadFromFile(punch);
        rw.draw(player);
        rw.display();
        while(clock.getElapsedTime().asMilliseconds()<100.f);
        clock.restart();
    }
}

void animationupperpunch()
{
    char upperpunch[50];

    Clock clock;

    for(int i=1; i<6; i++)
    {
        rw.clear(Color::Black);
        sprintf (upperpunch,"hulk animation/upperpunch-%d.png", i);
        playtxt.loadFromFile(upperpunch);
        rw.draw(player);
        rw.display();
        while(clock.getElapsedTime().asMilliseconds()<100.f);
        clock.restart();
    }

}

int main()
{
    rw.setFramerateLimit(100);
    playtxt.loadFromFile("hulk animation/idle-1.png");
    player.setPosition(0,rw.getSize().y/2);
    Clock clock;

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
        if(idlef==1)
        animationidle(clock);

        else
            animationreidle(clock);

        if(Keyboard::isKeyPressed(Keyboard::D))
        {
            idlef=1;
            animationwalk(clock);
            player.move(1.f, 0.0f);
        }

        if(Keyboard::isKeyPressed(Keyboard::A))
        {
            idlef=0;
            animationrewalk(clock);
            player.move(-1.f, 0.0f);
       }
        if(Keyboard::isKeyPressed(Keyboard::L)) animationpunch();

        if(Keyboard::isKeyPressed(Keyboard::U)) animationupperpunch();

        if(clock.getElapsedTime().asMilliseconds()>250.f) clock.restart();

        player.setTexture(&playtxt);
        rw.clear(Color::Black);
        rw.draw(player);
        rw.display();
    }
}
