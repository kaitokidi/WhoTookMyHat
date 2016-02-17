#include "Game.hpp"

Game::Game() : _window(sf::VideoMode::getFullscreenModes()[0],"TOPKeK", sf::Style::Close | sf::Style::Fullscreen) {
    _window.setFramerateLimit(FRAMERATE);
    //_window.setMouseCursorVisible(false);

    _lastScene = nullptr;
    _currentScene = nullptr;

    initInput();
    Resources::load();
    DataManager::load();
    SoundManager::load();
    TextBoxManager::load();

    SoundManager::setGlobalSoundVolumen(100.0f);
    SoundManager::setGlobalMusicVolumen(100.0f);
    //SoundManager::playMusic("overWorld");
    //SoundManager::setLoop(true, "overWorld");

}

Game::~Game() {
    for (auto it = _scenes.begin(); it != _scenes.end(); ++it) {
        delete it->second;
    }
}

void Game::start() {
    loadScenes();
    changeScene("test");

    while (_currentScene != nullptr) {
        _currentScene->run();
    }

    exit(0);
}


void Game::changeScene(std::string sceneName) {
    auto it = _scenes.find(sceneName);
    if (it == _scenes.end()) {

        if(sceneName == "previous" && _lastScene != nullptr){

            _currentScene = _lastScene;
            _lastScene = nullptr;

        } else {
            std::cout << "The selected scene does not exist: " << sceneName << std::endl;
            exit(EXIT_FAILURE);
        }
    } else {
        if (_currentScene != nullptr) {
            _lastScene = _currentScene;
            _currentScene->killScene();
        }
        _currentScene = (*it).second;
        _currentScene->init();
    }
}


void Game::loadScenes() {

    // ADD YOUR SCENES WITH A NAME OF REFERENCE AND THE INITIALIZATION
    /* Example
    _scenes.insert(std::make_pair("menu",new SceneMenu(this, &_window)));
    _scenes.insert(std::make_pair("cutScene",new SceneCutScene(this, &_window,
                                                               Resources::AnimationIntro)));
   */

    _scenes.insert(std::make_pair("test", new SceneTest(this, &_window, "test2")));
    _scenes.insert(std::make_pair("test2", new SceneTest(this, &_window, "previous")));
}

void Game::loadScene(std::string sceneName) {

}


void Game::initInput() {

    InputManager::bind(InputAction::menuUp, sf::Keyboard::Up);
    InputManager::bind(InputAction::menuDown, sf::Keyboard::Down);
    InputManager::bind(InputAction::menuEnter, sf::Keyboard::Return);
    InputManager::bind(InputAction::menuEnter, 0, 0);  // Xbox A
    InputManager::bind(InputAction::menuBack, sf::Keyboard::Escape);
    InputManager::bind(InputAction::menuBack, 0, 1); // Xbox B
    InputManager::bind(InputAction::menuMovement, 0, sf::Joystick::Axis::Y);

    InputManager::bind(InputAction::up, sf::Keyboard::W);
    InputManager::bind(InputAction::down, sf::Keyboard::S);
    InputManager::bind(InputAction::left, sf::Keyboard::A);
    InputManager::bind(InputAction::right, sf::Keyboard::D);
    InputManager::bind(InputAction::pause, sf::Keyboard::Escape);
    InputManager::bind(InputAction::action, sf::Keyboard::Space);
    InputManager::bind(InputAction::action, 0, 0);  // Xbox A

    InputManager::bind(InputAction::p1movementX, 0, sf::Joystick::Axis::X);
    InputManager::bind(InputAction::p2movementX, 1, sf::Joystick::Axis::X);
    InputManager::bind(InputAction::p1movementY, 0, sf::Joystick::Axis::Y);
    InputManager::bind(InputAction::p2movementY, 1, sf::Joystick::Axis::Y);

    InputManager::bind(InputAction::pause, 0, 7); // Xbox start

	InputManager::bind(InputAction::reset, sf::Keyboard::F5);
    InputManager::bind(InputAction::reset, 0, 6);
}
