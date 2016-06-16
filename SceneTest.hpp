#ifndef SCENETEST_HPP
#define SCENETEST_HPP
#include "utils.hpp"
#include "Scene.hpp"
#include "SceneSelector.hpp"

class Game;

class SceneTest : public Scene {

public:
    SceneTest(Game* g, sf::RenderWindow* w, std::string next, std::string text = "Press any Key");

    ~SceneTest();

    void init(sf::Vector2f aux = sf::Vector2f(0,0));

    void update(float deltaTime);

    void processInput();

    void render(sf::RenderTarget* target);

    void resizing();

private:

    float timer;
    Game* _game;
    sf::Text _text;
    std::string _next;
    sf::Sprite _sprite;
    sf::Texture _texture;

    SceneSelector _selector;

};

#endif // SCENETEST_HPP
