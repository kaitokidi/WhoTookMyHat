#include "Game.hpp"
#include "Resources.hpp"
#include "DataManager.hpp"
#include "ScenePlayable.hpp"
#include "TextBoxManager.hpp"

int main() {


    Resources::load();
    DataManager::load();
    SoundManager::load();
    TextBoxManager::load();


    srand(time(NULL));
    Game game;
    game.start();

    return 0;
}
