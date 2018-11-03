#include<SFML/Graphics.hpp>
#include<bits/stdc++.h>

using namespace sf;
using namespace std;

char idle [50], walk[50];
int i=1,j=1,flagidle=1,flagwalk=1;
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

int main()
{
    rw.setFramerateLimit(50);
    playtxt.loadFromFile("hulk animation/idle-1.png");
    player.setPosition(rw.getSize().x/2,rw.getSize().y/2);
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
        animationidle(clock);

        if(Keyboard::isKeyPressed(Keyboard::D))
        {
            animationwalk(clock);
            player.move(0.5f, 0.0f);
        }

        if(clock.getElapsedTime().asMilliseconds()>250.f) clock.restart();

        player.setTexture(&playtxt);
        rw.clear(Color::Black);
        rw.draw(player);
        rw.display();
    }
}
