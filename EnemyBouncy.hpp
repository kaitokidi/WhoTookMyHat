#ifndef ENEMYBOUNCY_HPP
#define ENEMYBOUNCY_HPP
#include "Enemy.hpp"

class EnemyBouncy : public Enemy {

public:
    EnemyBouncy();
    virtual void init();
    virtual void movement(float deltaTime, Background *bg);

};

#endif // ENEMYBOUNCY_HPP
