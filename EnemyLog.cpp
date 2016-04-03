#include "EnemyLog.hpp"
#define ENEMSPEED 100
//enum dir { down, left, right, up , none };

EnemyLog::EnemyLog(){
    _hp = 1;
    init();
    _animTimer.restart();
}

void EnemyLog::init() {
    _texture = Resources::log;
    _spawnAnimation = Resources::puff;
    _destroyAnimation = Resources::spawnAnim;
}

void EnemyLog::update(float deltaTime   , Background *bg) {
    _aliveTimer += deltaTime;
    if(_aliveTimer > 10) {
        _alive = false;
        _destroying = true;
        _animTimer.restart();
    }

    if(_spawning){
        updateSprite(true);
        return;
    } if(_destroying){
        updateSprite(false);
        return;
    } else {
        setTexture(_texture, true);
        if(getOrigin().x == 0){
            setPosition(getPosition().x + getLocalBounds().width/2+32, getPosition().y + getLocalBounds().height/2+32);
            setOrigin( getLocalBounds().width/2, getLocalBounds().height/2);
        }
    }

    movement(deltaTime, bg);

}


void EnemyLog::hit(){
}

void EnemyLog::movement(float deltaTime, Background *bg){

    _vel.y += +2*deltaTime;

    sf::Vector2f dest(0, _vel.y);

    sf::FloatRect desrect = getGlobalBounds();
    desrect.top += _vel.y;
    if(bg->rectangleColision( desrect )){
        _vel.y = 0;
    } else move(0, dest.y);


}

