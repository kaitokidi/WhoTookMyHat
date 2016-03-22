#ifndef ENEMYBLOC_HPP
#define ENEMYBLOC_HPP
#include "Enemy.hpp"

class EnemyBloc : public Enemy{
public:
    EnemyBloc();
    virtual void update(float deltaTime, Background* bg);
    virtual void movement(float deltaTime, Background *bg);
};

#endif // ENEMYBLOC_HPP
