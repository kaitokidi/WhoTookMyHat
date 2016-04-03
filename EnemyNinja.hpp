#ifndef ENEMYNINJA_HPP
#define ENEMYNINJA_HPP
#include "Enemy.hpp"
#include "EnemyLog.hpp"

class EnemyNinja : public Enemy {

public:
        EnemyNinja(std::list < Enemy* >* e);
        virtual void hit();
        virtual void init();
        virtual void movement(float deltaTime, Background *bg);
        virtual void getNewDirection();

protected:

        direction::dir _dir;
        std::list < Enemy* >* _enem;
};
#endif // ENEMYNINJA_HPP
