#ifndef STATEMANAGER_H
#define STATEMANAGER_H
#include <iostream>
#include <fstream>
#include <TGUI/TGUI.hpp>
#include "LoginScreen.h"
#include "Intro.h"
#include "Instructions.h"
#include "RoundOne.h"
#include "Enviroment.h"
#include "RewardScreen.h"

class StateManager
{
  private:
        class Enviroment *enviroment;class LoginScreen *loginScreen;
        class Intro *intro;class Instructions *instructions;
        class RoundOne *roundOne;class RewardScreen *rewardScreen;
        bool bActiveRound[3],bEndRound[3];

        //Render states
        bool bDisplayLoginScreen,bDisplayIntro,bDisplayInstrs;

    public:
        StateManager(sf::RenderWindow *window , tgui::Gui &gui);
        void handleEvents(sf::Event *event,sf::Mouse *mouse,sf::RenderWindow *window,tgui::Gui &gui);
        void Rendering(sf::RenderWindow *window,tgui::Gui &gui);

        ~StateManager();
};
#endif // STATEMANAGER_H
