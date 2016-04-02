#include "Bullet.hpp"
#define SPEED 600;

Bullet::Bullet(){
    _alive = true;
    setTexture(Resources::bullet);
    setOrigin(getLocalBounds().width/2, getLocalBounds().height/2);
}

bool Bullet::isAlive(){
    return _alive;
}

void Bullet::update(float deltaTime, Background *bg){
    sf::Vector2f movement;

    float angle = std::atan(deltaY / deltaX)*180/M_PI;
    float mod = std::sqrt(std::pow(deltaX,2) + std::pow(deltaY,2)); mod = 1;
    if(deltaX >= 0) { movement.x = std::cos(angle*M_PI/180) * mod * SPEED; }
    else movement.x = -1* std::cos(angle*M_PI/180) * mod * SPEED;
    if(deltaY >= 0) { movement.y = std::abs(std::sin(angle*M_PI/180)) * mod * SPEED; }
    else movement.y = -1* std::abs(std::sin(angle*M_PI/180)) * mod * SPEED;

    move(1+movement.x*deltaTime, 1+movement.y*deltaTime);

    if(bg->colision(getPosition())){
        _alive = false;
    }
}

void Bullet::setDestiny(sf::Vector2f destiny){
    _destiny = destiny;
    //TODO 50 hacks0rs wtf man
    deltaX = _destiny.x - getPosition().x-50;
    deltaY = _destiny.y - getPosition().y-50;
}

