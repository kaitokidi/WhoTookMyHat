#ifndef ANIMATEDCIRCLE_HPP
#define ANIMATEDCIRCLE_HPP

#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

typedef std::vector<sf::Texture *> VpT;

class AnimatedCircle{

private:

    VpT effect;
    VpT animation;

    int effectPointer;
    int animationPointer;

    sf::Texture* texture;
    sf::CircleShape circle;

public:

    AnimatedCircle();

    AnimatedCircle(float radius, unsigned int pointCount);

    AnimatedCircle(float radius, unsigned int pointCount, sf::Texture* tex);

    AnimatedCircle(float radius, unsigned int pointCount, sf::Texture* tex, float posX, float posY);


    void nextEffectFrame();

    void nextAnimationFrame();

    void setColor(sf::Color c);

    void setEffect(VpT &newEffect);

    void setAnimation(VpT &newAnimaiton);

    void setPosition (sf::Vector2f pos);

    void setPosition (float pX, float pY);

    sf::Vector2f getPosition();

    float getRadius();

    void draw(sf::RenderTarget *window);



};

#endif // ANIMATEDCIRCLE_HPP
