#ifndef __RESOURCES_HPP__
#define __RESOURCES_HPP__

#include "utils.hpp"

class Resources {
public:
    static void load();

    //DEFINE AS STATIC THE RESOURCES YOU WANT
    //static sf::Texture ...
    static sf::Texture key;
    static sf::Texture talkBox;
    static sf::Texture doors_OX;
    static sf::Texture doors_OO;
    static sf::Texture doors_XX;


    static sf::Shader cInvert;

    static sf::Font pauseMenuFont;

    static std::vector<SpriteSheetDescription> descriptions;


private:
    static SpriteSheetDescription loadDescription(std::string fileName);

};

#endif
