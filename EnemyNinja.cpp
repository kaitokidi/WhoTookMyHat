#include "EnemyNinja.hpp"
#define ENEMSPEED 100
//enum dir { down, left, right, up , none };

EnemyNinja::EnemyNinja(std::list<Enemy *> *e){
    _enem = e;
    _hp = 5;
    _dir = direction::none;
    init();
}

void EnemyNinja::init() {
    _texture = Resources::ninja;
    _spawnAnimation = Resources::spawnAnim;
    _destroyAnimation = Resources::destroyAnim;
}

void EnemyNinja::hit(){
    --_hp;
    _hitted = true;
    if(_hp <= 0) {
        _index = 0;
        setRotation(0);
        _hitted = false;
        _destroying = true;
        _animTimer.restart();
    } else {
        //spawn tronc
        if(rand()%4 == 0){
            ++_hp;
            _enem->push_back(new EnemyLog());
            _enem->back()->setPosition(sf::Vector2f(getPosition().x - getLocalBounds().width/2-32,
                                                    getPosition().y - getLocalBounds().height/2-32));
        }
    }
}

void EnemyNinja::movement(float deltaTime, Background *bg){

    if(!_hitted){

        if(_dir == direction::none)          getNewDirection();
        else if(_dir == direction::up)       _vel.y = -ENEMSPEED*deltaTime;
        else if(_dir == direction::left)     _vel.x = -ENEMSPEED*deltaTime;
        else if(_dir == direction::down)     _vel.y =  ENEMSPEED*deltaTime;
        else if(_dir == direction::right)    _vel.x =  ENEMSPEED*deltaTime;

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
    else{
        if(_dir == direction::none)          getNewDirection();
        else if(_dir == direction::up)       _dir =  direction::down;
        else if(_dir == direction::down)     _dir =    direction::up;
        else if(_dir == direction::left)     _dir = direction::right;
        else if(_dir == direction::right)    _dir =  direction::left;
    }
}

void EnemyNinja::getNewDirection() {
    int r = rand()%4;
    _dir = direction::dir(r);
}

