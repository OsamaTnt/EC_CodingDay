#include "Enviroment.h"

Enviroment::Enviroment(sf::RenderWindow *window,tgui::Gui &gui,bool *bActiveRound,bool *bDisplayInstrs)
{
    windowWidth = window->getSize().x; windowHeight = window->getSize().y;
    bInstrButtonClicked = false;

    //BackGround
    Bg_texture.loadFromFile("Data/G_BACKGROUND001.png");
    Bg_shape.setTexture(&Bg_texture);
    Bg_shape.setSize(sf::Vector2f(Bg_texture.getSize().x,Bg_texture.getSize().y));
    Bg_shape.setPosition(0,0);

    //CardsHolder
    CH_Batch_texture.loadFromFile("Data/CardsHolderBatch.png");
    for(int i=0;i<2;i++) { CH_Batch_Shape[i].setTexture(&CH_Batch_texture); CH_Batch_Shape[i].setSize(sf::Vector2f(CH_Batch_texture.getSize().x,CH_Batch_texture.getSize().y));}
    CH_Batch_Shape[0].setPosition(windowWidth/2-CH_Batch_Shape[0].getSize().x/2,windowHeight/2-CH_Batch_Shape[0].getSize().y);
    CH_Batch_Shape[1].setPosition(CH_Batch_Shape[0].getPosition().x,CH_Batch_Shape[0].getPosition().y*1.9);

    //Instruction Button
    InstrButtonTheme = tgui::Theme::create("Data/InstrsButtonConfig.txt");
    InstrButton = tgui::Button::create();
    InstrButton = InstrButtonTheme->load("Button");
    InstrButton->setPosition(windowWidth-InstrButton->getSize().x-InstrButton->getSize().x/1.5,InstrButton->getSize().y+InstrButton->getSize().y/2.5);
    gui.add(InstrButton,"Button");
    InstrButton->connect("pressed",&Enviroment::OnInstrButtonPressed,this,bActiveRound,bDisplayInstrs);
    InstrButton->hide();
}

void Enviroment::OnInstrButtonPressed(bool *bActiveRound,bool *bDisplayInstrs)
{
    //check if Round1 is active!
    if(bActiveRound[0]) {*bDisplayInstrs=true;bActiveRound[0]=false;}
}

sf::RectangleShape *Enviroment::getCH()
{return CH_Batch_Shape;}

void Enviroment::Display(sf::RenderWindow *window,bool *bDisplayInstrs,bool *bActiveRound)
{
    window->draw(Bg_shape);
    for(int i=0;i<2;i++) { window->draw(CH_Batch_Shape[i]); }
    if(!*bDisplayInstrs && bActiveRound[0]) {InstrButton->show();}
    else {InstrButton->hide();}
}

Enviroment::~Enviroment(){}
