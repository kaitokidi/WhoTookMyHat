#include "EnemySnipper.hpp"
#define SHOOTTIME 5
EnemySnipper::EnemySnipper(std::list < Enemy* >* e, Player *p) : EnemyShooter(e){
    _player = p;
}

void EnemySnipper::update(float deltaTime, Background *bg){
    Enemy::update(deltaTime, bg);
    _timeBetweenShoots += deltaTime;
    if(_timeBetweenShoots > SHOOTTIME){
        _timeBetweenShoots = 0;
        shoot(sf::Vector2i(getPosition()), bg->getIntersection(sf::Vector2i(getPosition()), sf::Vector2i(_player->getPosition())));
    }
}
