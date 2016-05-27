#ifndef ENEMYBLOC_HPP
#define ENEMYBLOC_HPP
#include "Enemy.hpp"

class EnemyBloc : public Enemy{
public:
    EnemyBloc();
    virtual void init();
    virtual void movement(float deltaTime, Background *bg);
    virtual void getNewDirection();

protected:

    direction::dir _dir;
    float _movementScaler;

};

#endif // ENEMYBLOC_HPP
