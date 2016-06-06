#include "EnemyBouncy.hpp"
#define ENEMSPEED 50
#define JUMPSPEED 300

EnemyBouncy::EnemyBouncy(){
    init();
}

void EnemyBouncy::init(){
    _texture = &Resources::enemy;
    _spawnAnimation = &Resources::spawnAnim;
    _destroyAnimation = &Resources::destroyAnim;
}

void EnemyBouncy::movement(float deltaTime, Background *bg) {

    if(_vel.x == 0) {
        if(rand()%2){
            _vel.x = ENEMSPEED + rand()%20;
        }
        else _vel.x = -ENEMSPEED - rand()%20;
    }
    _vel.y += constant::gravity;

    sf::Vector2f dest(_vel.x * deltaTime, _vel.y * deltaTime);
    if(bg->circleColision( sf::Vector2f( getPosition().x, float(getPosition().y)+dest.y ), 60)){
        //_vel.y = 0;
        if(_vel.y > 0) _vel.y = - JUMPSPEED - rand()%50;
        else _vel.y = 0;
        setScale(1,0.7);
    } else move(0, dest.y);
    if(bg->circleColision( sf::Vector2f( dest.x + float(getPosition().x), getPosition().y ), 60)){
        _vel.x = 0;
        setScale(0.7,1);
    } else {
        move(dest.x, 0);
        if (_vel.x > 0){
            //rotate(_vel.x*deltaTime/60.0*180/3.1415);//ENEMROTATION*deltaTime);
        } //else rotate(_vel.x*deltaTime/60.0*180/3.1415);//-ENEMROTATION*deltaTime);
    }

    if(getScale().x <= 1){
        setScale(getScale().x + 0.2*deltaTime,getScale().y);
    }
    if(getScale().y <= 1){
        setScale(getScale().x, 0.2*deltaTime + getScale().y);
    }

}
