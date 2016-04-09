#include "EnemyBullet.hpp"
#define SPEED 500;

EnemyBullet::EnemyBullet(){
    _hp = 1;
    init();
}

EnemyBullet::EnemyBullet(sf::Vector2i orig, sf::Vector2i dest){
    _hp = 1;
    _delta.x = (orig.x-dest.x)/( getModule(sf::Vector2f(orig), sf::Vector2f(dest)) );
    _delta.y = (orig.y-dest.y)/( getModule(sf::Vector2f(orig), sf::Vector2f(dest)) );
    _angle = std::atan2(_delta.y , _delta.x)*180/M_PI;
    init();
    setOrigin(getLocalBounds().width/2, getLocalBounds().height/2);
    setPosition(sf::Vector2f(orig));
}

void EnemyBullet::init() {
    _texture = Resources::bullet;
    _spawnAnimation = Resources::none;
    _destroyAnimation = Resources::none;
}

void EnemyBullet::movement(float deltaTime, Background *bg){
    move(_delta.x*deltaTime*-500, _delta.y*deltaTime*-500);
    if(bg->colision(getPosition())){
        _alive = false;
    }
}
