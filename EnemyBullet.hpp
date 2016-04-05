#ifndef ENEMYBULLET_HPP
#define ENEMYBULLET_HPP
#include "Enemy.hpp"

class EnemyBullet : public Enemy {

public:
    EnemyBullet();
    EnemyBullet(sf::Vector2i orig, sf::Vector2i dest);
    virtual void init();
    virtual void movement(float deltaTime, Background *bg);

protected:
    float _angle;
    sf::Vector2i _delta;

};

#endif // ENEMYBULLET_HPP
