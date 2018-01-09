#ifndef REWARDSCREEN_H
#define REWARDSCREEN_H
#include <TGUI/Gui.hpp>

struct BALANCE
{
    sf::Text text;
    sf::Vector2f Size,Position;
    bool bShowBalance;
};

class RewardScreen
{
    private:
        bool bActiveReward[3];
        float Window_Width,Window_Height;

        sf::Texture RewardBG_Texture;
        sf::RectangleShape RewardBG_shape;
        sf::Vector2f RewardBG_Size;

        BALANCE Balance[3];
        sf::Font Balance_font;

    public:
        RewardScreen(sf::RenderWindow *window);
        void Update(bool *bActiveRound,bool *bEndRound);
        void Display(sf::RenderWindow *window);
        ~RewardScreen();
};
#endif
