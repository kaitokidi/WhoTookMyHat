#ifndef ENEMYGHOST_HPP
#define ENEMYGHOST_HPP
#include "Enemy.hpp"

class EnemyGhost : public Enemy{
public:
    EnemyGhost();
    virtual void init();
    void getNewObjective();
    virtual void movement(float deltaTime, Background *bg);

protected:
    sf::Vector2f _objective;
    float _deltaX;
    float _deltaY;
};

#endif // ENEMYGHOST_HPP
