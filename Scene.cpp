#include "Scene.hpp"
#include "Game.hpp"

Scene::Scene(Game* g, sf::RenderWindow* w, sceneTypes sT, std::string name) :
    _game(g), 
    _window(w),
    _focus(true),
    _killed(false),
    _sceneName(name),
    _sceneType(sT)
     {
    _musicName = "none";
    _mousePointer.setTexture(Resources::pointer);
    _mousePointer.setOrigin(_mousePointer.getLocalBounds().width/2,_mousePointer.getLocalBounds().height/2);
}

Scene::~Scene(){}


void Scene::init(sf::Vector2f ) {

}

void Scene::run() {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate;
    sf::Time timePerFrame = sf::seconds(1.f/FRAMERATE);

    while (_window->isOpen()) {
        if (_focus) processInput();
        else withoutFocus();
        timeSinceLastUpdate = clock.restart();
        while (timeSinceLastUpdate > timePerFrame) {
            timeSinceLastUpdate -= timePerFrame;
            update(timePerFrame.asSeconds());
        }
        update(timePerFrame.asSeconds());
        display();
        if (_killed) {
            _game->changeScene(_nextScene);
            _killed = false;
            return;
        }
    }
}

void Scene::killScene() {
    _killed = true;
}

std::string Scene::getLanguage() {
    return _game->getLANGUAGE();
}

sceneTypes Scene::getType() {
    return _sceneType;
}

sf::View* Scene::getPtrView() {
    return &_view;
}

std::string Scene::getSceneName() {
    return _sceneName;
}

void Scene::setMusic(const std::string& name)
{
    _musicName = name;
}

void Scene::playMusic()
{
    SoundManager::playMusic(_musicName);
    SoundManager::setLoop(true, _musicName);
}

void Scene::stopMusic()
{
    SoundManager::stopMusic(_musicName);
}


void Scene::processInput() {
    sf::Event event;
    while (_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {_window->close(); exit(0);}
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            _window->close(); exit(0);
        }
    }
}

void Scene::update(float deltaTime) {
    (void)deltaTime;
}

void Scene::render() {
    render(_window);
}

void Scene::render(sf::RenderTarget* target) {
    (void) target;
}

void Scene::display() {
    _window->clear();
    _window->setView(_view);
    render();
    _window->setView(_window->getDefaultView());
    _mousePointer.setPosition(sf::Vector2f(sf::Mouse::getPosition(*_window)));
    _window->draw(_mousePointer);
    _window->display();
}

void Scene::initView(sf::View* view, sf::Vector2i windowSize) {
    int windowX = _window->getSize().x, windowY = _window->getSize().y;

    float xr = windowX / float(windowSize.x);
    float yr = windowY / float(windowSize.y);

    float aux;
    if (xr < yr) aux = 1/yr;
    else aux = 1/xr;

    xr *= aux;
    yr *= aux;
    sf::Vector2f min,max;

    min.x = (1.f - yr) / 2.f;
    min.y = (1.f - xr) / 2.f;
    max.x = 1.f - min.x*2;
    max.y = 1.f - min.y*2;

    view->reset(sf::FloatRect(0,0,windowSize.x,windowSize.y));
    view->setViewport(sf::FloatRect(min.x,min.y,max.x,max.y));
}

void Scene::resizing() {
    sf::Vector2i size(_view.getSize());
    initView(&_view,size);
}

void Scene::changeScene(std::string str){
    //extern int hardmode;
    //log("->", hardmode, &hardmode);
    _killed = true;
    _nextScene = str;
}

void Scene::withoutFocus() {
    sf::Event event;
    while (_window->pollEvent(event)) {
		if (event.type == sf::Event::Resized) resizing();
        else if (event.type != sf::Event::GainedFocus) continue;
        else {
            _focus = true;
            break;
        }
    }
}
