#ifndef SCENEANIMATION_HPP
#define SCENEANIMATION_HPP

#include "Scene.hpp"
#include "utils.hpp"
#include "Bullet.hpp"
#include "Player.hpp"
#include "Background.hpp"

#define Action std::vector <std::string>
class Element : public sf::Sprite {

public:

    Element();
    bool getVisible() const;
    void setVisible(bool value);

    bool dead;
    bool visible;
    float myTimer;
    Action currentAction;
    std::queue < Action > actionQueue;

private:

};

class SceneAnimation : public Scene {

public:
    SceneAnimation(Game *g, sf::RenderWindow *w, std::string previous, std::string levelName, std::string next);

    void resizing();

    void processInput();

    void update(float deltaTime);

    void readLVL(std::string name);

    void render(sf::RenderTarget* target);

    void init(sf::Vector2f aux = sf::Vector2f(0,0));

private:

    float _timer;
    bool _waiting;
    std::string aux;
    std::string _prev;
    std::string _next;
    std::string _levelName;
    std::vector < std::string > _names;
    std::vector < sf::Texture* > _textures;
    std::vector < Element* > _elements;
    std::vector < Action > _orders;

};

#endif // SCENECUTSCENE_HPP
