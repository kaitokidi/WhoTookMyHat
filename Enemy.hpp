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

protected:

    int _index;
    int _hp;
    bool _alive;
    bool _spawning;
    bool _destroying;

    sf::Vector2f _vel;

    sf::Clock _animTimer;

    sf::Texture _texture;
    std::vector < sf::Texture > _spawnAnimation;
    std::vector < sf::Texture > _destroyAnimation;


};

#endif // ENEMY_HPP
