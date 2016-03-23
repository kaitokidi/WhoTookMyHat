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

};

#endif // ENEMYBLOC_HPP
