#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "utils.hpp"

class Player : public sf::Sprite {

public:
    Player();
    ~Player();

    void update(float deltaTime);
    void draw(sf::RenderTarget * target);

private:


};

#endif // PLAYER_HPP
