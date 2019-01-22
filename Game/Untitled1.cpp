#include<SFML/Graphics.hpp>
#include<bits/stdc++.h>
#include<SFML/Audio.hpp>

using namespace sf;
using namespace std;

int j=1,flagwalk=1,i=1,flagidle=1,idlef=1, upperPunchAnim = 6, punchanim = 5,jumpanim=7;

char idle [50], walk[50] ;
RenderWindow rw(VideoMode(1000, 751),"Game",Style::Close|Style::Resize);
RectangleShape player (Vector2f(80.0f,100.0f));
Texture playtxt,BackgroundTexture,guli,example;

Music backgroundmusic;

Sprite background;
Vector2u TextureSize;
Vector2u WindowSize;
View view;

#include"player.hpp"
#include"punching.hpp"

float velocityY = 0.0, bx = 500;
bool isjumping = false;

///Jumping
void animationjump()
{
    char jump[50];
    Clock clock;

    sprintf (jump,"hulk animation/jump-%d.png", jumpanim);
    playtxt.loadFromFile(jump);
    while(clock.getElapsedTime().asMilliseconds()<50.f);
    clock.restart();
}

void animationrejump()
{
    char jump[50];
    Clock clock;

    sprintf (jump,"hulk animation/rejump-%d.png", jumpanim);
    playtxt.loadFromFile(jump);
    while(clock.getElapsedTime().asMilliseconds()<100.f);
    clock.restart();
}
///

///Menu screen
#include"menu.hpp"
///Menu End

///game over screen
bool isGameover = false;

void gameover(RenderWindow &window)
{
    window.clear();
    View overView;
    overView.setCenter(window.getSize().x/2,window.getSize().y/2);
    Texture gameoverBackground;
    gameoverBackground.loadFromFile("gameoverbg.png");
    Sprite overSprite(gameoverBackground);
    Vector2u TSize,WSize;

    TSize=gameoverBackground.getSize();
    WSize = window.getSize();

    float ScaleX = (float) window.getSize().x/ TSize.x;
    float ScaleY = (float) window.getSize().y/ TSize.y;

    overSprite.setTexture(gameoverBackground);
    overSprite.setScale(ScaleX, ScaleY);

    if(Keyboard::isKeyPressed(Keyboard::Escape))
        {
            isGameover = false;
            IsMenuStarted = true;
            return;
//            menuscreen(window);
        }
    overView.setSize(1000, 751);
    window.setView(overView);
    window.draw(overSprite);
    window.display();
}



class bullet
{
public:
    Sprite shape;
    bullet(Texture *texture,Vector2f pos)
    {
//        pos.y=pos.y+20;
        shape.setTexture(*texture);
        shape.setScale(-0.8,0.8);
        shape.setPosition(pos.x,pos.y);
    }
};
///Eenemy
class enemy
{
public:
    Texture CharacterTexture,guli;
    Sprite CharacterSprite;
    float scaleSize = 1.5;
    char loc[14];
    bool direction=true;
    int lyf=50;
    Clock time;
    vector<bullet> magazine;

    enemy()
    {
        CharacterTexture.loadFromFile("Enemy sprites/Enemy-1.png");
        CharacterSprite.setTexture(CharacterTexture);
        CharacterSprite.scale(-1*scaleSize, scaleSize);
//        CharacterSprite.setPosition(100,100);
        time.restart();
        CharacterSprite.setOrigin(CharacterSprite.getLocalBounds().width/2, CharacterSprite.getLocalBounds().height/2);
//        CharacterSprite.scale(-1,1);
    }

    void Walk()
    {
        static int x = 10;
        sprintf(loc, "Enemy sprites/Enemy-%d.png", x/10);
        CharacterTexture.loadFromFile(loc);
        CharacterSprite.setTexture(CharacterTexture);
        CharacterSprite.move(-1, 0);
        if (x < 100)
        {
            x++;
        }
        else
        {
            x = 10;
        }
    }
    void sp(float x, float y)
    {
        CharacterSprite.setPosition(x, y);
    }
    void Attack()
    {
        static int x=1;
        sprintf(loc, "Attack (%d).png", x);
        this->CharacterTexture.loadFromFile(loc);
        this->CharacterSprite.setTexture(CharacterTexture);
        if (x < 8)
            x++;
        else
            x = 1;
    }
    Vector2f get1()
    {
        return CharacterSprite.getPosition();
    }
    void dead()
    {
        static int x = 1;
        sprintf(loc, "Dead (%d).png", x);
        this->CharacterTexture.loadFromFile(loc);
        this->CharacterSprite.setTexture(CharacterTexture);
        if (x < 12)
            x++;
        else
            CharacterSprite.setPosition(-500,200);
    }
    int dying()
    {
        return lyf=lyf-10;
    }
    void Drawenemy(RenderWindow &app)
    {
        app.draw(CharacterSprite);
    }

    float getX()
    {
        return CharacterSprite.getPosition().x;
    }
//    void enemyBullet()
//    {
//        guli.loadFromFile("fire_blue.png");
//
//
//        time=btime.getElapsedTime().asSeconds();
//        exmp.setPosition(150.f,150.f);
//
//        if(time.getElapsedTime().asSeconds() > 1.0)
//        {
//            magazine.push_back(bullet(&guli,Vector2f(CharacterSprite.getPosition() )));
//            time.restart();
//            btime.restart();
//        }
//
//        for(int kl=0; kl < magazine.size(); kl++)
//        {
//            magazine[kl].shape.move(2.f,0.f);
//            if(magazine[kl].shape.getPosition().x > rw.getSize().x)
//            {
//                magazine.erase(magazine.begin()+kl);
//            }
//        }
//    }
//    void drawEnemyBullet(RenderWindow &rw)
//    {
//        for(int kl=0;kl < magazine.size() ;kl++)
//        {
//            rw.draw(magazine[kl].shape);
//        }
//    }

};

///end

///bulltet




int main()
{
    float lowergroundY = rw.getSize().y-290 ;
    rw.setFramerateLimit(100);
    playtxt.loadFromFile("hulk animation/idle-1.png");
    player.setPosition(0,lowergroundY);
    player.setScale(2,2);
    Clock clock,btime;
    ///Music
    backgroundmusic.openFromFile("Music samples/backgroundmusic.ogg");
    backgroundmusic.setVolume(25.f);
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

    float ScaleY = (float) WindowSize.y / TextureSize.y;

    background.setTexture(BackgroundTexture);
    background.setScale(1, ScaleY);

    ///hulk life

    int hulkLife = 100;

    ///enemy variables
    int enemyLowerGround = 583;
    enemy shoitan[5];

    shoitan[0].sp(5000,enemyLowerGround);
    shoitan[1].sp(1000,enemyLowerGround);
    shoitan[2].sp(3000,enemyLowerGround);
    shoitan[3].sp(2000,enemyLowerGround);
    shoitan[4].sp(6080,enemyLowerGround);
    ///end

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
        ///Gameover
        while(isGameover)
            gameover(rw);

        ///menu
        while(IsMenuStarted)
            menuscreen(rw);
        if(Keyboard::isKeyPressed(Keyboard::Escape))
            IsMenuStarted = true;
        ///end

        bool isPunching = false;


        if(idlef==1)
            animationidle(clock);
        else
            animationreidle(clock);

        if(Keyboard::isKeyPressed(Keyboard::D))
        {
            idlef=1;
            animationwalk(clock);
            player.move(1.3f, 0.0f);
        }

        if(Keyboard::isKeyPressed(Keyboard::A))
        {
            idlef=0;
            animationrewalk(clock);
            player.move(-1.3f, 0.0f);
        }

        if(Keyboard::isKeyPressed(Keyboard::L))
        {
            punchanim = 1;
            isPunching = true;

        }

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
        if(Keyboard::isKeyPressed(Keyboard::W) && player.getPosition().y >= lowergroundY)
        {
            isjumping = true;
        }
        if(isjumping)
        {
            velocityY=-20;
            jumpanim=1;
            if(jumpanim < 7)
            {
                if(idlef==1)
                    animationjump();
                else
                    animationrejump();
                jumpanim++;
            }

            velocityY=-22;
            isjumping=false;
        }
        player.move(0, velocityY);

        if(player.getPosition().y >= lowergroundY)
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

        if(time > 1)
        {
            //            magazine.push_back(bullet(&guli,shoitan[0].get1()));

            if(shoitan[0].getX() - player.getPosition().x <= 500)
                magazine.push_back(bullet(&guli,shoitan[0].get1()));


            if(shoitan[1].getX() - player.getPosition().x <= 500)
                magazine.push_back(bullet(&guli,shoitan[1].get1()));

            if(shoitan[2].getX() - player.getPosition().x <= 500)
                magazine.push_back(bullet(&guli,shoitan[2].get1()));

            if(shoitan[3].getX() - player.getPosition().x <= 500)
                magazine.push_back(bullet(&guli,shoitan[3].get1()));

            if(shoitan[4].getX() - player.getPosition().x <= 500)
                magazine.push_back(bullet(&guli,shoitan[4].get1()));

////            magazine.push_back(bullet(&guli,Vector2f(exmp.getPosition())));
            time=0.0;
            btime.restart();
        }

        for(int kl=0; kl < magazine.size(); kl++)
        {
            magazine[kl].shape.move(-2.f,0.f);
//            if(magazine[kl].shape.getPosition().x > rw.getSize().x)
//            {
//                magazine.erase(magazine.begin()+kl);
//            }
        }
        ///end


        ///enemy

//        shoitan[0].Walk();

//        test.Walk();

//        for(int i=0; i<5; i++)
//        {
//            shoitan[i].enemyBullet();
//        }
        ///end

//        ///for mouse co ordinates
//        if(Mouse::isButtonPressed(Mouse::Left) && clock.getElapsedTime().asMilliseconds()>100)
//        {
//            cout<<Mouse::getPosition().x<<"\t\t"<<Mouse::getPosition().y<<endl;
//        }

        ///for collision
        bool hit = false;

        for(int i=0; i<magazine.size(); i++)
        {
//            Clock hitTime;

//            if(hitTime.getElapsedTime().asMilliseconds()>)

            if(player.getGlobalBounds().intersects(magazine[i].shape.getGlobalBounds()) )
            {
//                while(hitTime.getElapsedTime().asMilliseconds()<100);
                cout<<"hit"<<endl;
//                hulkLife--;
//                hitTime.restart();
//                hit = true;
            }
        }

        if(player.getGlobalBounds().intersects(shoitan[0].CharacterSprite.getGlobalBounds()) )
        {
            cout<<"punching success"<<endl;

        }

        if(hulkLife == 0)
        {
            isGameover=true;

        }


        if(clock.getElapsedTime().asMilliseconds()>250.f)
            clock.restart();


        playtxt.setSmooth(true);
        player.setTexture(&playtxt);
        playtxt.setSmooth(true);
        rw.clear(Color::Black);
        rw.draw(background);
        rw.draw(player);
        rw.draw(exmp);

        ///for screen viewing
        if(player.getPosition().x > 500 && player.getPosition().x < 6560)
            bx = player.getPosition().x;
        view.setCenter(bx, 375.5);
        view.setSize(1000, 751);
        rw.setView(view);


        for(int kl=0; kl < magazine.size() ; kl++)
        {
            rw.draw(magazine[kl].shape);
        }

        for(int i=0; i<=4; i++)
        {
            shoitan[i].Drawenemy(rw);
        }
        rw.display();
    }
    return 0;
}

