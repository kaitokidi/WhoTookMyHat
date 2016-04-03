#ifndef ENEMYLOG_HPP
#define ENEMYLOG_HPP
#include "Enemy.hpp"

class EnemyLog : public Enemy{

public:
    EnemyLog();
    virtual void hit();
    virtual void init();
    virtual void update(float deltaTime, Background *bg);
    virtual void movement(float deltaTime, Background *bg);

};

#endif // ENEMYLOG_HPP
