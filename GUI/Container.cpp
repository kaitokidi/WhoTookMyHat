#include "Container.hpp"

Container::Container(Widget* parent) : Widget(parent),
_layout(nullptr) { }

Container::~Container() {
    if(_layout != nullptr and _layout->_parent == this) {
        _layout->_parent = nullptr;
        delete _layout;
    }
}

void Container::setLayout(Layout* layout) {

    if(_layout != nullptr and _layout->_parent == this) {
        _layout->_parent = nullptr;
    }
    if((_layout = layout) != nullptr) {
        _layout->_parent = this;
        _layout->updateShape();
    }
}

Layout* Container::getLayout()const {return _layout;}

sf::Vector2f Container::getSize()const {
    sf::Vector2f res(0,0);
    if(_layout)res = _layout->getSize();
    return res;
}

void Container::draw(sf::RenderTarget& target,
                     sf::RenderStates states) const {
    if(_layout) target.draw(*_layout,states);
}

bool Container::processEvent(const sf::Event& event,const
                             sf::Vector2f& parent_pos,
                             const sf::RenderTarget& target) {
    bool res = false;
    if(not res and _layout)
        res = _layout->processEvent(event,parent_pos, target);
    return res;
}

void Container::processEvents(const sf::Vector2f& parent_pos){
    if(_layout)
        _layout->processEvents(parent_pos);
}
