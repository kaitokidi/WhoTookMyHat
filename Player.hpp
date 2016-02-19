#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <cmath>
#include <iostream>
#include "Eyes.hpp"
#include "Hook.hpp"
#include "utils.hpp"
#include "AnimatedCircle.hpp"

class Player {

protected:

    //Eyes
    Eyes eyes;
    Hook hook;
    float angle;

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
    Player(int id);
    void setAngle(float a);
    sf::Vector2f getPosition();
    void draw(sf::RenderTarget *w);
    void setHookPos(sf::Vector2f pos);
    void setPosition(sf::Vector2f pos);
    void setHookPos(float posX, float posY);
    void setPosition(float posX, float posY);

    int actionW(){return -1;}
    int actionS(){return -1;}
    int actionCW(){return -1;}
    int actionCS(){return -1;}

    void setDistantHookPos();
    float getSpeed() const;
    sf::Vector2f getPos() const;
    sf::Vector2f getLookPos() const;
    sf::Vector2f getHookPos() const;
    sf::Vector2f getMousePos() const;

    void setSpeed(float value);
    void setPos(const sf::Vector2f &value);
    void setHookPos(const sf::Vector2f &value);
    void setMousePos(const sf::Vector2f &value);

    void update(float deltaTime);
    //void update(sf::Packet &packet, float deltaTime);

};

#endif // PLAYER_HPP
