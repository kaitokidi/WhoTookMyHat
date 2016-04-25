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

    bool _doorOpenedL;
    bool _doorOpenedR;

    void init(std::string lvlDesc);
    void draw(sf::RenderTarget *target);
    void readLevel(std::string lvlDesc);

    bool colision(float x, float y);
    bool colision(sf::Vector2f pos);
    bool colision(sf::Vector2f pos, float rad);
    bool rectangleColision(sf::FloatRect rect);
    bool circleColision(sf::Vector2f pos, float rad);

    sf::Vector2i getIntersection(sf::Vector2i mousePos);
    sf::Vector2f getCircleColisionOffset(sf::Vector2f pos, float rad);
    sf::Vector2i getIntersection(sf::Vector2i position, sf::Vector2i mousePos);

private:


    sf::Sprite _doors;
    sf::Texture _bTexture;
    sf::Sprite _background;

    std::vector<sf::FloatRect> _boundaries;


};

#endif // BACKGROUND_HPP
