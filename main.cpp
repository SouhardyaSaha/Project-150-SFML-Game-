#include<SFML/Graphics.hpp>
#include<bits/stdc++.h>

using namespace sf;
using namespace std;

int main()
{
    int x=100,y=100;
    RectangleShape player (Vector2f(100.0f,100.0f));

    RenderWindow rw(VideoMode(640,480),"VS-first",Style::Close|Style::Resize);
    player.setPosition(rw.getSize().x/2,rw.getSize().y/2);

    Texture playtxt;


    char idle [50];
    int i=1,flag=1;
    Clock clock;

    while (rw.isOpen())
    {
//        deltaTime = clock.restart().asSeconds();

        rw.setFramerateLimit(30);

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
        if(clock.getElapsedTime().asMilliseconds()>250.f){
        if(i>4)
        {
            flag=1;
            i=3;
        }
        if(i<1)
        {
            flag =0;
            i=2;
        }
        sprintf (idle, "hulk animation/idle-%d.png", i);
        playtxt.loadFromFile(idle);
        if(flag==1) i--;
        else i++;
        player.setTexture(&playtxt);
        clock.restart();
        }

        rw.clear(Color::Black);
        rw.draw(player);
        rw.display();
    }
}
