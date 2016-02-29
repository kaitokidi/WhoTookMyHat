#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "utils.hpp"
#include "Resources.hpp"

class Background {

public:

    Background();
    Background(std::string lvlDesc);

    ~Background();

    void init(std::string lvlDesc);
    bool colision(sf::Vector2f pos);
    void readLevel(std::string lvlDesc);
    void draw(sf::RenderTarget *target);
    bool circleColision(sf::Vector2i pos, float rad);
    sf::Vector2i getIntersection(sf::Vector2i mousePos);

    bool colision(float x, float y);
private:

    bool _doorOpenedL;
    bool _doorOpenedR;

    sf::Sprite _doors;
    sf::Texture _bTexture;
    sf::Sprite _background;

    std::vector<sf::FloatRect> _boundaries;


};

#endif // BACKGROUND_HPP
