#ifndef SCENEPLAYABLE_HPP
#define SCENEPLAYABLE_HPP
#include "utils.hpp"
#include "Enemy.hpp"
#include "Scene.hpp"
#include "Player.hpp"
#include "Background.hpp"

class Game;

class scenePlayable : public Scene {
public:

    scenePlayable(Game* g, sf::RenderWindow* w, std::string next, std::string levelName, Player * player);

    ~scenePlayable();

    void resizing();

    void processInput();

    void readEnemies(int lvl);

    void update(float deltaTime);

    void readLVL(std::string levelName);

    void render(sf::RenderTarget* target);

    void init(sf::Vector2f aux = sf::Vector2f(0,0));

private:

    bool _picking;
    bool _playing;

    Game* _game;
    float _timer;
    Background bg;
    char _hatsOwned;
    Player* _player;
    std::string _next;
    sf::Sprite _hats[3];
    sf::Texture _hatsT[3];

    sf::Vector2i _spawnPoint;
//    std::list < Shoots > _shoot;
    std::list < Enemy > _enemies;
    std::queue < Enemy > _enemyPull;
    std::queue < int > _enemyTimePull;

};

#endif // SCENEPLAYABLE_HPP