#include "Instructions.h"

Instructions::Instructions(sf::RenderWindow *window,tgui::Gui &gui,bool *bDisplayInstrs,bool *bActiveRound)
{
    window_Width = window->getSize().x; window_Height = window->getSize().y;

    //shownPage states
    CurrentPageNum=0;
    InstWindow_texture.loadFromFile("Data/Inst04.png");
    InstWindow_shape.setTexture(&InstWindow_texture);
    InstWindow_shape.setSize(sf::Vector2f(InstWindow_texture.getSize().x,InstWindow_texture.getSize().y));

    //Position Y is Out of the Screen (test)
    InstWindow_shape.setPosition(window_Width/2 - InstWindow_texture.getSize().x/2,-InstWindow_shape.getSize().y*1.5);

    //Instruction text , string & font
    Instrs_font.loadFromFile("Data/AGENCYB.TTF");
    Instrs_Text.setFont(Instrs_font);
    Instrs_Text.setFillColor(sf::Color(255,255,210));
    Instrs_Text.setCharacterSize(25);
    setInstrsText();
    DisplayInstrsText = false;
    TextDelayTimer=0;

    //Next Button!
    Next_Button_Config = tgui::Theme::create("Data/InstrConfig.txt");
    Next_Button = tgui::Button::create();
    Next_Button = Next_Button_Config->load("Button");
    gui.add(Next_Button,"Button");
    Next_Button->connect("pressed",&Instructions::OnNextButtonPressed,this,bDisplayInstrs,bActiveRound);
    Next_Button->hide();

    InstrWindowAnimSpeed = 5;
}

void Instructions::setInstrsText()
{
Instrs_String = "Welcome to EC CodingDay2017!!\n\nRound1 : You will have 10 Cards,each one of them have a Question for you!\nfor each correct answer you will gain 1 point!!, be patient and get ready\nfor the challenge,and ah do not forget the red wax timer!!\n Goodluck! & Enjoy the journy!!\n";
    Instrs_Text.setString(Instrs_String);
}

void Instructions::ManageEvents(sf::Event *event,sf::RenderWindow *window,tgui::Gui &gui)
{}

void Instructions::OnNextButtonPressed(bool *bDisplayInstrs,bool *bActiveRound)
{
     //hide InstrWindow & set bDisplayInstr to false
     InstWindow_shape.setPosition(window_Width/2 - InstWindow_texture.getSize().x/2,-InstWindow_shape.getSize().y*1.5);
     Next_Button->hide();
     DisplayInstrsText = *bDisplayInstrs = false;
     bActiveRound[0] = true;
}

//Called everyFrame
void Instructions::Update(bool *bInstrButtonClicked)
{
    //First time that Instruction will pop up automaticly!
    if(!*bInstrButtonClicked)
    {
        if(InstWindow_shape.getPosition().y < window_Height/2 - InstWindow_texture.getSize().y/1.5 )
        { InstWindow_shape.move(0,InstrWindowAnimSpeed);}
        else
        {
            if(TextDelayTimer<150){TextDelayTimer++;}    //uneccesary statement , just to stop the increment
            if(TextDelayTimer>140)
            {
                Instrs_Text.setPosition(InstWindow_shape.getPosition().x+InstWindow_shape.getSize().x/9 ,InstWindow_shape.getPosition().y+InstWindow_shape.getSize().y/2);
                Next_Button->setPosition(InstWindow_shape.getGlobalBounds().width+Next_Button->getSize().x/1.1,InstWindow_shape.getGlobalBounds().height-Next_Button->getSize().y*1.55);
                DisplayInstrsText = true;
            }
        }
    }
}

void Instructions::Display(sf::RenderWindow *window)
{
    window->draw(InstWindow_shape);
    if(DisplayInstrsText) {window->draw(Instrs_Text);Next_Button->show();}
}

Instructions::~Instructions() {}
