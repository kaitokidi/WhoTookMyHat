#include "Frame.hpp"

Frame::Frame(sf::RenderWindow& window, const sf::View& view) : Container(nullptr), _window(window), _view(view) {}

Frame::~Frame() {}

Frame& Frame::operator=(Frame&& original) {
	return original;
}

void Frame::draw() {
    _window.draw(*this);
}

void Frame::processEvents() {
    sf::Vector2f parent_pos(0,0);
    processEvents(parent_pos);
}

bool Frame::processEvent(const sf::Event& event) {
    sf::Vector2f parent_pos = getPosition();
    return processEvent(event,parent_pos,_window);
}


sf::Vector2f Frame::getSize()const {
    // sf::Vector2u size = sf::Vector2u(_view.getSize());
    return _view.getSize();
}

bool Frame::processEvent(const sf::Event& event,const sf::Vector2f& parent_pos, const sf::RenderTarget& target) {

    bool res = false;
    if(not res)
        res = Container::processEvent(event,parent_pos, target);
    return res;
}

void Frame::processEvents(const sf::Vector2f& parent_pos) {

    Container::processEvents(parent_pos);

    sf::Event event;
    while(_window.pollEvent(event))
        Container::processEvent(event,parent_pos,_window);
}
