#ifndef LOGINSCREEN_H
#define LOGINSCREEN_H
#include <iostream>
#include <fstream>
#include <string>
#include <TGUI/TGUI.hpp>

struct Image
{
    sf::Vector2f Size, Position;
    sf::Texture texture;
    sf::RectangleShape shape;
};

struct LoginInfo
{
    sf::Text text;
    sf::Font font;
    bool DisplayText;
    std::fstream file;
    std::string UserId;
};

struct Sponsor
{
    sf::Text text;
    sf::Font font;
    sf::Texture Logotexture;
    sf::RectangleShape Logoshape;
};

class LoginScreen
{
    private:
        float window_Width,window_Height;
        Image BG,EC_Logo;
        tgui::Theme::Ptr ThemeConfigProfile;
        tgui::EditBox::Ptr UserInput_EditBox;
        tgui::Button::Ptr Unlock_Key_Button;
        LoginInfo loginInfo;
        Sponsor Neon;
        bool SignedIn;

    public:
        LoginScreen(sf::RenderWindow *window,tgui::Gui &gui);
        void ManageEvents(sf::Event *event,sf::RenderWindow *window,tgui::Gui &gui);
        void CreateEditBox(tgui::Gui &gui);
        void UserLogin_Check(tgui::EditBox::Ptr UserInput_EditBox);
        void setLoginButton(tgui::Gui &gui);
        void Update();
        bool getLoginState();    //to check if the user signed In or not
        void Display(sf::RenderWindow *window);
        ~LoginScreen();
};
#endif
