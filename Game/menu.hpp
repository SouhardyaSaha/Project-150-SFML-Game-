#define Item_num_menu 3

void MoveUp();
void MoveDown();

Clock menuClock;
bool isMenuDisplay = false;


static int selectedItemIndex = 0;
Text menu[Item_num_menu];

int GetPressedItem()
{
    return selectedItemIndex;
}

bool IsMenuStarted = true;

void menuscreen(RenderWindow &window)
{
    Text menuUpperWriting;
    Font MenuStartFont,menuUp;
    float width = window.getSize().x, height = window.getSize().y;

    Texture MenuTexture;
    Vector2u menutexturesize, menuwindowsize;
    MenuTexture.loadFromFile("menu.png");
    Sprite menuDisplay(MenuTexture);

    menutexturesize = MenuTexture.getSize();
    menuwindowsize = window.getSize();

    float ScaleX = (float) menuwindowsize.x / menutexturesize.x;
    float ScaleY = (float) menuwindowsize.y / menutexturesize.y;

    menuDisplay.setTexture(MenuTexture);
    menuDisplay.setScale(ScaleX, ScaleY);

    if(!MenuStartFont.loadFromFile("Fonts/1.ttf"))
    {
        cout<<"error font"<<endl;
    }
    if(!menuUp.loadFromFile("Fonts/3.ttf"))
    {
        cout<<"error font"<<endl;
    }


        menuUpperWriting.setFont(menuUp);
        menuUpperWriting.setColor(Color::White);
        menuUpperWriting.setCharacterSize(60);
        menuUpperWriting.setString("Menu");
        menuUpperWriting.setPosition(210, 15);

//    float ScaleX = (float) menuwindowsize.x / menutexturesize.x;
//    float ScaleY = (float) menutexturesize.y / menutexturesize.y;

        menu[0].setFont(MenuStartFont);
        menu[0].setColor(Color::White);
        menu[0].setCharacterSize(60);
        menu[0].setString("Start Game");
        menu[0].setPosition(45, 150);

        menu[1].setFont(MenuStartFont);
        menu[1].setColor(Color::White);
        menu[0].setCharacterSize(40);
        menu[1].setString("Settings");
        menu[1].setPosition(45,210);

        menu[2].setFont(MenuStartFont);
        menu[2].setColor(Color::White);
        menu[0].setCharacterSize(40);
        menu[2].setString("Exit");
        menu[2].setPosition(45, 260);

    if(Keyboard::isKeyPressed(Keyboard::Up) && menuClock.getElapsedTime().asMilliseconds()>250)
        MoveUp();
    if(Keyboard::isKeyPressed(Keyboard::Down) && menuClock.getElapsedTime().asMilliseconds()>250)
        MoveDown();
    if(Keyboard::isKeyPressed(Keyboard::Return))
    {
        switch (GetPressedItem())
        {
        case 0:
            isMenuDisplay = false;
            cout << "Play button has been pressed" << std::endl;
            IsMenuStarted = false;
            break;
        case 1:
            cout << "Option button has been pressed" << std::endl;
            break;
        case 2:
            cout << "Exit button has been pressed" << std::endl;
//            backgroundmusic.play(false);
            window.close();
            break;
        }
    }

    menu[0].setColor(Color::White);
    menu[1].setColor(Color::White);
    menu[2].setColor(Color::White);

    menu[selectedItemIndex].setColor(Color::Green);


    window.draw(menuDisplay);
    for(int i=0; i< Item_num_menu; i++)
    {
        window.draw(menu[i]);
    }
    window.draw(menuUpperWriting);
    window.display();
}

void MoveUp()
{
    menuClock.restart();
    if (selectedItemIndex - 1 >= 0)
    {
        selectedItemIndex--;
    }
    else
    {
        selectedItemIndex = 2;
    }
}

void MoveDown()
{
    menuClock.restart();
    if (selectedItemIndex + 1 < Item_num_menu)
    {
        selectedItemIndex++;
    }
    else
    {
        selectedItemIndex = 0;
    }
}

