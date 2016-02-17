#include "Widget.hpp"
#include <iostream>
Widget::Widget(Widget* parent) : _parent(parent){}

Widget::~Widget() {}

void Widget::setPosition(const sf::Vector2f &pos){
    _position = pos;
}

void Widget::setPosition(float x, float y){
    _position.x = x; _position.y = y;
}

const sf::Vector2f& Widget::getPosition() const{ return _position; }

bool Widget::processEvent(const sf::Event&,
                          const sf::Vector2f&,
                          const sf::RenderTarget&) {
    return false;
}

void Widget::processEvents(const sf::Vector2f&){}

void Widget::updateShape(){
    if(_parent){
        _parent -> updateShape();
    }
}
