#ifndef ENEMYSNIPPER_HPP
#define ENEMYSNIPPER_HPP
#include "Enemy.hpp"
#include "Player.hpp"
#include "EnemyShooter.hpp"

class EnemySnipper : public Enemy, public EnemyShooter {

public:
    //TODO
    //init
    //Specific movement
    //specific pictures
    EnemySnipper(std::list < Enemy* >* e, Player* p);
    virtual void update(float deltaTime, Background* bg);
protected:
    Player* _player;
};

#endif // ENEMYSNIPPER_HPP
