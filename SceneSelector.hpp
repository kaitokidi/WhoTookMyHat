#ifndef SCENESELECTOR_HPP
#define SCENESELECTOR_HPP

#include "MyButton.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class SceneSelector {

private:
    sf::Sprite s;
    sf::Texture t;
    bool open;
    bool wantAnimation;

public:
    SceneSelector();
    ~SceneSelector();
    int select(sf::RenderWindow* window, std::vector<std::string> &buttonNames);
    void display(sf::RenderWindow* window);
    void display(sf::RenderWindow* window, std::string pathImage);
    void notAnimation();
    void animation();

};

#endif
