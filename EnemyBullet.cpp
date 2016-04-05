#include "EnemyBullet.hpp"
#define SPEED 600;

EnemyBullet::EnemyBullet(){
    _hp = 1;
    init();
}

EnemyBullet::EnemyBullet(sf::Vector2i orig, sf::Vector2i dest){
    _hp = 1;
    _delta.x = (orig.x-dest.x);
    _delta.y = (orig.y-dest.y);
    _angle = std::atan(_delta.y / _delta.x)*180/M_PI;
    init();
    setPosition(sf::Vector2f(orig));
}

void EnemyBullet::init() {
    _texture = Resources::bullet;
    _spawnAnimation = Resources::none;
    _destroyAnimation = Resources::none;
}

void EnemyBullet::movement(float deltaTime, Background *bg){
    sf::Vector2f movement;

    if(_delta.x >= 0) { movement.x = std::cos(_angle*M_PI/180) * SPEED; }
    else movement.x = -1* std::cos(_angle*M_PI/180) * SPEED;
    if(_delta.y >= 0) { movement.y = std::abs(std::sin(_angle*M_PI/180)) * SPEED; }
    else movement.y = -1* std::abs(std::sin(_angle*M_PI/180)) * SPEED;

    move(1+movement.x*deltaTime, 1+movement.y*deltaTime);

    if(bg->colision(getPosition())){
        _alive = false;
    }
}
