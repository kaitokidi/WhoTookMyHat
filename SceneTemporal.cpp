#include "SceneTemporal.hpp"
#include "Resources.hpp"

SceneTemporal::SceneTemporal(Game *g, sf::RenderWindow *w, std::string next, int maxTime, std::string text, std::string name) : Scene(g, w, sceneTypes::testScene, "test")  {
    _view = _window->getDefaultView();
    _next = next;
    _text.setFont(Resources::pauseMenuFont);
    _text.setString(text);
    _maxTime = maxTime;
    _name = name;
}

SceneTemporal::~SceneTemporal(){

}

void SceneTemporal::init(sf::Vector2f aux){
    aux = aux;
    timer = 0;
    if(_name == "Portada") _texture = Resources::Portada;
    _sprite.setTexture(_texture);
    _sprite.setOrigin(_sprite.getLocalBounds().width/2, _sprite.getLocalBounds().height/2);
    //_sprite.setPosition(_window->getSize().x/2, _window->getSize().y/2);
    _sprite.setPosition(1024/2, 768/2);
    _text.setOrigin(_text.getGlobalBounds().width/2, _text.getGlobalBounds().height/2);
    _text.setPosition(_sprite.getPosition().x, _sprite.getPosition().y);
    _view = _window->getDefaultView();
    initView(&_view, sf::Vector2i(1024,768));
}

void SceneTemporal::update(float deltaTime){
    timer += deltaTime;

    float f = 1+(std::sin(timer)/4);
    _text.setScale(sf::Vector2f(f,f));
    if(timer > _maxTime){
        changeScene(_next);
    }
}

void SceneTemporal::processInput(){
    sf::Event event;
    while(_window->pollEvent(event)){
        if (event.type == sf::Event::Closed) {_window->close(); exit(0);}
        if (event.type == sf::Event::KeyReleased) changeScene(_next);//{_window->close(); exit(0);}
    }
    InputManager::update();
}

void SceneTemporal::render(sf::RenderTarget *target){
    target->draw(_sprite);
    target->draw(_text);
}

void SceneTemporal::resizing(){
    //no tears
}
