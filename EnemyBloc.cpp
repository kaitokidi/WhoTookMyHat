#include "EnemyBloc.hpp"
#define ENEMSPEED 1500
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
    _dir = direction::none;
    if(_dir == direction::none) getNewDirection();
    if(_dir == direction::up)       _vel.y = -ENEMSPEED*deltaTime;
    if(_dir == direction::left)     _vel.x = -ENEMSPEED*deltaTime;
    if(_dir == direction::down)     _vel.y =  ENEMSPEED*deltaTime;
    if(_dir == direction::right)    _vel.x =  ENEMSPEED*deltaTime;
    //_vel.y += constant::gravity;

    sf::Vector2f dest(_vel.x * deltaTime, _vel.y * deltaTime);

    //colide on y
    if(bg->rectangleColision( getGlobalBounds() )){
        _vel.y = 0; _dir = direction::none;
    } else move(0, dest.y);
    //colide on x
    if(bg->rectangleColision( getGlobalBounds() )){
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
