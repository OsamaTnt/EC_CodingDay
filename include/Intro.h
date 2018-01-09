#ifndef INTRO_H
#define INTRO_H
#include <iostream>
#include <string>
#include <TGUI/TGUI.hpp>

struct _Image
{
    sf::Texture texture;
    sf::RectangleShape shape;
    sf::Vector2f Size,Position;
};

struct Logo
{
    sf::Texture texture;
    sf::IntRect srcImageRect;
    sf::Sprite sprite;
    sf::Vector2f CurrentImageMap,Size;
    sf::Clock clock;
    bool bDisplay,bPlayForward,bPlayBackward;
};

class Intro
{
    private:
         float window_Width,window_Hight;
        _Image BG;
        Logo Neon,EC;

        float TimeToStartDisplay,PauseTimer,DelayToStartInstr;

    public:
        Intro(sf::RenderWindow *window,tgui::Gui &gui);
        void Update();
        bool ShownState();
        void Display(sf::RenderWindow *window);
        ~Intro();
};
#endif // INTRO_H
