#ifndef ENEMYBOSS_HPP
#define ENEMYBOSS_HPP
#include "Enemy.hpp"

class EnemyBoss : public Enemy{
public:
    EnemyBoss();
    virtual void init();
    virtual void movement(float deltaTime, Background *bg);
    virtual void getNewDirection();

protected:

    direction::dir _dir;

};

#endif // ENEMYBOSS_HPP
