#include "EnemyBoss.hpp"
#include "EnemyBloc.hpp"
#include "EnemyGhost.hpp"
#include "EnemyNinja.hpp"
#include "EnemyBouncy.hpp"
#include "EnemyFlying.hpp"
#include "EnemySnipper.hpp"

#define ENEMSPEED 100
#define NUMENEMIES 7
#define BOSSMAXHP 22

const char chars [NUMENEMIES] = {'s','w','f','b','g','n','d'};

EnemyBoss::EnemyBoss(std::list<Enemy *> *e, Player* p, Background* bg){
    _hp = BOSSMAXHP;
    _bg = bg;
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
        sf::Vector2f position = getPosition();

        char enemy = chars[rand()%NUMENEMIES];
        switch(enemy) {
            case 's': // Spike ball
                _enem->push_back(new Enemy());
                _enem->back()->update(0.01, _bg);
                _enem->back()->setInitialPosition(position, _bg);
            break;
            case 'w': // Wall square
                _enem->push_back(new EnemyBloc());
                _enem->back()->update(0.01, _bg);                _enem->back()->setInitialPosition(position, _bg);
            break;
            case 'f': // Flying star
                _enem->push_back(new EnemyFlying());
                _enem->back()->update(0.01, _bg);_enem->back()->setInitialPosition(position, _bg);
            break;
            case 'b': // Bouncing spike
                _enem->push_back(new EnemyBouncy());
                _enem->back()->update(0.01, _bg);                _enem->back()->setInitialPosition(position, _bg);
            break;
            case 'g': // ghost
                _enem->push_back(new EnemyGhost());
                _enem->back()->update(0.01, _bg);                _enem->back()->setInitialPosition(position, _bg);
            break;
            case 'n': // ninja
                _enem->push_back(new EnemyNinja( _enem));
                _enem->back()->update(0.01, _bg);                _enem->back()->setInitialPosition(position, _bg);
            break;
            case 'd': //distant shooters
                _enem->push_back(new EnemySnipper( _enem, _player));
                _enem->back()->update(0.01, _bg);                _enem->back()->setInitialPosition(position, _bg);
            break;
            case 'm': //monster final boss
                _enem->push_back(new EnemyBoss( _enem, _player, _bg));
                 _enem->back()->update(0.01, _bg);               _enem->back()->setInitialPosition(position, _bg);
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
        if(_movementScaler > 1.5) {
            if(_movementScaler < 1.6 && rand()%3 == 0) getNewDirection();
            _movementScaler = 1.6;
        }

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
