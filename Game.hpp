#ifndef __GAME_HPP__
#define __GAME_HPP__

#include "utils.hpp"
#include "Scene.hpp"
#include "Resources.hpp"
#include "SceneTest.hpp"
#include "SceneTemporal.hpp"
#include "ScenePlayable.hpp"
#include "SceneCutScene.hpp"
#include "SceneAnimation.hpp"
#include "TextBoxManager.hpp"


class Game {

public:

    Game();
    ~Game();

    void start();

    void changeScene();
    void changeScene(std::string sceneName);

    std::string getLANGUAGE() const;
    void setLANGUAGE(const std::string &value);

private:
    Player _player;
    Scene* _lastScene;
    Scene* _currentScene;
    sf::RenderWindow _window;
    std::map<std::string, Scene*> _scenes;

    void initInput();
    void loadScenes();

};

#endif
