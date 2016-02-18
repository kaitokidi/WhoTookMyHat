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
    ~Background();
    Background(std::string lvlDesc);
    void init(std::string lvlDesc);
    void readLevel(std::string lvlDesc);
    void draw(sf::RenderTarget *target);

private:

    bool doorOpenedL;
    bool doorOpenedR;

    sf::Sprite doors;
    sf::Texture bTexture;
    sf::Sprite background;

    std::vector<sf::FloatRect> boundaries;


};

#endif // BACKGROUND_HPP
