#ifndef ENEMYFLYING_HPP
#define ENEMYFLYING_HPP
#include "Enemy.hpp"

class EnemyFlying : public Enemy {

public:
    EnemyFlying();
    virtual void init();
    void getNewObjective();
    virtual void movement(float deltaTime, Background *bg);

protected:
    sf::Vector2f _objective;
    float _deltaX;
    float _deltaY;
};

#endif // ENEMYFLYING_HPP
