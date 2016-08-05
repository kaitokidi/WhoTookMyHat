#include "LifeCounter.hpp"

LifeCounter::LifeCounter(){
    init();
}

LifeCounter::LifeCounter(sf::Vector2f pos){
    init();
    _position.x = pos.x;
    _position.y = pos.y;
}

void LifeCounter::init(){
    _lifes = hardmode? PLAYERHPHARD: PLAYERHPNORMAL;
    _hitted = false;
    _scale = 1;
    _position.x = 0;
    _position.y = 0;
    _sprite.setTexture(Resources::heart);
    _sprite.setOrigin(0, _sprite.getGlobalBounds().height/2);
}

int LifeCounter::lifes() const { return _lifes; }
void LifeCounter::setLifes(int lifes) {
    if(_lifes != lifes){
        hit();
    }
    _lifes = lifes;
}

sf::Vector2f LifeCounter::position() const { return _position; }
void LifeCounter::setPosition(const sf::Vector2f &position) { _position = position; }


void LifeCounter::Update(float dt) {
    _dtime = dt;
}

void LifeCounter::Draw(sf::RenderTarget * window){
    for(int i = 0; i < _lifes; ++i){

        _sprite.setPosition( _position.x+ i*_sprite.getGlobalBounds().width,
                             _position.y                                    );

        window->draw(_sprite);
    }
    if(_hitted && _scale > 0.1){
        _sprite.setPosition( _position.x+ _lifes*_sprite.getGlobalBounds().width,
                             _position.y                                    );
        _sprite.setScale(_scale, _scale);
        _scale -= 0.5*_dtime;
        window->draw(_sprite);
        _sprite.setScale(1,1);
    } else {
        _hitted = false; _scale = 1;
    }
}

void LifeCounter::hit() {
    _hitted = true;
    _scale = 1;
}
