
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
        if(flagidle==1)
            i--;
        else
            i++;
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
        if(flagidle==1)
            i--;
        else
            i++;
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
        if(flagwalk==1)
            j--;
        else
            j++;
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
        if(flagwalk==1)
            j--;
        else
            j++;
    }
}




