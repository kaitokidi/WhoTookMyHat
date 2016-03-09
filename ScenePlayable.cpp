#include "Resources.hpp"
#include "ScenePlayable.hpp"

scenePlayable::scenePlayable(Game *g, sf::RenderWindow *w, std::string next, std::string levelName, Player *player)
                                                    : Scene(g, w, sceneTypes::testScene, levelName)  {
    _view = _window->getDefaultView();
    initView(&_view, sf::Vector2i(1024,768));

    _player = player;
    //_player->setHookPos(100,100);
    //std::cout << "position "<< _player->getPosition().x << " , " << _player->getPosition().y << std::endl;
    _player->setPosition(_player->getRadius()*3,660);
    //std::cout << "position2 "<< _player->getPosition().x << " , " << _player->getPosition().y << std::endl;

    _next = next;
    readLVL(levelName);

    init();

  //  _picking = true;
//    _playing = false;
    _playing = true;
    _picking = false;

}

scenePlayable::~scenePlayable(){

}

void scenePlayable::readEnemies(int lvl){
//spoiler not neededs
}

void scenePlayable::init(sf::Vector2f aux){
    _timer = 0;
}

void scenePlayable::update(float deltaTime){
    _timer += deltaTime;

    if(_picking){

    }
    if(_playing){

       if(_enemyTimePull.size() > 0) {
           std::cout <<"timer = " << _timer << " and timepull = " << _enemyTimePull.front() << std::endl;
           if(_timer > _enemyTimePull.front()){
               _enemyTimePull.pop();
               _enemies.push_back(_enemyPull.front());
               _enemyPull.pop();
               _timer = 0;
           }
        }
        else {
           //s'han acabat els enemics
           if(_enemies.empty()) {
               _playing = false;
               _picking = true;
           }
       }

       for(auto it = _enemies.begin(); it != _enemies.end(); ++it){
           it->update(deltaTime, &bg);
       }

    }

    _player->update(deltaTime, sf::Vector2i(_window->mapPixelToCoords(sf::Mouse::getPosition((*_window)),_view)), &bg);
}

void scenePlayable::processInput(){
    sf::Event event;
    while(_window->pollEvent(event)){
        if (event.type == sf::Event::Closed) {_window->close(); exit(0);}
        switch (event.type){
            case  sf::Event::KeyPressed:
                //Close key
                if (event.key.code == sf::Keyboard::Escape) {
                    _window->close(); exit(0);
                }
                break;

            default:
                break;
        }
    }
    InputManager::update();
}

void scenePlayable::render(sf::RenderTarget *target){
    bg.draw(target);
    _player->draw(target);
    for(auto it = _enemies.begin(); it != _enemies.end(); ++it){
        target->draw(*it);
    }
}

void scenePlayable::resizing(){

}

void scenePlayable::readLVL(std::string levelName){

    std::string line;
    std::ifstream myfile (LVLDESCIPTPATH+levelName+".txt");

    if (myfile.is_open()) {
        std::getline (myfile,line);
        while(line[0] == '#') std::getline (myfile,line);

        while (line[0] != '$') {
            if(line[0] != '#'){
                bg.init(line);
            }
            std::getline (myfile,line);
            while(line[0] == '#') std::getline (myfile,line);
            //_hatsOwned = myStoi(line);
            _hatsOwned = line[0];

            for(int i = 0; i < 3; ++i){
                std::getline (myfile,line);
                while(line[0] == '#') std::getline (myfile,line);

                if(! _hatsT[i].loadFromFile(TEXTURETPATH+line)) std::cout << "not loaded texture of hat" << i << "on readlvl scenePlayable" << std::endl;
                else{
                    _hats[i].setTexture(_hatsT[i]);
                }
            }

            std::getline (myfile,line);
            while(line[0] == '#') std::getline (myfile,line);

            if(line == "spawn"){
                std::getline (myfile,line);
                while(line[0] == '#') std::getline (myfile,line);

                _spawnPoint.x = (myStoi(line));

                std::getline (myfile,line);
                while(line[0] == '#') std::getline (myfile,line);
                _spawnPoint.y = (myStoi(line));

                std::getline (myfile,line);
                while(line[0] == '#') std::getline (myfile,line);

            }

            if(line == "enemies"){

                std::getline (myfile,line);
                while(line[0] == '#') std::getline (myfile,line);

                while(line[0] != '$'){

                    if(line[0] == _hatsOwned){

                        std::getline (myfile,line);
                        while(line[0] == '#') std::getline (myfile,line);
                        for(int i = 0; i < line.size(); ++i){
                            switch(line[i]) {
                                case 'b':
                                _enemyPull.push(Enemy());
                                _enemyPull.back().setPosition(sf::Vector2f(_spawnPoint.x, _spawnPoint.y));
                                break;
                                default:
                                break;
                            }
                        }

                        std::getline (myfile,line);
                        while(line[0] == '#') std::getline (myfile,line);

                        for(int i = 0; i < line.size(); ++i){
                            if(line[i] != ' '){
                                _enemyTimePull.push(line[i]-'0');
                            }
                        }
                    } else {
                        std::getline (myfile,line);
                        while(line[0] == '#') std::getline (myfile,line);

                        std::getline (myfile,line);
                        while(line[0] == '#') std::getline (myfile,line);
                    }

                    std::getline (myfile,line);
                    while(line[0] == '#') std::getline (myfile,line);

                }

            }

        }
        myfile.close();
    }
    else std::cout << "scenePlayable file not oppened" << std::endl;


}
