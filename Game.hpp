#ifndef __GAME_HPP__
#define __GAME_HPP__

#include "utils.hpp"
#include "Scene.hpp"
#include "Resources.hpp"
#include "SceneTest.hpp"
#include "SceneChanger.hpp"
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
    sf::RenderWindow _window;
    std::map<std::string, Scene*> _scenes;
    Scene* _currentScene;
    Scene* _lastScene;

    //sf::Mutex _mutex;
    //f::Thread* _thread;

    void loadScenes();
    void loadScene(std::string sceneName);

    void initInput();
};

#endif
