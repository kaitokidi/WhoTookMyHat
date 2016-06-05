#ifndef ENEMYBOSS_HPP
#define ENEMYBOSS_HPP
#include "Enemy.hpp"
#include "Player.hpp"
#include "EnemyBloc.hpp"
#include "Background.hpp"
#include "EnemyGhost.hpp"
#include "EnemyNinja.hpp"
#include "EnemyBouncy.hpp"
#include "EnemyFlying.hpp"
#include "EnemySnipper.hpp"


class EnemyBoss : public Enemy{
public:
    EnemyBoss(std::list<Enemy *> *e, Player *p);

    virtual void hit();
    virtual void init();
    virtual void movement(float deltaTime, Background *bg);
    virtual void getNewDirection();

protected:

    Player* _player;
    direction::dir _dir;
    std::list<Enemy *>* _enem;
    float _movementScaler;

};

#endif // ENEMYBOSS_HPP
