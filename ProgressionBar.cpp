#include "ProgressionBar.hpp"

ProgressionBar::ProgressionBar(sf::FloatRect rectangle) {

    _maxTime = 100;
    _time = 100;

    _background.setPosition(rectangle.left, rectangle.top);
    _progress.setPosition(rectangle.left, rectangle.top);

    _background.setSize(sf::Vector2f(rectangle.width, rectangle.height));
    _progress.setSize(sf::Vector2f(rectangle.width, rectangle.height*0.9));

    _background.setFillColor(sf::Color(200,200,200));
    _background.setOutlineColor(sf::Color(0,0,0));
    _background.setOutlineThickness(3);

    _progress.setFillColor(sf::Color(100,100,100));

}

void ProgressionBar::SetMaxTime(float time){
    _maxTime = time;
    _time = time;
}

bool ProgressionBar::finish() const { return _finish; }

void ProgressionBar::Update(float dt) {
    _time -= dt;
    float factor = _time/_maxTime;
    if(factor < 0) {
        factor = 0.01;
        _finish = true;
    }else _finish = false;
    _progress.setSize(sf::Vector2f(_background.getSize().x*factor, _progress.getSize().y));
}

void ProgressionBar::Draw(sf::RenderTarget * window){
    window->draw(_background);
    window->draw(_progress);
}
