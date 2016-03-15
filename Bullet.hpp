#ifndef BULLET_HPP
#define BULLET_HPP
#include "utils.hpp"
#include "Resources.hpp"
#include "Background.hpp"

class Bullet : public sf::Sprite {

public:

    Bullet();
    bool isAlive();
    void update(float deltaTime, Background *bg);
    void setDestiny(sf::Vector2f destiny);

private:

    bool _alive;
    float deltaX;
    float deltaY;
    sf::Vector2f _destiny;
};

#endif // BULLET_HPP
