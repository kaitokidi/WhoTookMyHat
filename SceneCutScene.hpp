#ifndef SCENECUTSCENE_HPP
#define SCENECUTSCENE_HPP
#include "Scene.hpp"
#include "utils.hpp"
#include "Bullet.hpp"
#include "Player.hpp"
#include "Background.hpp"

class SceneCutScene : public Scene {

public:
    SceneCutScene(Game *g, sf::RenderWindow *w, std::string previous, std::string levelName, std::string next, Player *player);

    void resizing();

    void processInput();

    void update(float deltaTime);

    void readLVL(std::string name);

    void render(sf::RenderTarget* target);

    void init(sf::Vector2f aux = sf::Vector2f(0,0));

private:

    float _timer;
    Background bg;
    sf::Text _text;
    Player* _player;
    bool _updatedYet;
    bool _textActive;
    float _shootTimer;
    std::string LANG;
    std::string _prev;
    std::string _next;
    std::string _levelName;
    sf::Vector2i _spawnPoint;
    std::list < Bullet > _bullets;
    std::vector < std::string > _texts;

    sf::Text _thought;
    std::string _totalThought;


};

#endif // SCENECUTSCENE_HPP
