#ifndef __RESOURCES_HPP__
#define __RESOURCES_HPP__

#include "utils.hpp"

class Resources {
public:
    static void load();

    //DEFINE AS STATIC THE RESOURCES YOU WANT
    //static sf::Texture ...
    static sf::Texture key;
    static sf::Texture log;
    static sf::Texture eyes;
    static sf::Texture enemy;
    static sf::Texture chain;
    static sf::Texture ghost;
    static sf::Texture ninja;
    static sf::Texture bullet;
    static sf::Texture shooter;
    static sf::Texture pointer;
    static sf::Texture Portada;
    static sf::Texture talkBox;
    static sf::Texture doors_OX;
    static sf::Texture doors_OO;
    static sf::Texture doors_XX;
    static sf::Texture enemyBloc;
    static sf::Texture enemyStar;

    static sf::Shader cInvert;

    static sf::Font pauseMenuFont;

    static std::vector<sf::Texture> one;
    static std::vector<sf::Texture> none;
    static std::vector<sf::Texture> puff;
    static std::vector<sf::Texture> spawnAnim;
    static std::vector<sf::Texture> destroyAnim;

    static std::vector<SpriteSheetDescription> descriptions;


private:
    static SpriteSheetDescription loadDescription(std::string);

};

#endif
