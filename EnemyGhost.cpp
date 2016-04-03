#include "EnemyGhost.hpp"
#define MOVEMENT 80

EnemyGhost::EnemyGhost(){
    _hp = 3;
    _objective.x = -1;
    _objective.y = -1;
    init();
}

void EnemyGhost::init(){
    _texture = Resources::ghost;
    _spawnAnimation = Resources::spawnAnim;
    _destroyAnimation = Resources::destroyAnim;
}

void EnemyGhost::getNewObjective(){
    _objective.x = rand()%1024;
    _objective.y = rand()%768;

    float mod = (getModule(getPosition(), _objective))+0.0001;
    _deltaX = (_objective.x - getPosition().x) /mod;
    _deltaY = (_objective.y - getPosition().y) /mod;
}

void EnemyGhost::movement(float deltaTime, Background *bg){

    if(_objective.x == -1) getNewObjective();

    if(getPosition().x == _objective.x && getPosition().y == _objective.y ){
        _objective.x = -1;
    }

    _vel.x = MOVEMENT*deltaTime*_deltaX;
    _vel.y = MOVEMENT*deltaTime*_deltaY;
    if(        getPosition().x - getGlobalBounds().width/2 +_vel.x <= 5
            || getPosition().x + getGlobalBounds().width/2 +_vel.x >= 1020
            || getPosition().y - getGlobalBounds().height/2 +_vel.y <= 5
            || getPosition().y + getGlobalBounds().height/2 +_vel.y >= 760 ) {
        _objective.x = -1;
        log("change");
    }else {
        move(_vel.x, _vel.y);
        std::cout << "letsmove" << getPosition().x << std::endl;
    }


}
