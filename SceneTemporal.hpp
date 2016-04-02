#ifndef SCENETEMPORAL_HPP
#define SCENETEMPORAL_HPP
#include "utils.hpp"
#include "Scene.hpp"

class Game;

class SceneTemporal : public Scene {

public:
    SceneTemporal(Game* g, sf::RenderWindow* w, std::string next, int maxTime, std::string text = "", std::string name = "Portada");

    ~SceneTemporal();

    void init(sf::Vector2f aux = sf::Vector2f(0,0));

    void update(float deltaTime);

    void processInput();

    void render(sf::RenderTarget* target);

    void resizing();

private:

    Game* _game;
    bool _textOn;

    float timer;
    float _maxTime;

    sf::Text _text;
    std::string _next;
    std::string _name;
    sf::Sprite _sprite;
    sf::Texture _texture;
};

#endif // SCENETEMPORAL_HPP
