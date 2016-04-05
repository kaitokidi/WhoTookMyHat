#include "EnemyShooter.hpp"

EnemyShooter::EnemyShooter(std::list<Enemy *> *e) {
    _enem = e;
}

void EnemyShooter::shoot(sf::Vector2i orig, sf::Vector2i pos){
    _enem->push_back(new EnemyBullet(orig, pos));
}


