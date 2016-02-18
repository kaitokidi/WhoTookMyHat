#ifndef SCENEPLAYABLE_HPP
#define SCENEPLAYABLE_HPP
#include "utils.hpp"
#include "Scene.hpp"
#include "Background.hpp"

class Game;

class scenePlayable : public Scene {
public:
    scenePlayable(Game* g, sf::RenderWindow* w, std::string next, std::string levelName = "cave1");

    ~scenePlayable();

    void init(sf::Vector2f aux = sf::Vector2f(0,0));

    void update(float deltaTime);

    void processInput();

    void render(sf::RenderTarget* target);

    void resizing();

    void readLVL(std::string levelName);

private:

    Game* _game;
    float _timer;
    Background bg;
    int _hatsOwned;
    std::string _next;
    sf::Sprite _hats[3];
    sf::Texture _hatsT[3];

};

#endif // SCENEPLAYABLE_HPP
