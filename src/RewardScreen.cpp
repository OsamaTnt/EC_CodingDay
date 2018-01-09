#include "RewardScreen.h"

RewardScreen::RewardScreen(sf::RenderWindow *window)
{
    Window_Width=window->getSize().x;Window_Height=window->getSize().y;

    for(int i=0;i<3;i++){bActiveReward[i]=false;}

    RewardBG_Texture.loadFromFile("Data/G_REWARD.png");
    RewardBG_shape.setTexture(&RewardBG_Texture);
    RewardBG_Size = {(float)RewardBG_Texture.getSize().x,(float)RewardBG_Texture.getSize().y};
    RewardBG_shape.setSize(RewardBG_Size);
    RewardBG_shape.setPosition(0,Window_Height*0.2);

    Balance_font.loadFromFile("Data/AGENCYR.TTF");
    for(int i=0;i<3;i++)
    {
        Balance[i].text.setFont(Balance_font);
        Balance[i].text.setFillColor(sf::Color(255,255,180));
        Balance[i].text.setCharacterSize(30);
        Balance[i].text.setPosition(RewardBG_shape.getPosition().x+(RewardBG_Size.x*0.4),RewardBG_shape.getPosition().y+(RewardBG_Size.y*0.425));
    }
    Balance[0].text.setString("Your current balance is : 5.LD\n\n\t\tThanks for coming!!\n\tHope you enjoyed the day!! : )");
    Balance[1].text.setString("Your current balance is : 10.LD\n\n\t\tThanks for coming!!\n\tHope you enjoyed the day!! : )");
    Balance[2].text.setString("Your current balance is : 15.LD\n\n\t\tThanks for coming!!\n\tHope you enjoyed the day!! : )");
}

void RewardScreen::Update(bool *bActiveRound,bool *bEndRound)
{
    for(int i=0;i<3;i++) {if(bEndRound[i] && bActiveRound[i]) {bActiveReward[i]=true;}}
}

void RewardScreen::Display(sf::RenderWindow *window)
{
    for(int i=0;i<3;i++) {if(bActiveReward[i]) {window->draw(RewardBG_shape); window->draw(Balance[i].text);}}
}

RewardScreen::~RewardScreen() {}
