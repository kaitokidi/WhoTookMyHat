#ifndef __SCENE_HPP__
#define __SCENE_HPP__

#include "utils.hpp"

class Game;

class Scene {
friend class Game;
public:
    Scene(Game* g, sf::RenderWindow* w, sceneTypes sT, std::string name);
    virtual ~Scene();

    virtual void init(sf::Vector2f sceneIniCoord = sf::Vector2f(0,0));
    void run();
    void killScene();
    std::string getLanguage();

    virtual sceneTypes getType();
    sf::View* getPtrView();
    std::string getSceneName();

    void playMusic();
    void stopMusic();
    void setMusic(const std::string &name);

protected:

    bool _focus;
    Game* _game;
    sf::View _view;
    std::string _musicName;
    std::string _sceneName;
    sf::RenderWindow* _window;

    void render();

    virtual void display();
    virtual void resizing();

    virtual void processInput();
    virtual void update(float deltaTime);
    virtual void changeScene(std::string str);
    virtual void render(sf::RenderTarget* target);

    void initView(sf::View* view, sf::Vector2i windowSize);
    void initViewExpanded(sf::View* view, sf::Vector2i windowSize);



private: 

    bool _killed;
    sceneTypes _sceneType;
    std::string _nextScene;
    sf::Sprite _mousePointer;

    void withoutFocus();

};

#endif
