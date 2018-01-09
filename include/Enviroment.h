#ifndef ENVIROMENT_H
#define ENVIROMENT_H
#include <TGUI/TGUI.hpp>

class Enviroment
{
    private:
        sf::Texture Bg_texture;
        sf::RectangleShape Bg_shape;
        float windowWidth,windowHeight;

        //Card's Holder
        sf::Texture CH_Batch_texture;
        sf::RectangleShape CH_Batch_Shape[2];    //each batch will contain 5 cards!

        tgui::Theme::Ptr InstrButtonTheme;
        tgui::Button::Ptr InstrButton;

    public:
        bool bInstrButtonClicked;
        Enviroment(sf::RenderWindow *window,tgui::Gui &gui,bool *bActiveRound,bool *bDisplayInstrs);
        void OnInstrButtonPressed(bool *bActiveRound1,bool *bDisplayInstrs);
        sf::RectangleShape *getCH();
        void Display(sf::RenderWindow *window,bool *bDisplayInstrs,bool *bActiveRound);
        ~Enviroment();
};
#endif // ENVIROMENT_H
