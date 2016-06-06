#include "EnemyBoss.hpp"
#define ENEMSPEED 100
#define NUMENEMIES 7

const char chars [NUMENEMIES] = {'s','w','f','b','g','n','d'};

EnemyBoss::EnemyBoss(std::list<Enemy *> *e, Player* p){
    _hp = 22;
    _enem = e;
    _player = p;
    _dir = direction::none;
    _movementScaler = 1;
    init();
}

void EnemyBoss::init() {
    _texture = &Resources::boss;
    _spawnAnimation = &Resources::spawnAnim;
    _destroyAnimation = &Resources::destroyAnim;
}

void EnemyBoss::hit(){
    setScale(getScale().x*0.9,getScale().y*0.9);
    --_hp;
    _hitted = true;
    if(_hp <= 0) {
        _index = 0;
        setRotation(0);
        _hitted = false;
        _destroying = true;
        _animTimer.restart();
    } else {
        //SPAWN ENEMY
        char enemy = chars[rand()%NUMENEMIES];
        switch(enemy) {
            case 's': // Spike ball
                _enem->push_back(new Enemy());
                _enem->back()->setPosition(sf::Vector2f(getPosition().x, getPosition().y));
            break;
            case 'w': // Wall square
                _enem->push_back(new EnemyBloc());
                _enem->back()->setPosition(sf::Vector2f(getPosition().x, getPosition().y));
            break;
            case 'f': // Flying star
                _enem->push_back(new EnemyFlying());
                _enem->back()->setPosition(sf::Vector2f(getPosition().x, getPosition().y));
            break;
            case 'b': // Bouncing spike
                _enem->push_back(new EnemyBouncy());
                _enem->back()->setPosition(sf::Vector2f(getPosition().x, getPosition().y));
            break;
            case 'g': // ghost
                _enem->push_back(new EnemyGhost());
                _enem->back()->setPosition(sf::Vector2f(getPosition().x, getPosition().y));
            break;
            case 'n': // ninja
                _enem->push_back(new EnemyNinja( _enem));
                _enem->back()->setPosition(sf::Vector2f(getPosition().x, getPosition().y));
            break;
            case 'd': //distant shooters
                _enem->push_back(new EnemySnipper( _enem, _player));
                _enem->back()->setPosition(sf::Vector2f(getPosition().x, getPosition().y));
            break;
            case 'm': //monster final boss
                _enem->push_back(new EnemyBoss( _enem, _player));
                _enem->back()->setPosition(sf::Vector2f(getPosition().x, getPosition().y));
            default:
            break;
        }
    }
}

void EnemyBoss::movement(float deltaTime, Background *bg){

        if(_dir == direction::none)     getNewDirection();
        if(_dir == direction::up)       _vel.y = -ENEMSPEED*deltaTime*_movementScaler;
        if(_dir == direction::left)     _vel.x = -ENEMSPEED*deltaTime*_movementScaler;
        if(_dir == direction::down)     _vel.y =  ENEMSPEED*deltaTime*_movementScaler;
        if(_dir == direction::right)    _vel.x =  ENEMSPEED*deltaTime*_movementScaler;

        _movementScaler += deltaTime;
        if(_movementScaler > 1.5) _movementScaler = 1.6;

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

void EnemyBoss::getNewDirection() {
    int r = rand()%4;
    _movementScaler = 0.4;
    _dir = direction::dir(r);
}
