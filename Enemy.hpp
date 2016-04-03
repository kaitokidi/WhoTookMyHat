#ifndef ENEMY_HPP
#define ENEMY_HPP
#include "utils.hpp"
#include "Bullet.hpp"
#include "Player.hpp"
#include "Background.hpp"

class Enemy : public sf::Sprite {

public:
    Enemy();
    virtual void hit();
    virtual void init();
    virtual void dyeing();
    virtual bool isAlive();
    virtual bool colisionable();
    virtual bool colides(Bullet* b);
    virtual bool colides(Player* p);
    virtual void updateSprite(bool alive);
    virtual void update(float deltaTime, Background* bg);
    virtual void movement(float deltaTime, Background *bg);


    bool hitted() const;
    float hittedTimer() const;

protected:

    int _hp;
    int _index;

    bool _alive;
    bool _hitted;
    bool _spawning;
    bool _destroying;

    float _aliveTimer;
    float _hittedTimer;

    sf::Vector2f _vel;

    sf::Clock _animTimer;

    sf::Texture _texture;

    std::vector < sf::Texture > _spawnAnimation;
    std::vector < sf::Texture > _destroyAnimation;


};

#endif // ENEMY_HPP
