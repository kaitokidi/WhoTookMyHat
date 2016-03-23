#include "EnemyBloc.hpp"
#define ENEMSPEED 100
//enum dir { down, left, right, up , none };

EnemyBloc::EnemyBloc(){
    _hp = 5;
    _dir = direction::none;
    init();
}

void EnemyBloc::init() {
    _texture = Resources::enemyBloc;
    _spawnAnimation = Resources::spawnAnim;
    _destroyAnimation = Resources::destroyAnim;
}


void EnemyBloc::movement(float deltaTime, Background *bg){

//    log("::::::::::::::::::::::::::");
    if(_dir == direction::none)     getNewDirection();
    if(_dir == direction::up)       _vel.y = -ENEMSPEED*deltaTime;
    if(_dir == direction::left)     _vel.x = -ENEMSPEED*deltaTime;
    if(_dir == direction::down)     _vel.y =  ENEMSPEED*deltaTime;
    if(_dir == direction::right)    _vel.x =  ENEMSPEED*deltaTime;

    sf::Vector2f dest(_vel.x, _vel.y);

    //colide on y
    sf::FloatRect desrect = getGlobalBounds();
    desrect.top += _vel.y;
    if(bg->rectangleColision( desrect )){
        _vel.y = 0; _dir = direction::none;
    } else move(0, dest.y);
    desrect.top -= _vel.y;
    desrect.left += _vel.x;
    //colide on x
    if(bg->rectangleColision( desrect )){
        _vel.x = 0; _dir = direction::none;
    } else move(dest.x, 0);

}

void EnemyBloc::getNewDirection() {
    int r = rand()%4;
//    if(r == 3) _dir = direction::down;
//    if(r == 1) _dir = direction::left;
//    if(r == 2) _dir = direction::right;
//    if(r == 0) _dir = direction::up;
    _dir = direction::dir(r);
}
