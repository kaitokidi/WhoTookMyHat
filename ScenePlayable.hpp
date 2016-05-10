#ifndef SCENEPLAYABLE_HPP
#define SCENEPLAYABLE_HPP
#include "utils.hpp"
#include "Enemy.hpp"
#include "Scene.hpp"
#include "Bullet.hpp"
#include "Player.hpp"
#include "EnemyBloc.hpp"
#include "Background.hpp"
#include "EnemyGhost.hpp"
#include "EnemyNinja.hpp"
#include "EnemySnipper.hpp"
#include "EnemyBouncy.hpp"
#include "EnemyFlying.hpp"

class Game;

class scenePlayable : public Scene {
public:

    scenePlayable(Game* g, sf::RenderWindow* w, std::string previous, std::string levelName, std::string next, Player * player);

    ~scenePlayable();

    void resizing();

    void processInput();

    void incrementHats();

    void writteLVL(int lvl);

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
    sf::Sprite _s;
    sf::Texture _t;
    int _hatsOwned;
    Player* _player;
    int _hatshits[3];
    int _hatsAchieved;
    float _shootTimer;
    std::string _prev;
    std::string _next;
    sf::Sprite _hats[3];
    sf::Texture _hatsT[3];
    std::string _levelName;
    sf::Sprite _playerHatSprite;
    sf::Texture _playerHatTexture;

    sf::Vector2i _spawnPoint;
    std::list < Bullet > _bullets;
    std::list < Enemy* > _enemies;
    std::queue < Enemy* > _enemyPull;
    std::queue < int > _enemyTimePull;

};

#endif // SCENEPLAYABLE_HPP
