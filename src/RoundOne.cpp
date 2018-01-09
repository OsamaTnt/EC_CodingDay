#include "RoundOne.h"

RoundOne::RoundOne(sf::RenderWindow *window,sf::RectangleShape *CH_Batch_Shape)
{
    window_Width = window->getSize().x; window_Height = window->getSize().y;

    ////Card Texture's
    //Normal(0),onHovered(1)
    BCard_texture[0].loadFromFile("Data/BCard000.png");BCard_texture[1].loadFromFile("Data/BCard111.png");
    GCard_texture.loadFromFile("Data/Green222.png");RCard_texture.loadFromFile("Data/Red222.png");

    //Cards Properties
    BCard_Size = {(float)BCard_texture[0].getSize().x,(float)BCard_texture[0].getSize().y};

    for(int i=0;i<10;i++)
    {
        Card[i] = new CARD;
        Card[i]->bActive=true;
        Card[i]->sprite.setTexture(BCard_texture[0]);
        Card[i]->StrterPos = {(float)(window_Width-BCard_Size.x*1.2),(float)(CH_Batch_Shape[0].getPosition().y+130)};
        Card[i]->sprite.setPosition(Card[i]->StrterPos);
    }

    Card[0]->Position = {(float)CH_Batch_Shape[0].getPosition().x+25,(float)CH_Batch_Shape[0].getPosition().y+10};
    Card[1]->Position = {(float)(Card[0]->Position.x+175),Card[0]->Position.y};Card[2]->Position = {Card[1]->Position.x+152,Card[0]->Position.y};
    Card[3]->Position = {(float)(Card[2]->Position.x+151.75),Card[0]->Position.y};Card[4]->Position = {(float)(Card[3]->Position.x+171),Card[0]->Position.y};
    Card[5]->Position = {Card[0]->Position.x,Card[0]->Position.y+265};Card[6]->Position = {Card[1]->Position.x,Card[5]->Position.y};
    Card[7]->Position = {Card[2]->Position.x,Card[5]->Position.y};Card[8]->Position = {Card[3]->Position.x,Card[5]->Position.y};
    Card[9]->Position = {Card[4]->Position.x,Card[5]->Position.y};

    timer=0;
    bLeftMouseClicked=bStart=false;

    ////QWindow
    QWindow.texture.loadFromFile("Data/QWindow01.png");
    QWindow.shape.setTexture(&QWindow.texture);
    QWindow.Size = {(float)(QWindow.texture.getSize().x/0.85),(float)(QWindow.texture.getSize().y/0.85)};
    QWindow.shape.setSize(QWindow.Size);
    QWindow.Position = {window_Width/2-QWindow.shape.getSize().x/2,(float)(window_Height/2-QWindow.shape.getSize().y/2.25)};
    QWindow.shape.setPosition(QWindow.Position);

    QWindow.font.loadFromFile("Data/AGENCYR.TTF");
    QWindow.Question_text.setFont(QWindow.font);
    QWindow.Question_text.setCharacterSize(30);
    QWindow.Question_text.setFillColor(sf::Color::White);
    QWindow.Question_text.setPosition(QWindow.shape.getPosition().x/0.65,QWindow.shape.getPosition().y/0.75);

    /////ANSWR
    //Texture's , 0=Normal,1=onHover
    AnswrField_texture[0].loadFromFile("Data/AnswrField.png");
    AnswrField_texture[1].loadFromFile("Data/AnswrFieldHover.png");
    GAnswr_texture.loadFromFile("Data/GAnswr00.png");
    RAnswr_texture.loadFromFile("Data/RAnswr00.png");

    AnswrField_Size = {(float)AnswrField_texture[0].getSize().x,(float)AnswrField_texture[0].getSize().y};

    //A
    Answr[0].sprite.setPosition(QWindow.shape.getPosition().x+(QWindow.shape.getPosition().x*0.6),QWindow.shape.getPosition().y*2);
    Answr[0].text.setPosition(Answr[0].sprite.getPosition().x+Answr[0].sprite.getPosition().x*0.15,Answr[0].sprite.getPosition().y+Answr[0].sprite.getPosition().y*0.065);
    //B
    Answr[1].sprite.setPosition((QWindow.shape.getPosition().x+QWindow.shape.getSize().x-AnswrField_Size.x)-(QWindow.shape.getPosition().x*0.6),Answr[0].sprite.getPosition().y);
    Answr[1].text.setPosition(Answr[1].sprite.getPosition().x+Answr[0].sprite.getPosition().x*0.15,Answr[1].sprite.getPosition().y+Answr[1].sprite.getPosition().y*0.065);
    //C
    Answr[2].sprite.setPosition(Answr[0].sprite.getPosition().x,(Answr[0].sprite.getPosition().y+AnswrField_Size.y)+AnswrField_Size.y*0.075);
    Answr[2].text.setPosition(Answr[2].sprite.getPosition().x+Answr[2].sprite.getPosition().x*0.15,Answr[2].sprite.getPosition().y+Answr[2].sprite.getPosition().y*0.06);
    //D
    Answr[3].sprite.setPosition(Answr[1].sprite.getPosition().x,(Answr[1].sprite.getPosition().y+AnswrField_Size.y)+AnswrField_Size.y*0.075);
    Answr[3].text.setPosition(Answr[1].text.getPosition().x,Answr[3].sprite.getPosition().y+Answr[3].sprite.getPosition().y*0.06);

    //Answr field
    Answr_font.loadFromFile("Data/AGENCYR.TTF");
    for(int i=0;i<4;i++)
    {
        Answr[i].sprite.setTexture(AnswrField_texture[0]);
        Answr[i].text.setFont(Answr_font);
        Answr[i].text.setCharacterSize(24);
        Answr[i].text.setFillColor(sf::Color(255,255,135));
    }

    bActiveAnswr=true;
    bDisplayQWindow=bUserAnswered=bPopUpQWindow=false;
    QWindow.QIndex=userAnswrIndex=-1;

    //points
    BPoint_texture.loadFromFile("Data/G_BLUE TIME.png");
    unActivePoint_texture.loadFromFile("Data/0G_BLUE TIME.png");
    for(int i=0;i<10;i++)
    {
        Point_shape[i].setTexture(&unActivePoint_texture);
        Point_Size = {(float)BPoint_texture.getSize().x,(float)BPoint_texture.getSize().y};
        Point_shape[i].setSize(Point_Size);
        if(i==0){Point_shape[i].setPosition((window_Width*0.015),window_Height*0.075);}
        else{Point_shape[i].setPosition(Point_shape[i-1].getPosition().x+Point_Size.x,Point_shape[i-1].getPosition().y);}
    }
    CurrentPointIndex=-1;

    ////TimerBar
    //Texture ==> 0=normal,1=half time is passed,2=expired
    R_TimerBar_texture[0].loadFromFile("Data/G_RED TIME.png");
    R_TimerBar_texture[1].loadFromFile("Data/G_RED TIME01.png");
    R_TimerBar_texture[2].loadFromFile("Data/G_RED TIME01.png");
    R_TimerBar_texture[3].loadFromFile("Data/expiredTimeBar.png");

    for(int i=0;i<10;i++)
    {
        TimerBar_shape[i].setTexture(&R_TimerBar_texture[0]);
        TimerBar_Size = {(float)R_TimerBar_texture[0].getSize().x,(float)R_TimerBar_texture[0].getSize().y};
        TimerBar_shape[i].setSize(TimerBar_Size);
        if(i==0){TimerBar_shape[i].setPosition(window_Width*0.015,window_Height-window_Height*0.12);}
        else{TimerBar_shape[i].setPosition(TimerBar_shape[i-1].getPosition().x+TimerBar_Size.x,TimerBar_shape[i-1].getPosition().y);}
    }
    CurrentTimerBarIndex=10;
    randNum1=-1;
    bEndRoundOne=false;
    QCounter=-1;
    TotalPoints=0;


    ////Card letter
    letter_font.loadFromFile("Data/AbrilFatface-Regular.ttf");
    for(int i=0;i<10;i++)
    {
        Card[i]->randBatch[0] = rand()%10+48;
        Card[i]->randBatch[1] = rand()%26+65;
        Card[i]->randBatch[2] = rand()%26+97;
        Card[i]->randNum = rand()%3;

        if(Card[i]->randNum==0){Card[i]->letter = Card[i]->randBatch[0];}
        else if(Card[i]->randNum==1){Card[i]->letter = Card[i]->randBatch[1];}
        else {Card[i]->letter = Card[i]->randBatch[2];}

        Card[i]->letter_text.setFont(letter_font);
        Card[i]->letter_text.setCharacterSize(30);
        Card[i]->letter_text.setFillColor(sf::Color(255,250,180));
        Card[i]->letter_text.setString(Card[i]->letter);
    }
}

void RoundOne::ManageEvents(sf::Event *event,sf::Mouse *mouse,sf::RenderWindow *window,tgui::Gui &gui)
{
    //Mouse event
    if(event->type == sf::Event::MouseButtonPressed)
    {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {bLeftMouseClicked=true;}
    }
    if(event->type == sf::Event::MouseButtonReleased) {bLeftMouseClicked=false;}
}

void RoundOne::ManageLogics(sf::Event *event,sf::Mouse *mouse,sf::RenderWindow *window)
{
    ////Card logic's
    for(int i=0;i<10;i++)
    {
        timer++;
        if(Card[i] && timer >1000)
        {
            //Before Activation , moving Them to thier Position!
            if(!bStart)
            {
                if(i==0)
                {
                    if(Card[i]->sprite.getPosition().x > Card[i]->Position.x) {Card[i]->sprite.move(-10,0);}
                    else { if(Card[i]->sprite.getPosition().y > Card[i]->Position.y) {Card[i]->sprite.move(0,-10);} }
                }
                else if(i>0 && Card[i-1]->sprite.getPosition().x <= Card[i-1]->Position.x)
                {
                     if(Card[i]->sprite.getPosition().x > Card[i]->Position.x) {Card[i]->sprite.move(-10,0);}
                     else
                     {
                         if(i<5) { if(Card[i]->sprite.getPosition().y > Card[i]->Position.y) {Card[i]->sprite.move(0,-10);} }
                         else if(i>=5)
                         {
                             if(Card[i]->sprite.getPosition().y < Card[i]->Position.y) {Card[i]->sprite.move(0,10);}
                             if(i==9 && Card[i]->sprite.getPosition().y >= Card[i]->Position.y) {bStart=true;RoundOne_Clock.restart();}
                         }
                     }
                }
            }
            if(!bEndRoundOne && bStart && Card[i]->bActive)
            {
                if(!bPopUpQWindow)
                {
                    if(mouse->getPosition(*window).x > Card[i]->sprite.getPosition().x && mouse->getPosition(*window).x < Card[i]->sprite.getPosition().x+BCard_Size.x
                    && mouse->getPosition(*window).y > Card[i]->sprite.getPosition().y && mouse->getPosition(*window).y < Card[i]->sprite.getPosition().y+BCard_Size.y)
                    {
                        //OnClicked
                        if(bLeftMouseClicked)
                        {
                            QWindow.clock.restart();
                            QWindow.QIndex = i;
                            bPopUpQWindow=true;
                            CurrentPointIndex+=1;
                            QCounter+=1;
                        }else {Card[i]->sprite.setTexture(BCard_texture[1]);}
                    }else {Card[i]->sprite.setTexture(BCard_texture[0]);}
                }
                else if(bPopUpQWindow)
                {
                    QWindow.DisplayDelayTimer = QWindow.clock.getElapsedTime();
                    if(QWindow.DisplayDelayTimer.asSeconds()>2){bDisplayQWindow=true;}
                    if(QWindow.DisplayDelayTimer.asSeconds()>3){setQuestion();}
                }
            }
        }
    }

    //QWindow
    if(!bEndRoundOne && bDisplayQWindow && Card[QWindow.QIndex]->bActive)
    {
        //Detect Mouse Hover on Answr's
        for(int i=0;i<4;i++)
        {
            if(mouse->getPosition(*window).x > Answr[i].sprite.getPosition().x && mouse->getPosition(*window).x < Answr[i].sprite.getPosition().x+AnswrField_Size.x
            && mouse->getPosition(*window).y > Answr[i].sprite.getPosition().y && mouse->getPosition(*window).y < Answr[i].sprite.getPosition().y+AnswrField_Size.y)
            {
                if(bLeftMouseClicked && bActiveAnswr)
                {
                    userAnswrIndex=i;
                    bUserAnswered=true;
                    clock.restart();
                    bActiveAnswr=false;
                }else {if(bActiveAnswr){Answr[i].sprite.setTexture(AnswrField_texture[1]);};}
            }else {Answr[i].sprite.setTexture(AnswrField_texture[0]);}
        }

        if(bDisplayQWindow && bUserAnswered && !bActiveAnswr)
        {
            //ColorEffect
            AnswrDelayTime = clock.getElapsedTime();
            if(AnswrDelayTime.asSeconds() < 4)
            {
                randNum = rand()%4;
                switch(randNum)
                {
                    case 0 : Answr[userAnswrIndex].sprite.setTexture(AnswrField_texture[0]);break;
                    case 1 : Answr[userAnswrIndex].sprite.setTexture(RAnswr_texture);break;
                    case 2 : Answr[userAnswrIndex].sprite.setTexture(GAnswr_texture);break;
                    case 3 : Answr[userAnswrIndex].sprite.setTexture(RAnswr_texture);break;
                    default: break;
                }
            }
            else if(AnswrDelayTime.asSeconds() >=4 && AnswrDelayTime.asSeconds() <6)
            {
                if(checkAnswr()) {Answr[userAnswrIndex].sprite.setTexture(GAnswr_texture);Point_shape[CurrentPointIndex].setTexture(&BPoint_texture);}
                else {Answr[userAnswrIndex].sprite.setTexture(RAnswr_texture);Point_shape[CurrentPointIndex].setTexture(&unActivePoint_texture);}
            }
            else
            {
                Card[QWindow.QIndex]->bActive=false;
                bPopUpQWindow=false;
                bDisplayQWindow = false;
                bActiveAnswr=true;
                if(checkAnswr()) {Card[QWindow.QIndex]->sprite.setTexture(GCard_texture);TotalPoints+=1;}
                else {Card[QWindow.QIndex]->sprite.setTexture(RCard_texture);}

                if(Card[QWindow.QIndex]->randNum==0){Card[QWindow.QIndex]->letter_text.setPosition(Card[QWindow.QIndex]->sprite.getPosition().x+BCard_Size.x*0.425,Card[QWindow.QIndex]->sprite.getPosition().y+BCard_Size.y*0.4);}
                else{Card[QWindow.QIndex]->letter_text.setPosition(Card[QWindow.QIndex]->sprite.getPosition().x+BCard_Size.x*0.4,Card[QWindow.QIndex]->sprite.getPosition().y+BCard_Size.y*0.4);}
                if(QCounter==9){bEndRoundOne=true;}
            }
        }
    }

    //RoundTimer
    if(!bEndRoundOne && bStart){UpdateRoundTimer();}

}

void RoundOne::setQuestion()
{
    if(QWindow.QIndex > -1 && QWindow.QIndex < 10)
    {
         switch(QWindow.QIndex)
         {
            case 0 :
                    QWindow.Question_string = "What is the correct value to return to the operating system upon the \nsuccessful completion of a program?";
                    Answr[0].text.setString("A) -1");
                    Answr[1].text.setString("B) 1");
                    Answr[2].text.setString("C) 0");
                    Answr[3].text.setString("D) Programs do not return a value"); break;
            case 1 :
                    QWindow.Question_string = "Which of the following is NOT a type of algorithm?";
                    Answr[0].text.setString("A) Program");
                    Answr[1].text.setString("B) Flowchart");
                    Answr[2].text.setString("C) Decision Table");
                    Answr[3].text.setString("D) Pseudocode"); break;
            case 2 :
                    QWindow.Question_string = "In a flowchart the symbol that represents a condition based on which a\n decision should be made is";
                    Answr[0].text.setString("A) Procedure");
                    Answr[1].text.setString("B) Annonation");
                    Answr[2].text.setString("C) Decision");
                    Answr[3].text.setString("D) Process"); break;
            case 3 :
                    QWindow.Question_string = "Which of the following is/are valid variable name/s?";
                    Answr[0].text.setString("A) NBasic Salary");
                    Answr[1].text.setString("B) NBasic.Salary");
                    Answr[2].text.setString("C) NBasic_Salary");
                    Answr[3].text.setString("D) Basic Salary"); break;
            case 4 :
                    QWindow.Question_string = "In the following expression z = x + y x and y are called:";
                    Answr[0].text.setString("A) Operators");
                    Answr[1].text.setString("B) Values");
                    Answr[2].text.setString("C) Literals");
                    Answr[3].text.setString("D) Operands"); break;
            case 5 :
                    QWindow.Question_string = "Which operator has the highest precedence level?";
                    Answr[0].text.setString("A) ()");
                    Answr[1].text.setString("B) !");
                    Answr[2].text.setString("C) AND");
                    Answr[3].text.setString("D) *"); break;
            case 6 :
                    QWindow.Question_string = "What is the built in library function to adjust the allocated dynamic memory\n size.";
                    Answr[0].text.setString("A) resize");
                    Answr[1].text.setString("B) realloc");
                    Answr[2].text.setString("C) malloc");
                    Answr[3].text.setString("D) calloc"); break;
            case 7 :
                    QWindow.Question_string = "Which of the following is true?";
                    Answr[0].text.setString("A) 1");
                    Answr[1].text.setString("B) 66");
                    Answr[2].text.setString("C) 0");
                    Answr[3].text.setString("D) All of the above"); break;
            case 8 :
                    QWindow.Question_string = "What is required to avoid falling through from one case to the next?";
                    Answr[0].text.setString("A) end;");
                    Answr[1].text.setString("B) break;");
                    Answr[2].text.setString("C) Stop;");
                    Answr[3].text.setString("D) A semicolon"); break;
            case 9 :
                    QWindow.Question_string = "Which properly declares a variable of struct IPhoneX?";
                    Answr[0].text.setString("A) struct IPhoneX;");
                    Answr[1].text.setString("B) struct IPhoneX var;");
                    Answr[2].text.setString("C) IPhoneX;");
                    Answr[3].text.setString("D) int IPhoneX;"); break;
            default :
                    QWindow.Question_string = "No question given"; break;
         }
      QWindow.Question_text.setString(QWindow.Question_string);
    }
}

bool RoundOne::checkAnswr()
{
    if( (QWindow.QIndex==0 && userAnswrIndex==2) || (QWindow.QIndex==1 && userAnswrIndex==0) ||
        (QWindow.QIndex==2 && userAnswrIndex==2) || (QWindow.QIndex==3 && userAnswrIndex==2) ||
        (QWindow.QIndex==4 && userAnswrIndex==3) || (QWindow.QIndex==5 && userAnswrIndex==0) ||
        (QWindow.QIndex==6 && userAnswrIndex==1) || (QWindow.QIndex==7 && userAnswrIndex==0) ||
        (QWindow.QIndex==8 && userAnswrIndex==1) || (QWindow.QIndex==9 && userAnswrIndex==1) )
      {return true;}
    else {return false;}
}

void RoundOne::UpdateRoundTimer()
{
    //Round1 Time = 5m (300second)
    randNum1 = rand()%3;
    if(bStart)
    {
        if((int)RoundOne_Clock.getElapsedTime().asSeconds() >=15 && (int)RoundOne_Clock.getElapsedTime().asSeconds()<30){TimerBar_shape[9].setTexture(&R_TimerBar_texture[randNum1]);}
        else if((int)RoundOne_Clock.getElapsedTime().asSeconds()==30){TimerBar_shape[9].setTexture(&R_TimerBar_texture[3]);}

        if((int)RoundOne_Clock.getElapsedTime().asSeconds() >=45 && (int)RoundOne_Clock.getElapsedTime().asSeconds()<60){TimerBar_shape[8].setTexture(&R_TimerBar_texture[randNum1]);}
        else if((int)RoundOne_Clock.getElapsedTime().asSeconds()==60){TimerBar_shape[8].setTexture(&R_TimerBar_texture[3]);}

        if((int)RoundOne_Clock.getElapsedTime().asSeconds() >=75 && (int)RoundOne_Clock.getElapsedTime().asSeconds()<90){TimerBar_shape[7].setTexture(&R_TimerBar_texture[randNum1]);}
        else if((int)RoundOne_Clock.getElapsedTime().asSeconds()==90){TimerBar_shape[7].setTexture(&R_TimerBar_texture[3]);}

        if((int)RoundOne_Clock.getElapsedTime().asSeconds() >=105 && (int)RoundOne_Clock.getElapsedTime().asSeconds()<120){TimerBar_shape[6].setTexture(&R_TimerBar_texture[randNum1]);}
        else if((int)RoundOne_Clock.getElapsedTime().asSeconds()==120){TimerBar_shape[6].setTexture(&R_TimerBar_texture[3]);}

        if((int)RoundOne_Clock.getElapsedTime().asSeconds() >=135 && (int)RoundOne_Clock.getElapsedTime().asSeconds()<150){TimerBar_shape[5].setTexture(&R_TimerBar_texture[randNum1]);}
        else if((int)RoundOne_Clock.getElapsedTime().asSeconds()==150){TimerBar_shape[5].setTexture(&R_TimerBar_texture[3]);}

        if((int)RoundOne_Clock.getElapsedTime().asSeconds() >=165 && (int)RoundOne_Clock.getElapsedTime().asSeconds()<180){TimerBar_shape[4].setTexture(&R_TimerBar_texture[randNum1]);}
        else if((int)RoundOne_Clock.getElapsedTime().asSeconds()==180){TimerBar_shape[4].setTexture(&R_TimerBar_texture[3]);}

        if((int)RoundOne_Clock.getElapsedTime().asSeconds() >=195 && (int)RoundOne_Clock.getElapsedTime().asSeconds()<210){TimerBar_shape[3].setTexture(&R_TimerBar_texture[randNum1]);}
        else if((int)RoundOne_Clock.getElapsedTime().asSeconds()==210){TimerBar_shape[3].setTexture(&R_TimerBar_texture[3]);}

        if((int)RoundOne_Clock.getElapsedTime().asSeconds() >=225 && (int)RoundOne_Clock.getElapsedTime().asSeconds()<240){TimerBar_shape[2].setTexture(&R_TimerBar_texture[randNum1]);}
        else if((int)RoundOne_Clock.getElapsedTime().asSeconds()==240){TimerBar_shape[2].setTexture(&R_TimerBar_texture[3]);}

        if((int)RoundOne_Clock.getElapsedTime().asSeconds() >=255 && (int)RoundOne_Clock.getElapsedTime().asSeconds()<270){TimerBar_shape[1].setTexture(&R_TimerBar_texture[randNum1]);}
        else if((int)RoundOne_Clock.getElapsedTime().asSeconds()==270){TimerBar_shape[1].setTexture(&R_TimerBar_texture[3]);}

        if((int)RoundOne_Clock.getElapsedTime().asSeconds() >=285 && (int)RoundOne_Clock.getElapsedTime().asSeconds()<300){TimerBar_shape[0].setTexture(&R_TimerBar_texture[randNum1]);}
        else if((int)RoundOne_Clock.getElapsedTime().asSeconds()==300){TimerBar_shape[0].setTexture(&R_TimerBar_texture[3]);bEndRoundOne=true;}
    }
}

bool RoundOne::bCheckState()
{return bEndRoundOne;}

void RoundOne::Display(sf::RenderWindow *window)
{
    for(int i=0;i<10;i++)
    {
        window->draw(Card[i]->sprite);
        window->draw(Point_shape[i]);
        window->draw(TimerBar_shape[i]);
        if(!Card[i]->bActive){window->draw(Card[i]->letter_text);}
    }


    if(bDisplayQWindow)
    {
        window->draw(QWindow.shape);
        window->draw(QWindow.Question_text);
        for(int i=0;i<4;i++){window->draw(Answr[i].sprite);window->draw(Answr[i].text);}
    }
}
