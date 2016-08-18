#include "Game.hpp"
//getFullscreenModes()[0]

static const std::string FIRSTSCENE = "test";
//static const std::string FIRSTSCENE = "level1";

Game::Game() : _window(sf::VideoMode::getDesktopMode(),"WhoTookMyHat", sf::Style::Close | sf::Style::Fullscreen) {
    _window.setFramerateLimit(FRAMERATE);
    _window.setMouseCursorVisible(false);

    _lastScene = nullptr;
    _currentScene = nullptr;

    initInput();

    SoundManager::setGlobalSoundVolumen(100.0f);
    SoundManager::setGlobalMusicVolumen(100.0f);
    //SoundManager::playMusic("overWorld");
    //SoundManager::setLoop(true, "overWorld");

    _player.setPosition(_player.getRadius()*3,660);

}

Game::~Game() {
    for (auto it = _scenes.begin(); it != _scenes.end(); ++it) {
        delete it->second;
    }
}

void Game::start() {
    loadScenes();
    changeScene(FIRSTSCENE);

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
std::string Game::getLANGUAGE() const
{
    return LANGUAGE;
}

void Game::setLANGUAGE(const std::string &value)
{
    LANGUAGE = value;
}



void Game::loadScenes() {

    // ADD YOUR SCENES WITH A NAME OF REFERENCE AND THE INITIALIZATION
    /* Example
    _scenes.insert(std::make_pair("menu",new SceneMenu(this, &_window)));
    _scenes.insert(std::make_pair("cutScene",new SceneCutScene(this, &_window,
                                                               Resources::AnimationIntro)));
   */
     _scenes.insert(std::make_pair("pause", new SceneTemporal(this, &_window, "previous", -1, "", "Pause.png")));

    _scenes.insert(std::make_pair("test",    new SceneTest(this, &_window, "portada")));
    _scenes.insert(std::make_pair("portada", new SceneTemporal(this, &_window, "anim0", 5, "", "Portada")));
    _scenes.insert(std::make_pair("anim0",   new SceneAnimation(this, &_window, "test2", "anim0","cutScene1")));
    _scenes.insert(std::make_pair("cutScene1", new SceneCutScene(this, & _window, "cutScene1", "cutScene1", "cutScene2", &_player)));
    _scenes.insert(std::make_pair("cutScene2", new SceneCutScene(this, & _window, "cutScene1", "cutScene3", "cutScene3", &_player)));
    _scenes.insert(std::make_pair("cutScene3", new SceneCutScene(this, & _window, "cutScene2", "cutScene2", "cutScene3_4", &_player)));
    _scenes.insert(std::make_pair("cutScene3_4", new SceneCutScene(this, & _window, "cutScene3", "cutScene3_4", "cutScene4", &_player)));
    _scenes.insert(std::make_pair("cutScene4", new SceneCutScene(this, & _window, "cutScene3_4", "cutScene4", "level1", &_player)));
    _scenes.insert(std::make_pair("level1",    new scenePlayable(this, & _window, "cutScene4", "level1", "cutScene5", &_player)));
    _scenes.insert(std::make_pair("cutScene5", new SceneCutScene(this, & _window, "level1", "cutScene5", "level2", &_player)));
    _scenes.insert(std::make_pair("level2",    new scenePlayable(this, & _window, "cutScene5", "level2", "cutScene6", &_player)));
    _scenes.insert(std::make_pair("cutScene6", new SceneCutScene(this, & _window, "level2", "cutScene6", "level3", &_player)));
    _scenes.insert(std::make_pair("level3",    new scenePlayable(this, & _window, "cutScene6", "level3", "cutScene7", &_player)));
    _scenes.insert(std::make_pair("cutScene7", new SceneCutScene(this, & _window, "level3", "cutScene7", "level4", &_player)));
    _scenes.insert(std::make_pair("level4",    new scenePlayable(this, & _window, "cutScene7", "level4", "level5", &_player)));
    _scenes.insert(std::make_pair("level5",    new scenePlayable(this, & _window, "level4", "level5", "End", &_player)));
    _scenes.insert(std::make_pair("End", new SceneTemporal(this, &_window, "End1", 5, "", "End.png")));
    _scenes.insert(std::make_pair("End1", new SceneTemporal(this, &_window, "End2", 4, "", "credits/credits1.png")));
    _scenes.insert(std::make_pair("End2", new SceneTemporal(this, &_window, "End3", 4, "", "credits/credits2.png")));
    _scenes.insert(std::make_pair("End3", new SceneTemporal(this, &_window, "End4", 4, "", "credits/credits3.png")));
    _scenes.insert(std::make_pair("End4", new SceneTemporal(this, &_window, "End5", 4, "", "credits/credits4.png")));
    _scenes.insert(std::make_pair("End5", new SceneTemporal(this, &_window, "EndEnd", 4, "", "credits/credits5.png")));
    _scenes.insert(std::make_pair("EndEnd", new SceneTemporal(this, &_window, "test", 10, "", "End.png")));

    //previously on how to hardcode animations...
    /*
    _scenes.insert(std::make_pair("s1", new SceneTemporal(this, &_window, "s2", 1, "", "scene1.png")));
    _scenes.insert(std::make_pair("s2", new SceneTemporal(this, &_window, "s3", 1, "", "scene2.png")));
    _scenes.insert(std::make_pair("s3", new SceneTemporal(this, &_window, "s4", 1, "", "scene3.png")));
    _scenes.insert(std::make_pair("s4", new SceneTemporal(this, &_window, "s5", 1, "", "scene4.png")));
    _scenes.insert(std::make_pair("s5", new SceneTemporal(this, &_window, "s6", 1, "", "scene5.png")));
    _scenes.insert(std::make_pair("s6", new SceneTemporal(this, &_window, "s7", 1, "", "scene6.png")));
    _scenes.insert(std::make_pair("s7", new SceneTemporal(this, &_window, "s8", 1, "", "scene7.png")));
    _scenes.insert(std::make_pair("s8", new SceneTemporal(this, &_window, "s9", 1, "", "scene8.png")));
    _scenes.insert(std::make_pair("s9", new SceneTemporal(this, &_window, "s10", 1, "", "scene9.png")));
    _scenes.insert(std::make_pair("s10", new SceneTemporal(this, &_window, "test2", 1, "", "scene10.png")));
    _scenes.insert(std::make_pair("test2",   new SceneTest(this, &_window, "anim0")));
    */

}


void Game::initInput() {

    InputManager::bind(InputAction::hook,  0, 4); // Xbox LB
    InputManager::bind(InputAction::shoot, 0, 5); // Xbox RB

    InputManager::bind(InputAction::movementX, 0, sf::Joystick::Axis::X);
    InputManager::bind(InputAction::movementY, 0, sf::Joystick::Axis::Y);

    InputManager::bind(InputAction::up,    sf::Keyboard::W);
    InputManager::bind(InputAction::left,  sf::Keyboard::A);
    InputManager::bind(InputAction::down,  sf::Keyboard::S);
    InputManager::bind(InputAction::right, sf::Keyboard::D);

    InputManager::bind(InputAction::hook,  sf::Keyboard::Space);
    InputManager::bind(InputAction::hook,  sf::Mouse::Right);
    InputManager::bind(InputAction::shoot, sf::Mouse::Left);
    InputManager::bind(InputAction::pause, sf::Keyboard::P);

    InputManager::bind(InputAction::action, 0,0);
    InputManager::bind(InputAction::pause, 0, 7); // Xbox start

}
