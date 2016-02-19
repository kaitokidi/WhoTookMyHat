#ifndef HOOK_HPP
#define HOOK_HPP

#include <cmath>
#include <SFML/Graphics.hpp>

class Hook {

private:

    float size;
    bool simple;

    sf::Sprite sprite;
    sf::Texture texture;

    sf::Vector2f origin;
    sf::Vector2f destiny;

    float getAngle(sf::Vector2f &orig, sf::Vector2f &des);
    float getModule(sf::Vector2f &orig, sf::Vector2f &des);

public:
    //Creator
    Hook();
    Hook(float w);
    Hook(float w, sf::Vector2f orig, sf::Vector2f dest);

    float getAngle();

    float getWidth() const;
    void setWidth(float value);

    sf::Vector2f getOrigin() const;
    void setOrigin(const sf::Vector2f &value);

    sf::Vector2f getDestiny() const;
    void setDestiny(const sf::Vector2f &value);

    void setTexture(std::string path);
    bool makeTextureRepeteable();

    void draw(sf::RenderTarget *window);
};

#endif // HOOK_HPP
