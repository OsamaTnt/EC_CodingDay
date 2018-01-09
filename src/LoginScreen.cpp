#include "LoginScreen.h"

LoginScreen::LoginScreen(sf::RenderWindow *window,tgui::Gui &gui)
{
     //WindowSize
     window_Width = window->getSize().x; window_Height = window->getSize().y;

     //BackGround
     BG.texture.loadFromFile("Data/BG.jpg");
     BG.Size = {window_Width,window_Height}; BG.Position = {0,0};
     BG.shape.setTexture(&BG.texture);
     BG.shape.setSize(BG.Size);
     BG.shape.setPosition(BG.Position);

     //EC_Logo
     EC_Logo.texture.loadFromFile("Data/EC.png");
     EC_Logo.Size.x = EC_Logo.texture.getSize().x;  EC_Logo.Size.y = EC_Logo.texture.getSize().y;
     EC_Logo.Position.x = (window_Width/2) - (EC_Logo.Size.x/2); EC_Logo.Position.y = (window_Height/2) - (EC_Logo.Size.y/1.1);

     EC_Logo.shape.setTexture(&EC_Logo.texture);
     EC_Logo.shape.setSize(EC_Logo.Size);
     EC_Logo.shape.setPosition(EC_Logo.Position);

     //Gui ThemeConfig File
     ThemeConfigProfile = tgui::Theme::create("Data/LoginScreen_ThemeConfig.txt");

     //Gui UserInput EditBox
     CreateEditBox(gui);

     //Unlock Button
     setLoginButton(gui);

     //LoginInfo (After UserInput)
     loginInfo.font.loadFromFile("Data/IM_FELL_SC.ttf");
     loginInfo.text.setFont(loginInfo.font);
     loginInfo.text.setCharacterSize(14);

     //loginInfo.text.setSize(200,400);
     loginInfo.text.setPosition(EC_Logo.Position.x , EC_Logo.Position.y/0.75);

     SignedIn = false;

     //Official Sponsor
     Neon.Logotexture.loadFromFile("Data/login00.png");
     Neon.Logoshape.setTexture(&Neon.Logotexture);
     Neon.Logoshape.setSize(sf::Vector2f(50,50));

     Neon.font.loadFromFile("Data/IM_FELL_SC.ttf");
     Neon.text.setFont(Neon.font);
     Neon.text.setString("Powered By NeonElectroArt");
     Neon.text.setCharacterSize(18);
     Neon.text.setFillColor(sf::Color::Black);
     Neon.text.setPosition(window_Width-Neon.text.getLocalBounds().width-Neon.Logoshape.getSize().x*1.75,window_Height-Neon.text.getLocalBounds().height*2);
     Neon.Logoshape.setPosition(Neon.text.getPosition().x+Neon.text.getLocalBounds().width+Neon.Logoshape.getSize().x/2.75,window_Height-Neon.text.getLocalBounds().height*3);

}

void LoginScreen::ManageEvents(sf::Event *event,sf::RenderWindow *window,tgui::Gui &gui)
{
    while(window->pollEvent(*event))
    {
        //Gui HandleEvent
        gui.handleEvent(*event);

        //CloseWindow (Temporary!)
        if( (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) || (event->type == sf::Event::Closed) )
        {window->close();}
    }
}

void LoginScreen::Update()
{
    ///everyFrame
    //The Updated UserState!
    getLoginState();
}

void LoginScreen::CreateEditBox(tgui::Gui &gui)
{
    UserInput_EditBox = tgui::EditBox::create();
    if(UserInput_EditBox)
    {
        UserInput_EditBox = ThemeConfigProfile->load("EditBox");
        UserInput_EditBox->setSize(EC_Logo.Size.x/1.075,47.5);
        UserInput_EditBox->setPosition(EC_Logo.Position.x/0.98,EC_Logo.shape.getPosition().y+EC_Logo.Size.y*1.04);
        gui.add(UserInput_EditBox,"EditBox");
        UserInput_EditBox->setPasswordCharacter('*');
    }
}

void LoginScreen::UserLogin_Check(tgui::EditBox::Ptr UserInput_EditBox)
{
    //Open LoginInfo file
    loginInfo.file.open("Data/UserLogin.txt",std::ios::in);
    loginInfo.DisplayText = true;
    loginInfo.text.setPosition(UserInput_EditBox->getPosition().x*1.05,UserInput_EditBox->getPosition().y+UserInput_EditBox->getSize().y*1.05 );

   if(SignedIn == false)
   {
       //Check if the user entered a valid Id
       while(loginInfo.file>>loginInfo.UserId && !loginInfo.file.eof())
       {
            //if it's valid
            if(loginInfo.UserId == UserInput_EditBox->getText())
            {
                loginInfo.text.setString("Entering..");
                SignedIn = true;
                break;
            }
            //if not
            else if(loginInfo.UserId != UserInput_EditBox->getText())
            {
                 loginInfo.text.setString("Login Is Invalid!");
                 loginInfo.text.setFillColor(sf::Color::Red);
            }
       }
   }
   //close the file (reset it's pointer)
   loginInfo.file.close();
}

void LoginScreen::setLoginButton(tgui::Gui &gui)
{
    Unlock_Key_Button = tgui::Button::create();
    if(Unlock_Key_Button)
    {
        Unlock_Key_Button = ThemeConfigProfile->load("Button");
        Unlock_Key_Button->setPosition( (UserInput_EditBox->getPosition().x+UserInput_EditBox->getSize().x-10)
        ,(UserInput_EditBox->getPosition().y-Unlock_Key_Button->getSize().y/3.5 ));
        //Unlock_Key_Button->setText("Unlock");
        gui.add(Unlock_Key_Button,"Button");

        //Bind To function
        Unlock_Key_Button->connect("pressed",&LoginScreen::UserLogin_Check,this, UserInput_EditBox);
    }
}

bool LoginScreen::getLoginState()
{
    if(SignedIn)
    {UserInput_EditBox->hide();Unlock_Key_Button->hide();}
    return SignedIn;
}

void LoginScreen::Display(sf::RenderWindow *window)
{
    if(!SignedIn)
    {
        window->draw(BG.shape);
        window->draw(EC_Logo.shape);
        if(loginInfo.DisplayText==true) { window->draw(loginInfo.text); }
        window->draw(Neon.Logoshape);
        window->draw(Neon.text);
    }
}

LoginScreen::~LoginScreen() {}
