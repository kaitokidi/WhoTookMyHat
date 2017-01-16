#include "Enemy.hpp"
#define ENEMSPEED 60
#define ANIMTIMER 0.10
#define HITEDTIMER 0.91
#define ENEMROTATION 40
#define ENEMYMAXHP 5

Enemy::Enemy(){

    _hp = ENEMYMAXHP;
    _index = 0;

    _alive = true;
    _hitted = false;
    _spawning = true;
    _destroying = false;

    _vel.x = _vel.y = 0;

    init();
    _hittedTimer = 0.0;
    _animTimer.restart();

}

//it calls dyeing, just in case you need it
void Enemy::hit(){
    --_hp;
    _hitted = true;
    if(_hp <= 0) {
        _index = 0;
        setRotation(0);
        _hitted = false;
        _destroying = true;
        _animTimer.restart();
        dyeing();
    }
}


void Enemy::init() {
    _texture = &Resources::enemy;
    _spawnAnimation = &Resources::spawnAnim;
    _destroyAnimation = &Resources::destroyAnim;
}

bool Enemy::isAlive()                             {
    return _alive;
}

bool Enemy::colisionable(){
    return (!_spawning && !_destroying && !_hitted);
}


void Enemy::update(float deltaTime, Background *bg){

    _aliveTimer += deltaTime;

    if(_spawning){
        updateSprite(true);
        return;
    } if(_destroying){
        updateSprite(false);
        return;
    } else {
        setTexture(*_texture, true);
        if(getOrigin().x == 0){
            setPosition(getPosition().x + getLocalBounds().width/2, getPosition().y + getLocalBounds().height/2);
            setOrigin( getLocalBounds().width/2, getLocalBounds().height/2);
        }
    }

    movement(deltaTime, bg);

    if(_hitted){
        _hittedTimer += deltaTime;
        if(_hittedTimer >= HITEDTIMER){
            _hitted = false;
            _hittedTimer = 0.0;
        }
    }
}

void Enemy::dyeing(){
    SoundManager::playSound("enemyDie");
    //IS INVOKED FROM THE HIT FUNCTION
    //if you implementd hit() be careful to call it if you want this function
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
        setTexture((*_spawnAnimation)[_index],true);
    } else {
        setTexture((*_destroyAnimation)[_index],true);
    }

    if(_animTimer.getElapsedTime().asSeconds() > ANIMTIMER){
        ++_index;
        if(    (_alive && size_t(_index) >= _spawnAnimation->size() )
            || (!_alive && size_t(_index) >= _destroyAnimation->size() ) ) {

            if(_destroying) {
                _destroying = false;
                _alive = false;
            }
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

void Enemy::setInitialPosition(sf::Vector2f position, Background* bg) {
    setPosition(position);
    if(bg->rectangleColision(sf::FloatRect(getGlobalBounds()))){
        int i = 1;
        int movx = 10;
        int movy = 10;
        while(bg->rectangleColision(sf::FloatRect(getGlobalBounds()))){
            //log("notOK, while", i,getGlobalBounds().left,getGlobalBounds().top, getGlobalBounds().width, getGlobalBounds().height);
              move(i*movx, 0);//R
              if(! bg->rectangleColision(sf::FloatRect(getGlobalBounds()))) return;
              setPosition(sf::Vector2f(position.x-2*i*movx,position.y)); //move(-2*i*movx,0);//L
              if(! bg->rectangleColision(sf::FloatRect(getGlobalBounds()))) return;
              move(i*movx,0);//-
              move(0, i*movy);//D
              if(! bg->rectangleColision(sf::FloatRect(getGlobalBounds()))) return;
              setPosition(sf::Vector2f(position.x,position.y-i*movy)); //move(0, -2*i*movy);//U
              if(! bg->rectangleColision(sf::FloatRect(getGlobalBounds()))) return;
              move(i*movx, 0); //UR
              if(! bg->rectangleColision(sf::FloatRect(getGlobalBounds()))) return;
              move(-2*i*movx,0); //UL
              if(! bg->rectangleColision(sf::FloatRect(getGlobalBounds()))) return;
              move(0,2*i*movy); //DL
              if(! bg->rectangleColision(sf::FloatRect(getGlobalBounds()))) return;
              move(2*i*movx,0); //DR
              if(! bg->rectangleColision(sf::FloatRect(getGlobalBounds()))) return;
              move(-i*movx,-i*movy); //base
              ++i;
        }
    }//else log("totOK",getGlobalBounds().left,getGlobalBounds().top, getGlobalBounds().width, getGlobalBounds().height);
}

bool Enemy::hitted() const { return _hitted; }
float Enemy::hittedTimer() const{ return _hittedTimer; }

