#include "Enemy.hpp"
#define ANIMTIMER 0.10
#define ENEMSPEED 60
#define ENEMROTATION 40
Enemy::Enemy(){

    _hp = 4;
    _index = 0;

    _alive = true;
    _spawning = true;
    _destroying = false;

    _vel.x = _vel.y = 0;

    init();
    _animTimer.restart();

}

void Enemy::hit(){
    --_hp;
    if(_hp <= 0) {
        _index = 0;
        setRotation(0);
        _destroying = true;
        _animTimer.restart();
    }
}


void Enemy::init() {
    _texture = Resources::enemy;
    _spawnAnimation = Resources::spawnAnim;
    _destroyAnimation = Resources::destroyAnim;
}

bool Enemy::isAlive()                             {
    return _alive;
}

bool Enemy::colisionable(){
    return (!_spawning && !_destroying);
}


void Enemy::update(float deltaTime, Background *bg){

    if(_spawning){
        updateSprite(true);
        return;
    } if(_destroying){
        updateSprite(false);
        return;
    } else {
        setTexture(_texture);
        if(getOrigin().x == 0){
            setPosition(getPosition().x + getLocalBounds().width/2, getPosition().y + getLocalBounds().height/2);
            setOrigin( getLocalBounds().width/2, getLocalBounds().height/2);
        }
    }

    movement(deltaTime, bg);
}

void Enemy::dyeing(){
    //ghost function
}

bool Enemy::colides(Bullet *b){
    return getGlobalBounds().contains(b->getPosition());
}

bool Enemy::colides(Player *p){
    float rad = p->getRadius();
    sf::Vector2f pos = p->getPosition();
    sf::FloatRect _boundaries = getGlobalBounds();
    if(    _boundaries.contains(pos.x+rad, pos.y)
        || _boundaries.contains(pos.x-rad, pos.y)
        || _boundaries.contains(pos.x, pos.y+rad)
        || _boundaries.contains(pos.x, pos.y-rad)
                                                                ){
        return true;
    }
    else if(       getModule(pos, sf::Vector2f(_boundaries.left,_boundaries.top)) < rad
                || getModule(pos, sf::Vector2f(_boundaries.left+_boundaries.width,_boundaries.top)) < rad
                || getModule(pos, sf::Vector2f(_boundaries.left,_boundaries.top+_boundaries.height)) < rad
                || getModule(pos, sf::Vector2f(_boundaries.left+_boundaries.width,_boundaries.top+_boundaries.height)) < rad
                   ){
        return true;
    }
    return false;
}

void Enemy::updateSprite(bool alive){
    if(alive){
        setTexture(_spawnAnimation[_index]);
    } else {
        setTexture(_destroyAnimation[_index]);
    }

    if(_animTimer.getElapsedTime().asSeconds() > ANIMTIMER){
        ++_index;
        if(_index > 8) {
            if(_destroying) _destroying = _alive = false;
            else _spawning = false;
        }
        _animTimer.restart();
    }
}

void Enemy::movement(float deltaTime, Background *bg) {

    if(_vel.x == 0) {
        if(rand()%2){
            _vel.x = ENEMSPEED + rand()%20;
        }
        else _vel.x = -ENEMSPEED - rand()%20;
    }
    _vel.y += constant::gravity;

    sf::Vector2f dest(_vel.x * deltaTime, _vel.y * deltaTime);
    if(bg->circleColision( sf::Vector2f( getPosition().x, float(getPosition().y)+dest.y ), 60)){
        _vel.y = 0;
    } else move(0, dest.y);
    if(bg->circleColision( sf::Vector2f( dest.x + float(getPosition().x), getPosition().y ), 60)){
        _vel.x = 0;
    } else {
        move(dest.x, 0);
        if (_vel.x > 0){
            rotate(_vel.x*deltaTime/60.0*180/3.1415);//ENEMROTATION*deltaTime);
        } else rotate(_vel.x*deltaTime/60.0*180/3.1415);//-ENEMROTATION*deltaTime);
    }


}
