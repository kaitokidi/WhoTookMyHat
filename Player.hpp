#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <cmath>
#include <iostream>
#include "Eyes.hpp"
#include "Hook.hpp"
#include "utils.hpp"
#include "Background.hpp"
#include "AnimatedCircle.hpp"

class Player {

protected:

    //Eyes
    Eyes eyes;
    Hook hook;
    float angle;
    sf::Sprite hat;

    float speed;
    bool hooking;
    float radius;
    float lastUpdate;

    sf::Vector2f pos;
    sf::Vector2f vel;
    sf::Vector2f hookPos;
    sf::Vector2f mousePos;
    sf::Vector2f cameraPos;

    AnimatedCircle body;
    AnimatedCircle guide;

public:

    Player();

    void update(float deltaTime, sf::Vector2i auxMousePos, Background *bg);
    void draw(sf::RenderTarget *w);

    float getSpeed() const;
    float getRadius() const;
    sf::Vector2f getPosition();
    sf::Vector2f getPos() const;
    sf::Vector2f getLookPos() const;
    sf::Vector2f getHookPos() const;
    sf::Vector2f getMousePos() const;

    void setHat(sf::Sprite &spr);

    void setAngle(float a);
    void setSpeed(float value);

    void setPos(const sf::Vector2f &value);
    void setMousePos(const sf::Vector2f &value);

    void setPosition(float posX, float posY);
    void setPosition(const sf::Vector2f pos);

    void setDistantHookPos(sf::Vector2i mousePos, Background* bg);
    void setHookPos(float posX, float posY);
    void setHookPos(const sf::Vector2f value);

};

#endif // PLAYER_HPP
