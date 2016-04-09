#ifndef ENEMYSNIPPER_HPP
#define ENEMYSNIPPER_HPP
#include "Enemy.hpp"
#include "Player.hpp"
#include "EnemyShooter.hpp"

class EnemySnipper : public Enemy, public EnemyShooter {

public:
    //TODO
    virtual void init();
    EnemySnipper(std::list < Enemy* >* e, Player* p);
    virtual void update(float deltaTime, Background* bg);
    virtual void movement(float deltaTime, Background *bg);
protected:
    Player* _player;
};

#endif // ENEMYSNIPPER_HPP
