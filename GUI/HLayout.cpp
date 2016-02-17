#include <iostream>
#include "HLayout.hpp"

HLayout::HLayout(Widget *parent): Layout(parent) {}

HLayout::~HLayout() {
    for(Widget* widget : _widgets) {
        if(widget->_parent == this)
        delete widget;
    }
}

void HLayout::add(Widget* widget) {
    widget->_parent = this;
    _widgets.emplace_back(widget);
    updateShape();
}

Widget* HLayout::at(unsigned int index)const {
    return _widgets.at(index);
}

sf::Vector2f HLayout::getSize()const {

    float max_y = 0;
    float x = 0;
    for(Widget* widget : _widgets) {
        sf::Vector2f size = widget->getSize();
        if(size.y > max_y) max_y = size.y;
        x += _space + size.x;
    }

    return sf::Vector2f(x+_space, max_y+_space*2);
}

bool HLayout::processEvent(const sf::Event& event,
                           const sf::Vector2f& parent_pos,
                           const sf::RenderTarget& target) {
    for(Widget* widget : _widgets) {
        if(widget->processEvent(event,parent_pos+_position,target))
            return true;
    }
    return false ;
}

void HLayout::processEvents(const sf::Vector2f& parent_pos) {
    for(Widget* widget : _widgets)
    widget->processEvents(parent_pos);
}

void HLayout::updateShape() {

    float max_y = (_parent?_parent->getSize().y:0);
    for(Widget* widget : _widgets) {
        sf::Vector2f size = widget->getSize();
        float widget_y = size.y;
        if(widget_y > max_y)
        max_y = widget_y;
    }

    float pos_x = _space;
    if(_parent)
        pos_x = (_parent->getSize().x - getSize().x)/2.f;

    for(Widget* widget : _widgets) {
        sf::Vector2f size = widget->getSize();
        widget->setPosition(pos_x,(max_y-size.y)/2.0);
        pos_x += size.x + _space;
    }

    Widget::updateShape();

}

void HLayout::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform.translate(_position);
    for(Widget* widget : _widgets) {
        target.draw(*widget,states);
    }
}

