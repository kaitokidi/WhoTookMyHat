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

public:

    Player();

    void draw(sf::RenderTarget *w);

    void updateSprite();
    void moveOut(float speed);
    void updateHits(float deltaTime);
    void update(float deltaTime, sf::Vector2i auxMousePos, Background *bg);

    void hit(int damage = 1);
    bool isDead();
    int getHP() const;
    int actualHat() const;
    float getSpeed() const;
    float getRadius() const;
    sf::Vector2f getPosition();
    sf::Vector2f getPos() const;
    sf::Vector2f getLookPos() const;
    sf::Vector2f getHookPos() const;
    sf::Vector2f getMousePos() const;
    sf::Vector2f getGuidePosition();

    void setAngle(float a);
    void setSpeed(float value);
    void setHP(int helthPoints);
    void setHat(sf::Sprite &spr);
    void setActualHat(int actualHat);
    void setPos(const sf::Vector2f &value);
    void setPosition(float posX, float posY);
    void setPosition(const sf::Vector2f pos);
    void setHookPos (float posX, float posY);
    void setHookPos (const sf::Vector2f value);
    void setMousePos(const sf::Vector2f &value);
    void setDistantHookPos(sf::Vector2i mousePos, Background* bg);

    bool hitted() const;
    void setHitted(bool hitted);
    float hittedTimer() const;
    void setHittedTimer(float hittedTimer);

protected:

    //Eyes
    Eyes eyes;
    Hook hook;
    sf::Sprite hat;

    bool _hitted;
    bool hooking;
    bool jumping;
    bool _destroying;

    float angle;
    float speed;
    float radius;
    float lastUpdate;
    float _hittedTimer;

    int _hp;
    int _index;
    int _actualHat;

    sf::Vector2f pos;
    sf::Vector2f vel;
    sf::Vector2f hookPos;
    sf::Vector2f mousePos;
    sf::Vector2f cameraPos;

    AnimatedCircle body;
    AnimatedCircle guide;

    sf::Clock _animTimer;
    std::vector<sf::Texture>* _destroyAnim;
};

#endif // PLAYER_HPP
