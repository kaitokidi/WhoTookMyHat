#include "EnemyFlying.hpp"
#define MOVEMENT 80

EnemyFlying::EnemyFlying(){
    _hp = 4;
    _objective.x = -1;
    _objective.y = -1;
    init();
}

void EnemyFlying::init(){
    _texture = &Resources::enemyStar;
    _spawnAnimation = &Resources::spawnAnim;
    _destroyAnimation = &Resources::destroyAnim;
}

void EnemyFlying::getNewObjective(){
    _objective.x = rand()%1024;
    _objective.y = rand()%768;

    float mod = (getModule(getPosition(), _objective))+0.0001;
    _deltaX = (_objective.x - getPosition().x) /mod;
    _deltaY = (_objective.y - getPosition().y) /mod;
}

void EnemyFlying::movement(float deltaTime, Background *bg){

    if(_objective.x == -1) getNewObjective();

    if(getPosition().x == _objective.x && getPosition().y == _objective.y ){
        _objective.x = -1;
    }

    _vel.x = MOVEMENT*deltaTime*_deltaX;
    _vel.y = MOVEMENT*deltaTime*_deltaY;
    if(bg->circleColision(sf::Vector2f(getPosition().x + _vel.x,getPosition().y + _vel.y), getGlobalBounds().width/2)){
        _objective.x = -1;
    }else {
        move(_vel.x, _vel.y);
        rotate(_vel.x/60.0*180/3.1415);
    }


}
