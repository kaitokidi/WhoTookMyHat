#include "EnemySnipper.hpp"
#define SHOOTTIME 5
#define ENEMSPEED 50

void EnemySnipper::init(){
    _texture = &Resources::shooter;
    _spawnAnimation = &Resources::spawnAnim;
    _destroyAnimation = &Resources::destroyAnim;
}

EnemySnipper::EnemySnipper(std::list < Enemy* >* e, Player *p) : EnemyShooter(e){
    _player = p;
    init();
}

void EnemySnipper::update(float deltaTime, Background *bg){
    Enemy::update(deltaTime, bg);
    _timeBetweenShoots += deltaTime;
    if(_timeBetweenShoots > SHOOTTIME && _alive && !_destroying){
        _timeBetweenShoots = 0;
        shoot(sf::Vector2i(getPosition()), bg->getIntersection(sf::Vector2i(getPosition()),
                                                               sf::Vector2i(_player->getPosition())));
    }
}

void EnemySnipper::movement(float deltaTime, Background *bg){
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

    }

}
