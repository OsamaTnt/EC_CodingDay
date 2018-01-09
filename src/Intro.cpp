#include "Intro.h"

Intro::Intro(sf::RenderWindow *window,tgui::Gui &gui)
{
    window_Width = window->getSize().x; window_Hight = window->getSize().y;
    Neon.bDisplay = true; EC.bDisplay=false;
    TimeToStartDisplay = PauseTimer = DelayToStartInstr = 0;

    //Neon Logo
    Neon.texture.loadFromFile("Data/NeonLogo00.png");
    Neon.sprite.setTexture(Neon.texture);
    Neon.CurrentImageMap.x= Neon.CurrentImageMap.y = -1;
    Neon.Size.x = Neon.texture.getSize().x/4; Neon.Size.y = Neon.texture.getSize().y/3;
    Neon.srcImageRect = {(int)Neon.CurrentImageMap.x,(int)Neon.CurrentImageMap.y,(int)Neon.Size.x,(int)Neon.Size.y};
    Neon.sprite.setTextureRect(Neon.srcImageRect);
    Neon.sprite.setPosition( (window_Width/2)-Neon.srcImageRect.width/2 , (window_Hight/2)-Neon.srcImageRect.height/2);
    Neon.bPlayForward = true; Neon.bPlayBackward =false;

    //EC Logo
    EC.texture.loadFromFile("Data/EC_Logo01.png");
    EC.sprite.setTexture(EC.texture);
    EC.CurrentImageMap.x= EC.CurrentImageMap.y = -1;
    EC.Size.x = EC.texture.getSize().x/4; EC.Size.y = EC.texture.getSize().y/3;
    EC.srcImageRect = {(int)EC.CurrentImageMap.x,(int)EC.CurrentImageMap.y,(int)EC.Size.x,(int)EC.Size.y};
    EC.sprite.setTextureRect(EC.srcImageRect);
    EC.sprite.setPosition( (window_Width/2)-EC.srcImageRect.width/2 , (window_Hight/2)-EC.srcImageRect.height/2);
    EC.bPlayForward = true; EC.bPlayBackward =false;
}

void Intro::Update()
{
    TimeToStartDisplay++;
    if(TimeToStartDisplay >250)
    {
        //Thick!
        if(Neon.clock.getElapsedTime().asSeconds() > 0.225)
        {
            //Neon Logo
            if(Neon.bDisplay && !EC.bDisplay)
            {
                 if(Neon.bPlayForward && !Neon.bPlayBackward)
                 {
                    //when the image reach the limit -> Stop the image for n seconds then play in backward
                    if(Neon.CurrentImageMap.y == 2 && Neon.CurrentImageMap.x == 3)
                    {
                        PauseTimer++;
                        if(PauseTimer > 3.5) {Neon.bPlayForward=false;Neon.bPlayBackward=true;}
                    }
                    else if(Neon.CurrentImageMap.y*Neon.srcImageRect.height <= Neon.texture.getSize().y)
                    {
                        Neon.CurrentImageMap.x+=1;
                        if(Neon.CurrentImageMap.x*Neon.srcImageRect.width >= Neon.texture.getSize().x)
                        {Neon.CurrentImageMap.y+=1; Neon.CurrentImageMap.x = 0;}
                    }
                 }
                 else if (Neon.bPlayBackward && !Neon.bPlayForward)
                 {
                    if(Neon.CurrentImageMap.y<0)
                    {
                        DelayToStartInstr++;
                        if(DelayToStartInstr > 30) {EC.bDisplay=true;Neon.bPlayBackward=false;Neon.bDisplay=false;Neon.CurrentImageMap.x=Neon.CurrentImageMap.y=PauseTimer=DelayToStartInstr=-1;}
                    }
                    else if(Neon.CurrentImageMap.y*Neon.srcImageRect.height >= 0)
                    {
                        Neon.CurrentImageMap.x-=1;
                        if(Neon.CurrentImageMap.x < 0) {Neon.CurrentImageMap.y-=1; Neon.CurrentImageMap.x=3;}
                    }
                }
            }

            //EC_LOGO
            if(EC.bDisplay && !Neon.bDisplay)
            {
                 if(EC.bPlayForward && !EC.bPlayBackward)
                 {
                    if(EC.CurrentImageMap.y == 2 && EC.CurrentImageMap.x == 3)
                    {
                        PauseTimer++;
                        if(PauseTimer > 3.5) {EC.bPlayForward=false;EC.bPlayBackward=true;}
                    }
                    else if(EC.CurrentImageMap.y*EC.srcImageRect.height <= EC.texture.getSize().y)
                    {
                        EC.CurrentImageMap.x+=1;
                        if(EC.CurrentImageMap.x*EC.srcImageRect.width >= EC.texture.getSize().x)
                        {EC.CurrentImageMap.y+=1; EC.CurrentImageMap.x = 0;}
                    }
                 }
                 else if (EC.bPlayBackward && !EC.bPlayForward)
                 {
                    if(EC.CurrentImageMap.y<0)
                    {
                        DelayToStartInstr++;
                        if(DelayToStartInstr > 30) {EC.bPlayBackward=false;EC.bDisplay=false;EC.CurrentImageMap.x=EC.CurrentImageMap.y=-1;}
                    }
                    else if(EC.CurrentImageMap.y*EC.srcImageRect.height >= 0)
                    {
                        EC.CurrentImageMap.x-=1;
                        if(EC.CurrentImageMap.x < 0) {EC.CurrentImageMap.y-=1; EC.CurrentImageMap.x=3;}
                    }
                }
            }
              //reset the clock
              Neon.clock.restart();
        }
    }
        //Update Neon_Logo sprite
        Neon.srcImageRect = {(int)Neon.CurrentImageMap.x*(int)Neon.Size.x,(int)Neon.CurrentImageMap.y*(int)Neon.Size.y,(int)Neon.Size.x,(int)Neon.Size.y};
        Neon.sprite.setTextureRect(Neon.srcImageRect);

        EC.srcImageRect = {(int)EC.CurrentImageMap.x*(int)EC.Size.x,(int)EC.CurrentImageMap.y*(int)EC.Size.y,(int)EC.Size.x,(int)EC.Size.y};
        EC.sprite.setTextureRect(EC.srcImageRect);
}

bool Intro::ShownState()
{
    //DelayTime should be -100 to display Instr!
    if(!Neon.bDisplay && !EC.bDisplay) {return false;}
    else {return true;}
}

void Intro::Display(sf::RenderWindow *window)
{
    if(Neon.bDisplay && !EC.bDisplay) {window->draw(Neon.sprite);}
    else {window->draw(EC.sprite);}
}

Intro::~Intro() {}
