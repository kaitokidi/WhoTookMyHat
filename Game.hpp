#ifndef __GAME_HPP__
#define __GAME_HPP__

#include "utils.hpp"
#include "Scene.hpp"
#include "Resources.hpp"
#include "SceneTest.hpp"
#include "SceneChanger.hpp"
#include "ScenePlayable.hpp"
#include "TextBoxManager.hpp"


class Game {
friend class SceneMenu;
friend class SceneCutScene;
public:

    Game();
    ~Game();

    void start();

    void changeScene(SceneChanger* sC);
    void changeScene(std::string sceneName);


private:
    //Player _player
    Scene* _lastScene;
    Scene* _currentScene;
    sf::RenderWindow _window;
    std::map<std::string, Scene*> _scenes;

    //sf::Mutex _mutex;
    //sf::Thread* _thread;

    void initInput();
    void loadScenes();
    void loadScene(std::string sceneName);

};

#endif
