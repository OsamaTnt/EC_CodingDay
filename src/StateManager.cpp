#include "StateManager.h"

StateManager::StateManager(sf::RenderWindow *window,tgui::Gui &gui)
{
    window->setFramerateLimit(60);
    window->setKeyRepeatEnabled(false);

    bDisplayLoginScreen=true;
    bDisplayIntro=bDisplayInstrs=false;
    for(int i=0;i<3;i++){bActiveRound[i]=false;bEndRound[i]=false;}

    enviroment = new Enviroment(window,gui,bActiveRound,&bDisplayInstrs);
    loginScreen = new LoginScreen(window,gui);
    intro = new Intro(window,gui);
    instructions = new Instructions(window,gui,&bDisplayInstrs,bActiveRound);
    roundOne = new RoundOne(window,enviroment->getCH());
    rewardScreen = new RewardScreen(window);
}

void StateManager::handleEvents(sf::Event *event,sf::Mouse *mouse,sf::RenderWindow *window,tgui::Gui &gui)
{
    ///handle events!!
    while(window->pollEvent(*event))
    {
        gui.handleEvent(*event);

        if(loginScreen) {loginScreen->ManageEvents(event,window,gui);}
        if(instructions) {instructions->ManageEvents(event,window,gui);}
        if(bActiveRound[0]) {roundOne->ManageEvents(event,mouse,window,gui);}
    }

    ///Every Frame..
    //loginScreen
    if(loginScreen && bDisplayLoginScreen)
    {
        loginScreen->Update();
        //check if the user has signed in , if so bDisplayIntro will be active
        if(loginScreen->getLoginState()) {bDisplayLoginScreen=false; bDisplayIntro=true;}
    }

    //Intro
    if(intro && bDisplayIntro)
    {
        intro->Update();
        //check if Intro gif's ended , if so bDisplayInstrs will be on
        if(!intro->ShownState()) {bDisplayIntro=false;bDisplayInstrs=true;}
    }

    //Instructions
    if(instructions && bDisplayInstrs)
    {instructions->Update(&enviroment->bInstrButtonClicked);}

    //Round1
    if(roundOne && bActiveRound[0]) {roundOne->ManageLogics(event,mouse,window);}
    if(roundOne) {if(roundOne->bCheckState()){bEndRound[0]=true;}}else{bEndRound[0]=false;}

    //Handle Reward
    rewardScreen->Update(bActiveRound,bEndRound);
}

void StateManager::Rendering(sf::RenderWindow *window,tgui::Gui &gui)
{
     //clear && Draw
     window->clear();
     if(loginScreen && bDisplayLoginScreen) {loginScreen->Display(window);}
     if(intro && bDisplayIntro) {intro->Display(window);}
     //enviroment of round1 will be displayed once the intro has been ended
     if(!bDisplayLoginScreen && !bDisplayIntro) {enviroment->Display(window,&bDisplayInstrs,bActiveRound);}
     if(instructions && bDisplayInstrs) {instructions->Display(window);}
     if(roundOne && bActiveRound[0]) {roundOne->Display(window);}
     if(rewardScreen) {rewardScreen->Display(window);}
     gui.draw();
     window->display();
}

StateManager::~StateManager()
{}
