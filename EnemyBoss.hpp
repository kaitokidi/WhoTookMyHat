#ifndef ENEMYBOSS_HPP
#define ENEMYBOSS_HPP
#include "Enemy.hpp"
#include "Player.hpp"
#include "Background.hpp"


class EnemyBoss : public Enemy{
public:
    EnemyBoss(std::list<Enemy *> *e, Player *p, Background* bg);

    virtual void hit();
    virtual void init();
    virtual void movement(float deltaTime, Background *bg);
    virtual void getNewDirection();

protected:

    Player* _player;
    Background* _bg;
    direction::dir _dir;
    std::list<Enemy *>* _enem;
    float _movementScaler;

};

#endif // ENEMYBOSS_HPP
