#ifndef ENEMYSHOOTER_HPP
#define ENEMYSHOOTER_HPP
#include "EnemyBullet.hpp"

class EnemyShooter {
public:
    EnemyShooter(std::list < Enemy* >* e);
    virtual void shoot(sf::Vector2i orig, sf::Vector2i pos);


protected:
    int _maxShoots;
    float _timeBetweenShoots;
    std::list < Enemy* >* _enem;

};

#endif // ENEMYSHOOTER_HPP
