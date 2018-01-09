#ifndef ROUNDONE_H_INCLUDED
#define ROUNDONE_H_INCLUDED
#include <iostream>
#include <TGUI/Gui.hpp>

struct CARD
{
    sf::Sprite sprite;
    sf::Vector2f Size,StrterPos,Position;
    sf::Clock clock;
    bool bActive;
    int randBatch[3],randNum;
    char letter;
    sf::Text letter_text;
};

struct QWINDOW
{
    sf::RectangleShape shape;
    sf::Texture texture;
    sf::Vector2f Size,Position,strterSize;
    bool bActive;
    sf::String Question_string;
    sf::Text Question_text;
    sf::Font font;
    int QIndex;
    sf::Clock clock;
    sf::Time DisplayDelayTimer;
};

struct ANSWR
{
    sf::Sprite sprite;
    sf::Vector2f Size,Position;
    sf::Clock clock;
    bool bActive;
    sf::Text text;
};

class RoundOne
{
    private:
        float window_Width,window_Height;
        sf::Texture BCard_texture[2];   //0=Flipped,1=onHovered,2=unFlipped
        sf::Texture GCard_texture,RCard_texture;

        sf::Vector2f BCard_Size;
        CARD *Card[10];
        float timer;
        bool bLeftMouseClicked,bStart;

        //QWindow && Answr
        QWINDOW QWindow;
        ANSWR Answr[4]; //0=A,1=B,2=C,3=D
        sf::Texture AnswrField_texture[2];   //0=Normal,1=onHover
        sf::Texture GAnswr_texture,RAnswr_texture;
        sf::Vector2f AnswrField_Size;
        sf::Font Answr_font;
        bool bDisplayQWindow,bUserAnswered;
        sf::Clock clock;
        sf::Time AnswrDelayTime;
        int randNum,userAnswrIndex;
        bool bActiveAnswr,bPopUpQWindow;

        //points
        sf::Texture BPoint_texture,unActivePoint_texture;
        sf::RectangleShape Point_shape[10];
        sf::Vector2f Point_Size;
        int CurrentPointIndex,TotalPoints;

        //Graphic Timer
        sf::Texture R_TimerBar_texture[4];
        sf::RectangleShape TimerBar_shape[10];
        sf::Vector2f TimerBar_Size;
        int CurrentTimerBarIndex;

        sf::Clock RoundOne_Clock;
        int randNum1,QCounter;
        bool bEndRoundOne;

        sf::Font letter_font;

    public:
        RoundOne(sf::RenderWindow *window,sf::RectangleShape *CH_Batch_Shape);
        void ManageEvents(sf::Event *event,sf::Mouse *mouse,sf::RenderWindow *window,tgui::Gui &gui);
        void ManageLogics(sf::Event *event,sf::Mouse *mouse,sf::RenderWindow *window);
        void setQuestion();
        bool checkAnswr();
        void UpdateRoundTimer();
        bool bCheckState();
        void Display(sf::RenderWindow *window);
        ~RoundOne();
};
#endif
