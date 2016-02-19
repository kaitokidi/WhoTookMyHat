#ifndef EYES_HPP
#define EYES_HPP

#include <iostream>
#include <SFML/Graphics.hpp>

class Eyes {

private:

    sf::Sprite sprite;

public:
    Eyes();
    void setTexture();
    void setSize(float sizeX, float sizeY);
    void draw(sf::RenderTarget *window);
    void setPosition(sf::Vector2f pos);
    sf::Vector2f getSize();
};

#endif // EYES_HPP
