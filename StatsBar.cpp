#include "StatsBar.hpp"
#include <iostream>
StatsBar::StatsBar(int maxHP, sf::Texture heart, sf::Texture halfHeart, sf::Texture emptyHeart){

    _space = 0;
    size.x = maxHP;
    size.y = maxHP;

    _maxHP = maxHP;
    _actualHP = maxHP;

    _heart = new ImgButton(heart, heart, this);
    _halfHeart = new ImgButton(halfHeart, halfHeart, this);;
    _emptyHeart = new ImgButton(emptyHeart, emptyHeart, this);;

    updatePics();
}


StatsBar::~StatsBar(){
    delete _heart;
    delete _halfHeart;
    delete _emptyHeart;
}

void StatsBar::updatePics() {
    sf::Vector2f butSize(size.y, size.y);
    _heart->setSize(butSize);
    _halfHeart->setSize(butSize);
    _emptyHeart->setSize(butSize);

    for(Widget* widget : _widgets) {
        delete widget;
    }
    _widgets.clear();
    for(int i  = 0; i < _maxHP; ++i ){
        if(i+1 <= _actualHP){
            add(new ImgButton(*_heart));
        }
        else {
            if( i < _actualHP && _actualHP < i+1){
                add(new ImgButton(*_halfHeart));
            }
            else {
                add(new ImgButton(*_emptyHeart));
            }
        }
    }
    StatsBar::updateShape();
}

void StatsBar::updateShape(){

    float pos_x = _space;
    //if(_parent)
      // pos_x = (_parent->getSize().x - getSize().x)/2.f;

    for(Widget* widget : _widgets) {
        sf::Vector2f auxsize = widget->getSize();
        widget->setPosition(pos_x,0);
        pos_x += auxsize.x + _space;
    }

    Widget::updateShape();
}

void StatsBar::setMaxHP(int value){
    if(_maxHP == value) return;
    _maxHP = value;
    updatePics();
}

void StatsBar::setActualHP(float value){
    if( _actualHP == value) return;
    _actualHP = value;
    updatePics();
}

/*sf::Vector2f StatsBar::getSize(){
    return size;
}*/
sf::Vector2f StatsBar::getSize() const {
    float max_y = 0;
    float x = 0;
    for(Widget* widget : _widgets) {
        sf::Vector2f size = widget->getSize();
        if(size.y > max_y) max_y = size.y;
        x += _space + size.x;
    }
    return sf::Vector2f(x+_space, max_y+_space*2);
}

void StatsBar::setSize(const sf::Vector2f &value){
    size = value;
    updatePics();
}

