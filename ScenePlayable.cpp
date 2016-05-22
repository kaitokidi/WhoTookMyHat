#include <stdio.h>
#include <unistd.h>
#include "Resources.hpp"
#include "ScenePlayable.hpp"

/*
colisió bullet _hat
*/

scenePlayable::scenePlayable(Game *g, sf::RenderWindow *w, std::string previous, std::string levelName, std::string next, Player *player)
                                                    : Scene(g, w, sceneTypes::testScene, levelName)  {
    _next = next;
    _hatsOwned = 0;
    _player = player;
    _prev = previous;
    readLVL(levelName);
    _levelName = levelName;
    init();

}

void scenePlayable::init(sf::Vector2f){

    _timer = 0;
    _view = _window->getDefaultView();
    initView(&_view, sf::Vector2i(1024,768));

    _shootTimer = 0;

    for(int i = 0; i < 3; ++i) { _hatshits[i] = 0; _hats[i].setScale(sf::Vector2f(1.0,1.0)); _hats[i].setRotation(0);}
    for(int i = 0; i < 3; ++i) _hats[i].setOrigin(_hats[i].getGlobalBounds().width/2,_hats[i].getGlobalBounds().height/2 );
    //init();

    if(! _t.loadFromFile(std::string(TEXTURETPATH+std::string("hat0.png")))) std::cout << "unable to open hat0" << std::endl;
    _s.setTexture(_t);
    _s.setOrigin(_s.getGlobalBounds().width/2, _s.getGlobalBounds().height/2);

    _picking = true;
    _playing = false;

    int value = 0;
    std::string line;
    std::ifstream inf( HATSPATH + std::string("progress.txt"));
    if(inf.is_open()){
        std::getline (inf,line);
        value = myStoi(line)+1;
    }else std::cout << "can't open progress.txt to read on init." << std::endl;
    _hatsAchieved = value;
    inf.close();

}

scenePlayable::~scenePlayable(){

}

void scenePlayable::readEnemies(int lvl) {
//spoiler not neededs
    //spoiler2 si que needs it

    std::string line;
    std::ifstream myfile (LVLDESCIPTPATH+_levelName+".txt");

    if (myfile.is_open()) {
        //read name of cave
        std::getline (myfile,line);
        while(line[0] == '#') std::getline (myfile,line);

        //read _hatsowned
        std::getline (myfile,line);
        while(line[0] == '#') std::getline (myfile,line);
        _hatsOwned = lvl;

        //until end reached
        while (line[0] != '$') {

            //read new line
            std::getline (myfile,line);
            while(line[0] == '#') std::getline (myfile,line);

            if(line == "enemies"){

                std::getline (myfile,line);
                while(line[0] == '#') std::getline (myfile,line);

                while(line[0] != '$'){

                    if(int(line[0]-'0') == lvl){

                        //read enemies
                        std::getline (myfile,line);

                        while(line[0] == '#') std::getline (myfile,line);
                        for(int i = 0; i < line.size(); ++i){
                            switch(line[i]) {
                                case 's': // Spike ball
                                _enemyPull.push(new Enemy());
                                _enemyPull.back()->setPosition(sf::Vector2f(_spawnPoint.x, _spawnPoint.y));
                                break;
                                case 'w': // Wall square
                                _enemyPull.push(new EnemyBloc());
                                _enemyPull.back()->setPosition(sf::Vector2f(_spawnPoint.x, _spawnPoint.y));
                                break;
                                case 'f': // Flying star
                                _enemyPull.push(new EnemyFlying());
                                _enemyPull.back()->setPosition(sf::Vector2f(_spawnPoint.x, _spawnPoint.y));
                                break;
                                case 'b': // Bouncing spike
                                _enemyPull.push(new EnemyBouncy());
                                _enemyPull.back()->setPosition(sf::Vector2f(_spawnPoint.x, _spawnPoint.y));
                                break;
                                case 'g': // ghost
                                _enemyPull.push(new EnemyGhost());
                                _enemyPull.back()->setPosition(sf::Vector2f(_spawnPoint.x, _spawnPoint.y));
                                break;
                                case 'n': // ninja
                                _enemyPull.push(new EnemyNinja(&_enemies));
                                _enemyPull.back()->setPosition(sf::Vector2f(_spawnPoint.x, _spawnPoint.y));
                                break;
                                case 'd': //distant shooters
                                _enemyPull.push(new EnemySnipper(& _enemies, _player));
                                _enemyPull.back()->setPosition(sf::Vector2f(_spawnPoint.x, _spawnPoint.y));
                                break;
                                case 'm': //monster final boss
                                _enemyPull.push(new EnemyBoss(& _enemies, _player));
                                _enemyPull.back()->setPosition(sf::Vector2f(_spawnPoint.x, _spawnPoint.y));
                                default:
                                break;
                            }
                        }

                        //read times
                        std::getline (myfile,line);
                        while(line[0] == '#') std::getline (myfile,line);

                        for(int i = 0; i < line.size(); ++i){
                            if(line[i] != ' '){
                                _enemyTimePull.push(line[i]-'0');
                            }
                        }
                    } else {
                        //read enemies
                        std::getline (myfile,line);
                        while(line[0] == '#') std::getline (myfile,line);
                        //read times
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
    else std::cout << "scenePlayable file not oppened loading enemies" << std::endl;


}

void scenePlayable::update(float deltaTime){

    _timer += deltaTime;
    _shootTimer += deltaTime;

    //PICKING
    if(_picking){

        bg._doorOpenedL = true;
        bg._doorOpenedR = false;
        if(_hatsOwned >= 3) bg._doorOpenedR = true;

        //Set selection Hats
        _hats[0].setPosition(300,150); _hats[1].setPosition(500,150); _hats[2].setPosition(700,150);

        if(_player->getPosition().y > 666){//està a terra
            if(bg._doorOpenedR && _player->getPosition().x > 948) {
                if (_player->getPosition().x < 1024+_player->getRadius()+50 ) {
                    _player->moveOut(90*deltaTime);
                    _bullets.clear();
                }
                else {
                    _player->setPosition(76, 666);
                    changeScene(_next);//move to next LVL
                }

            }
            else if(bg._doorOpenedL && _player->getPosition().x < 76) {
                if(_player->getPosition().x > 0-_player->getRadius()-50){
                    _player->moveOut(-90*deltaTime);
                    _bullets.clear();
                }else {
                    _player->setPosition(947,666);
                    changeScene(_prev);
                }
            }
            else _player->update(deltaTime, sf::Vector2i(_window->mapPixelToCoords(sf::Mouse::getPosition((*_window)),_view)), &bg);
        } else   _player->update(deltaTime, sf::Vector2i(_window->mapPixelToCoords(sf::Mouse::getPosition((*_window)),_view)), &bg);

        //Update Bullets
        for(auto it = _bullets.begin(); it != _bullets.end();){
            it->update(deltaTime, &bg);
            bool kill = false;
            for(int i = 0; i < 3; ++i){
                if(i <= _hatsOwned
                        && _hats[i].getGlobalBounds().contains(it->getPosition())
                   ){
                    ++_hatshits[i];
                    _hats[i].setScale(sf::Vector2f(_hats[i].getScale().x*2,_hats[i].getScale().y*2));
                    kill = true;
                }
            }
            if(kill) it = _bullets.erase(it);
            else ++it;
        }

        //HATS bouncing animation
        for(int i = 0; i < 3; ++i){
            _hats[i].rotate((std::sin(_timer))*20*deltaTime);
        }

        //Hat hitted
        for(int i = 0; i < 3; ++i){
            if(_hatshits[i] > 1){
                if(_enemyPull.empty()) readEnemies(i);
                _player->setHat(_hats[i]);
                _playing = true;
                _picking = false;
            }
        }
    }




    //PLAYING
    if(_playing){
        bg._doorOpenedL = false;
        bg._doorOpenedR = false;

       //spawn enemy if needed
       if(_enemyTimePull.size() > 0) {
           if(_timer > _enemyTimePull.front()){
               _enemyTimePull.pop();
               _enemies.push_back(_enemyPull.front());
               _enemyPull.pop();
               _timer = 0;
           }
        }
        else {
           //s'han acabat els enemics
           if(_enemies.empty() && _enemyPull.empty()) {
               _playing = false;
               _picking = true;
               for(int i = 0; i < 3; ++i) { _hatshits[i] = 0; _hats[i].setScale(sf::Vector2f(1.0,1.0)); _hats[i].setRotation(0);}
               //_hatsOwned = (_hatsOwned + 1);
               writteLVL(std::min(_hatsOwned,3));
           }
       }

       //Update Enemies
       for(auto it = _enemies.begin(); it != _enemies.end(); ++it){
           (*it)->update(deltaTime, &bg);
       }

       //Update Bullets
       for(auto it = _bullets.begin(); it != _bullets.end(); ++it){
           it->update(deltaTime, &bg);
       }


       //Erase dead bullets
       auto itb = _bullets.begin();
       for(;itb != _bullets.end();){
           if(! (*itb).isAlive()){
               itb = _bullets.erase(itb);
           }
           else ++itb;
       }

       //Erase dead enemies
       auto ite = _enemies.begin();
       for(; ite != _enemies.end();){
           if(! (*(*ite)).isAlive()){
               delete(*ite);
               ite = _enemies.erase(ite);
           }
           else ++ite;
       }

       //Colision between enemies and bullets
       ite = _enemies.begin();
       for(; ite != _enemies.end();++ite){

            itb = _bullets.begin();
           if((*ite)->colides(_player) && (*ite)->colisionable()){
               (*ite)->hit(); _player->hit();
           }
           else for(; itb != _bullets.end() && ite != _enemies.end();){

               //check enemy and bullet colision
               if((*ite)->colides(&(*itb))  && (*ite)->colisionable()){
                   itb = _bullets.erase(itb);
                   (*ite)->hit();
               }
               else ++itb;

           }

       }

    _player->update(deltaTime, sf::Vector2i(_window->mapPixelToCoords(sf::Mouse::getPosition((*_window)),_view)), &bg);

    }


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

                if (event.key.code == sf::Keyboard::Y){
                    int hat = (_player->actualHat()+1)%_hatsAchieved;
                    _player->setActualHat(hat);
                    if(! _playerHatTexture.loadFromFile( std::string (
                                              TEXTURETPATH+
                                              std::string("hat")+
                                              std::to_string(hat+1)+
                                              std::string(".png")                        ))) std::cout << "unable to open next hat" << std::endl;
                    _playerHatSprite.setTexture(_playerHatTexture);
                    _playerHatSprite.setOrigin(_playerHatSprite.getGlobalBounds().width/2, _playerHatSprite.getGlobalBounds().height/2);
                   _player->setHat(_playerHatSprite);
                }

                if(event.key.code == sf::Keyboard::K){
                    auto ite = _enemies.begin();
                    for(; ite != _enemies.end();){
                        delete(*ite);
                        ite = _enemies.erase(ite);
                    }
                }
                break;

            default:
                break;
        }
    }

    InputManager::update();

    if( InputManager::action(InputAction::shoot) > 0 && _shootTimer > constant::shootMaxTime){
        _shootTimer = 0;
        Bullet b;
        b.setPosition(_player->getPosition());
        b.setDestiny(sf::Vector2f(bg.getIntersection( sf::Vector2i(_player->getPosition()) ,sf::Vector2i(_window->mapPixelToCoords(sf::Mouse::getPosition((*_window)),_view)))));
        _bullets.push_back(b);
    }
}

void scenePlayable::incrementHats() {

    int value = 0;
    std::string line;
    std::ifstream inf( HATSPATH + std::string("progress.txt"));
    if(inf.is_open()){
        std::getline (inf,line);
        value = myStoi(line)+1;
    }else std::cout << "can't open progress.txt to read." << std::endl;
    _hatsAchieved = value;
    inf.close();

    std::ofstream aux( HATSPATH + std::string("progress.txt"));
    if(aux.is_open()){
        aux << std::to_string(value);
    }else std::cout << "can't open progress.txt to writte." << std::endl;
    aux.close();
}

void scenePlayable::writteLVL(int lvl){

    std::string line;
    std::ifstream inf( LVLDESCIPTPATH+_levelName+".txt");
    std::ofstream aux( LVLDESCIPTPATH+_levelName+".aux");

    if(inf.is_open() && aux.is_open()){

        //Name
        std::getline (inf,line);
        while(line[0] == '#') std::getline (inf,line);
        aux << line << '\n';

        //number
        std::getline (inf,line);
        while(line[0] == '#') std::getline (inf,line);
        int oldLVL = (line[0]-'0');
        _hatsOwned = std::min(std::max(oldLVL,lvl+1),4);

        if(oldLVL < _hatsOwned ) incrementHats();

        aux << std::min(std::max(oldLVL,lvl+1),4) << '\n';

        while(std::getline (inf,line)){
            aux << line << '\n';
        }

        inf.close();
        aux.close();

        std::ifstream auxin( LVLDESCIPTPATH+_levelName+".aux");
        std::ofstream out( LVLDESCIPTPATH+_levelName+".txt");
        if(auxin.is_open() && out.is_open()){

            std::cout << line << std::endl;
            while(std::getline (auxin,line)){
                out << line << '\n';
            }

        } else {log("no puc escriure u.u");}


        auxin.close();
        out.close();
    } else {log("NO, no puedo escribir aquí..."); std::cout << inf.is_open() << "  " << aux.is_open() << std::endl;}


}

void scenePlayable::render(sf::RenderTarget *target){
    bg.draw(target);

    //draw player
    _player->draw(target);

    //draw enemies
    for(auto it = _enemies.begin(); it != _enemies.end(); ++it){
        if((*it)->hitted()){
            float aux = (*it)->hittedTimer();
            Resources::cInvert.setParameter("deltaTime", aux);
            if (int(aux*10) %3 != 0) target->draw(*(*it),&Resources::cInvert);
            else target->draw(*(*it));
        }
        else target->draw(*(*it));

        if(DEBUGDRAW){
            sf::RectangleShape box;
            box.setFillColor(sf::Color(100,0,100,130));
            box.setOutlineThickness(4);
            box.setOutlineColor(sf::Color(100,0,100,180));
            box.setOrigin((*(*it)).getOrigin());
            box.setRotation((*(*it)).getRotation());
            box.setPosition((*(*it)).getPosition());
            box.setSize(sf::Vector2f ((*(*it)).getLocalBounds().width, (*(*it)).getLocalBounds().height) );
            target->draw(box);
        }
    }

    //if picking draw hats
    if(_picking){
        for(int i = 0; i < 3; ++i){
            if(i <= _hatsOwned ) target->draw(_hats[i]);
            else {
                _s.setPosition(300+200*i,150);
                target->draw(_s);
            }
        }
        if(DEBUGDRAW){
            sf::RectangleShape box;
            box.setFillColor(sf::Color(0,0,100,130));
            box.setOutlineThickness(5);
            box.setOutlineColor(sf::Color(0,0,100,180));
            for(int i = 0; i < 3; ++i){
                if(i <= _hatsOwned ){
                    box.setOrigin(_hats[i].getOrigin());
                    box.setRotation(_hats[i].getRotation());
                    box.setPosition(_hats[i].getPosition());
                    box.setSize(sf::Vector2f (_hats[i].getLocalBounds().width*_hats[i].getScale().x, _hats[i].getLocalBounds().height*_hats[i].getScale().y) );
                    target->draw(box);
                }
                else {
                    box.setOrigin(_s.getOrigin());
                    box.setPosition(300+200*i,150);
                    box.setSize(sf::Vector2f (_s.getLocalBounds().width*_s.getScale().x, _s.getLocalBounds().height*_s.getScale().y) );
                    target->draw(box);
                }
            }
        }
    }

    //draw bullets
    for(auto it = _bullets.begin(); it != _bullets.end(); ++it){
        target->draw(*it);
        if(DEBUGDRAW){
            sf::RectangleShape box;
            box.setFillColor(sf::Color(0,100,100,130));
            box.setOutlineThickness(2);
            box.setOutlineColor(sf::Color(0,100,100,180));
            box.setOrigin((*it).getOrigin());
            box.setRotation((*it).getRotation());
            box.setPosition((*it).getPosition());
            box.setSize(sf::Vector2f ((*it).getLocalBounds().width, (*it).getLocalBounds().height) );
            target->draw(box);
        }
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
            _hatsOwned = line[0]-'0';

            for(int i = 0; i < 3; ++i){
                std::getline (myfile,line);
                while(line[0] == '#') std::getline (myfile,line);

                if(! _hatsT[i].loadFromFile(TEXTURETPATH+line)) std::cout << "not loaded texture of hat" << i << "on readlvl scenePlayable" << std::endl;
                else{
                    _hats[i].setTexture(_hatsT[i],true);
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

                    if((line[0]-'0') == _hatsOwned){

                        std::getline (myfile,line);
                        while(line[0] == '#') std::getline (myfile,line);
                        /*
                        for(int i = 0; i < line.size(); ++i){
                            switch(line[i]) {
                                case 'b':
                                _enemyPull.push(new Enemy());
                                _enemyPull.back()->setPosition(sf::Vector2f(_spawnPoint.x, _spawnPoint.y));
                                break;
                                case 's':
                                _enemyPull.push(new EnemyBloc());
                                _enemyPull.back()->setPosition(sf::Vector2f(_spawnPoint.x, _spawnPoint.y));
                                break;
                                default:
                                break;
                            }
                        }
                        */

                        std::getline (myfile,line);
                        while(line[0] == '#') std::getline (myfile,line);

/*                        for(int i = 0; i < line.size(); ++i){
                            if(line[i] != ' '){
                                _enemyTimePull.push(line[i]-'0');
                            }
                        }*/
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
    else std::cout << "scenePlayable file " << LVLDESCIPTPATH+levelName << " not oppened" << std::endl;

   // log("readLVL finishes");

}
