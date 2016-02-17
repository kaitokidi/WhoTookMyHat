#include "SceneTest.hpp"
#include "Resources.hpp"

SceneTest::SceneTest(Game *g, sf::RenderWindow *w, std::string next, std::string text) : Scene(g, w, sceneTypes::testScene, "test")  {
    _view = _window->getDefaultView();
    _next = next;
    _text.setFont(Resources::pauseMenuFont);
    _text.setString(text);
}

SceneTest::~SceneTest(){

}

void SceneTest::init(sf::Vector2f aux){
    timer = 0;
    _texture = Resources::key;
    _sprite.setTexture(_texture);
    _sprite.setOrigin(_sprite.getLocalBounds().width/2, _sprite.getLocalBounds().height/2);
    _sprite.setPosition(_window->getSize().x/2, _window->getSize().y/2);
    _text.setOrigin(_text.getGlobalBounds().width/2, _text.getGlobalBounds().height/2);
    _text.setPosition(_sprite.getPosition().x, _sprite.getPosition().y + _sprite.getGlobalBounds().height);
}

void SceneTest::update(float deltaTime){
    timer += deltaTime;
    _sprite.rotate(5*deltaTime);
    float f = 1+(std::sin(timer)/4);
    _text.setScale(sf::Vector2f(f,f));
}

void SceneTest::processInput(){
    sf::Event event;
    while(_window->pollEvent(event)){
        if (event.type == sf::Event::Closed) {_window->close(); exit(0);}
        if (event.type == sf::Event::KeyReleased) changeScene(_next);//{_window->close(); exit(0);}
    }
    InputManager::update();
}

void SceneTest::render(sf::RenderTarget *target){
    target->draw(_sprite);
    target->draw(_text);
}

void SceneTest::resizing(){
    //no tears
}
