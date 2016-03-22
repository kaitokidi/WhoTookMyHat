#include <stdio.h>
#include <unistd.h>
#include "Resources.hpp"
#include "ScenePlayable.hpp"
/* QUESTLOG

changes when hitted or something plox


//He tret el llegir enemics del readLVL, ho deixo escrit just in case
*/

scenePlayable::scenePlayable(Game *g, sf::RenderWindow *w, std::string next, std::string levelName, Player *player)
                                                    : Scene(g, w, sceneTypes::testScene, levelName)  {
    _view = _window->getDefaultView();
    initView(&_view, sf::Vector2i(1024,768));

    _player = player;
    _player->setPosition(_player->getRadius()*3,660);

    _next = next;
    _hatsOwned = 0;
    _shootTimer = 0;

    readLVL(levelName);
//    readEnemies(_hatsOwned);
    _levelName = levelName;

    for(int i = 0; i < 3; ++i) _hatshits[i] = 0;
    for(int i = 0; i < 3; ++i) _hats[i].setOrigin(_hats[i].getGlobalBounds().width/2,_hats[i].getGlobalBounds().height/2 );
    init();

    if(! _t.loadFromFile(std::string(TEXTURETPATH+std::string("hat0.png")))) std::cout << "unable to open hat0" << std::endl;
    _s.setTexture(_t);
    _s.setOrigin(_s.getGlobalBounds().width/2, _s.getGlobalBounds().height/2);

    _player->setHat(_hats[0]);
    _picking = true;
    _playing = false;
//    _playing = true;
//    _picking = false;

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
        //std::cout << "1__ " << _hatsOwned << std::endl;
        //_hatsOwned = line[0]-'0';
        _hatsOwned = lvl;
        //std::cout << "2__ " << _hatsOwned << std::endl;

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
                                case 'b':
                                _enemyPull.push(Enemy());
                                _enemyPull.back().setPosition(sf::Vector2f(_spawnPoint.x, _spawnPoint.y));
                                break;
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

void scenePlayable::init(sf::Vector2f aux){
    _timer = 0;
}

void scenePlayable::update(float deltaTime){

    _timer += deltaTime;
    _shootTimer += deltaTime;

    if(_picking){
        bg._doorOpenedL = true;
        bg._doorOpenedR = true;


        _hats[0].setPosition(300,150); _hats[1].setPosition(500,150); _hats[2].setPosition(700,150);

        //Update Bullets
        for(auto it = _bullets.begin(); it != _bullets.end();){
            it->update(deltaTime, &bg);
            bool kill = false;
            for(int i = 0; i < 3; ++i){
                if(i <= _hatsOwned && _hats[i].getGlobalBounds().contains(it->getPosition())){
                    ++_hatshits[i];
                    _hats[i].setScale(sf::Vector2f(_hats[i].getScale().x*2,_hats[i].getScale().y*2));
                    kill = true;
                }
            }
            if(kill) it = _bullets.erase(it);
            else ++it;
        }

        for(int i = 0; i < 3; ++i){
            _hats[i].rotate((std::sin(_timer))*20*deltaTime);
        }

        for(int i = 0; i < 3; ++i){
            if(_hatshits[i] > 1){
                if(_enemyPull.empty()) readEnemies(i);
                _player->setHat(_hats[i]);
                _playing = true;
                _picking = false;
            }
        }

    }
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
           if(_enemies.empty()) {
               _playing = false;
               _picking = true;
               for(int i = 0; i < 3; ++i) { _hatshits[i] = 0; _hats[i].setScale(sf::Vector2f(1.0,1.0));}
               for(int i = 0; i < 3; ++i) { _hatshits[i] = 0; _hats[i].setRotation(0);}
               //_hatsOwned = (_hatsOwned + 1);
               writteLVL(std::min(_hatsOwned,2));
           }
       }

       //Update Enemies
       for(auto it = _enemies.begin(); it != _enemies.end(); ++it){
           it->update(deltaTime, &bg);
       }

       //Update Bullets
       for(auto it = _bullets.begin(); it != _bullets.end(); ++it){
           it->update(deltaTime, &bg);
       }


       //erase dead bullets
       auto itb = _bullets.begin();
       for(itb; itb != _bullets.end();){
           if(! (*itb).isAlive()){
               itb = _bullets.erase(itb);
           }
           else ++itb;
       }

       //erase dead enemies
       auto ite = _enemies.begin();
       for(ite; ite != _enemies.end();){
           if(! (*ite).isAlive()){
               ite = _enemies.erase(ite);
           }
           else ++ite;
       }

       //colision between enemies and bullets
       ite = _enemies.begin();
       itb = _bullets.begin();
       for(ite; ite != _enemies.end();){

           if(ite->colides(_player) && ite->colisionable()){
               ite->hit();
           }
           else for(itb; itb != _bullets.end() && ite != _enemies.end();){

               //check enemy and bullet colision
               if(ite->colides(&(*itb))  && ite->colisionable()){
                   itb = _bullets.erase(itb);
                   ite->hit();
               }
               else ++itb;

           }

           if(ite != _enemies.end()) ++ite;

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

    if( InputManager::action(InputAction::shoot) > 0 && _shootTimer > constant::shootMaxTime){
        _shootTimer = 0;
        Bullet b;
        b.setPosition(_player->getPosition());
        b.setDestiny(sf::Vector2f(bg.getIntersection( sf::Vector2i(_player->getPosition()) ,sf::Vector2i(_window->mapPixelToCoords(sf::Mouse::getPosition((*_window)),_view)))));
        _bullets.push_back(b);
    }
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
        _hatsOwned = std::min(std::max(oldLVL,lvl+1),2);
        aux << std::min(std::max(oldLVL,lvl+1),2) << '\n';
        //if(oldLVL > _hatsOwned) _hatsOwned = oldLVL;
        //if(lvl > oldLVL) aux << lvl << '\n';
        //else aux << line << '\n';

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
    if(_picking){
        for(int i = 0; i < 3; ++i){
            if(i <= _hatsOwned ) target->draw(_hats[i]);
            else {
                _s.setPosition(300+200*i,150);
                target->draw(_s);
            }
        }
//        target->draw(_hats[0]);
//        target->draw(_hats[1]);
//        target->draw(_hats[2]);
    }
    _player->draw(target);
    for(auto it = _enemies.begin(); it != _enemies.end(); ++it){
        target->draw(*it);
    }
    for(auto it = _bullets.begin(); it != _bullets.end(); ++it){
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
            _hatsOwned = line[0]-'0';


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

/*
            if(line == "enemies"){

                std::getline (myfile,line);
                while(line[0] == '#') std::getline (myfile,line);

                while(line[0] != '$'){

                    if((line[0]-'0') == _hatsOwned){

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
*/
        }
        myfile.close();
    }
    else std::cout << "scenePlayable file not oppened" << std::endl;


}
