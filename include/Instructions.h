#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H
#include <iostream>
#include <string>
#include <fstream>
#include <TGUI/TGUI.hpp>

class Instructions
{
    private:
        float window_Width,window_Height;
        int CurrentPageNum;
        std::fstream instr_file;
        std::string Read_String;     //will be used when reading from instr_file!

        tgui::Theme::Ptr Next_Button_Config;
        tgui::Button::Ptr Next_Button;

        sf::Clock TextClock;

        sf::Texture InstWindow_texture;
        sf::RectangleShape InstWindow_shape;

        sf::Font Instrs_font;
        sf::Text Instrs_Text;
        std::string Instrs_String;
        bool DisplayInstrsText;
        float TextDelayTimer,hideInstrWindow,showInstrWindow,InstrWindowAnimSpeed;

    public:
        Instructions(sf::RenderWindow *window,tgui::Gui &gui,bool *bDisplayInstrs,bool *bActiveRound);
        void setInstrsText();
        void ManageEvents(sf::Event *event,sf::RenderWindow *window,tgui::Gui &gui);
        void Update(bool *bInstrButtonClicked);
        void OnNextButtonPressed(bool *bDisplayInstrs,bool *bActiveRound);
        bool isShown();
        void Display(sf::RenderWindow *window);
        ~Instructions();
};
#endif // INSTRUCTIONS_H
