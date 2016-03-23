#include "EnemyBloc.hpp"

EnemyBloc::EnemyBloc(){
    _hp = 5;
}

void EnemyBloc::init() {
    _texture = Resources::enemyBloc;
    _spawnAnimation = Resources::spawnAnim;
    _destroyAnimation = Resources::destroyAnim;
}

void EnemyBloc::movement(float deltaTime, Background *bg){


}
