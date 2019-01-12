void animationpunch()
{
    char punchc[50];
    Clock clock;

    sprintf (punchc,"hulk animation/punch-%d.png", punchanim);
    playtxt.loadFromFile(punchc);
    while(clock.getElapsedTime().asMilliseconds()<100.f);
    clock.restart();
}

void animationrepunch()
{
    char punchc[50];
    Clock clock;

    sprintf (punchc,"hulk animation/repunch-%d.png", punchanim);
    playtxt.loadFromFile(punchc);
    while(clock.getElapsedTime().asMilliseconds()<100.f);
    clock.restart();
}


void animationupperpunch()
{
    char upperpunch[50];

    Clock clock;
    sprintf (upperpunch,"hulk animation/upperpunch-%d.png", upperPunchAnim);
    playtxt.loadFromFile(upperpunch);
    while(clock.getElapsedTime().asMilliseconds()<100.f);
    clock.restart();
}

void animationreupperpunch()
{
    char upperpunch[50];

    Clock clock;
    sprintf (upperpunch,"hulk animation/reupperpunch-%d.png", upperPunchAnim);
    playtxt.loadFromFile(upperpunch);
    while(clock.getElapsedTime().asMilliseconds()<100.f);
    clock.restart();
}
