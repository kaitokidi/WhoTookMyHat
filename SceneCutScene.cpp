#include "SceneCutScene.hpp"
#include "TextBoxManager.hpp"

SceneCutScene::SceneCutScene(Game *g, sf::RenderWindow *w, std::string previous, std::string levelName, std::string next, Player *player)
    : Scene(g, w, sceneTypes::testScene, levelName)  {

    _next = next;
    _player = player;
    _prev = previous;
    _levelName = levelName;
    init();

    _updatedYet = false;

    bg._doorOpenedL = true;
    bg._doorOpenedR = true;

    _text.setFont(Resources::pauseMenuFont);
    _text.setCharacterSize(40);
    _text.setPosition(150,200);
    _text.setColor(sf::Color(214,214,198));

    _thought.setFont(Resources::pauseMenuFont);
    _thought.setCharacterSize(20);
    _thought.setPosition(100,710);

}

void SceneCutScene::init(sf::Vector2f aux){
    aux = aux; //per treure el warning de unused variable -_-
    _timer = 0;
    _view = _window->getDefaultView();
    initView(&_view, sf::Vector2i(1024,768));
   _shootTimer = 0;

   _textActive = false;

}

void SceneCutScene::resizing() { }

void SceneCutScene::processInput() {
    sf::Event event;
    while(_window->pollEvent(event)){
        if (event.type == sf::Event::Closed) {_window->close(); exit(0);}
        switch (event.type){
            case  sf::Event::KeyPressed:
                //Close key
                if (event.key.code == sf::Keyboard::Escape) {
                    _window->close(); exit(0);
                }
                if (event.key.code == sf::Keyboard::T) {
                    _textActive = !_textActive;
                }
                if(event.key.code == sf::Keyboard::N && sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)){
                    changeScene(_next);
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

std::string gettextqtty(int ppos, int max, std::string s){
    float rate = float(ppos)/float(max);
    size_t value = s.size()*rate;
    std::string aux;
    for(size_t i = 0; i < value && i < s.size(); ++i) aux.push_back(s[i]);
    return aux;
}

void SceneCutScene::update(float deltaTime){

    //fix for the joystick if it is plugged
    if(sf::Joystick::isConnected(0) &&
            sf::Joystick::hasAxis(0, sf::Joystick::U)&&
            sf::Joystick::hasAxis(0, sf::Joystick::V)){
/*        if( sf::Joystick::hasAxis(0, sf::Joystick::R)) //Right trigger
        if( sf::Joystick::hasAxis(0, sf::Joystick::Z)) //left trigger*/

        float dirx = sf::Joystick::getAxisPosition(0, sf::Joystick::U);
        float diry =  sf::Joystick::getAxisPosition(0, sf::Joystick::V);

        if(dirx >= 50 || diry >= 50 || dirx <= -50 || diry <= -50) {
            float angle = getAngle(sf::Vector2f(dirx,0), sf::Vector2f(0,diry));
            angle = angle*M_PI/180;
            sf::Vector2f playerPos = _player->getPosition();
            sf::Mouse::setPosition(sf::Vector2i(
                                       playerPos.x+170 - (std::cos(angle))*_player->getRadius()*10,
                                       playerPos.y + (std::sin(angle))*_player->getRadius()*10));
        }
    }

    if(!_updatedYet) {
        readLVL(_levelName);
        _updatedYet = true;
    }

    _timer += deltaTime;
    _shootTimer += deltaTime;

    //Movement between scenes by sides
    //left        75.2164 , 666.996
    //right       948.689 , 666.996
    if(_player->getPosition().y > 666){//està a terra
        if(bg._doorOpenedR && _player->getPosition().x > 948) {
            if (_player->getPosition().x < 1024+_player->getRadius()+50 ) {
                _player->moveOut(90*deltaTime);
            }
            else {
                _player->setPosition(76, 666);
                changeScene(_next);//move to next LVL
            }
        }
        else if(bg._doorOpenedL && _player->getPosition().x < 76) {
            if(_player->getPosition().x > 0-_player->getRadius()-50){
                _player->moveOut(-90*deltaTime);
            }else {
                _player->setPosition(947,666);
                changeScene(_prev);
            }
        }
        else _player->update(deltaTime, sf::Vector2i(_window->mapPixelToCoords(sf::Mouse::getPosition((*_window)),_view)), &bg);
    } else   _player->update(deltaTime, sf::Vector2i(_window->mapPixelToCoords(sf::Mouse::getPosition((*_window)),_view)), &bg);

   //Update Bullets
   for(auto it = _bullets.begin(); it != _bullets.end(); ++it){
       it->update(deltaTime, &bg);
   }

   //erase dead bullets
   auto itb = _bullets.begin();
   for(;itb != _bullets.end();){
       if(! (*itb).isAlive()){
           itb = _bullets.erase(itb);
       }
       else ++itb;
   }

   std::string actualText = gettextqtty(_player->getPosition().x, 800, _totalThought);
   _thought.setString(actualText);

}


void SceneCutScene::render(sf::RenderTarget *target) {
    bg.draw(target);

    _player->draw(target);

    for(unsigned int i = 0; i < _texts.size(); ++i){
        _text.setString(_texts[i]);

        //TextOutline
        _text.setColor(sf::Color(30,30,30)); int offset = 5;
        _text.setPosition(int ( (1024)/2 - (_text.getGlobalBounds().width/2))+offset, 150+i*_text.getCharacterSize()*1.5);
        target->draw(_text);
        _text.setPosition(int ( (1024)/2 - (_text.getGlobalBounds().width/2))-offset, 150+i*_text.getCharacterSize()*1.5);
        target->draw(_text);
        _text.setPosition(int ( (1024)/2 - (_text.getGlobalBounds().width/2)), 150+i*_text.getCharacterSize()*1.5+offset);
        target->draw(_text);
        _text.setPosition(int ( (1024)/2 - (_text.getGlobalBounds().width/2)), 150+i*_text.getCharacterSize()*1.5-offset);
        target->draw(_text);

        //TEXT
        _text.setColor(sf::Color(214,214,198));
        _text.setPosition(int ( (1024)/2 - (_text.getGlobalBounds().width/2)), 150+i*_text.getCharacterSize()*1.5);
        target->draw(_text);
    }

    for(auto it = _bullets.begin(); it != _bullets.end(); ++it){
        target->draw(*it);
    }

    //if(_textActive) TextBoxManager::drawText(target, _player->getPosition().x - TextBoxManager::getSize().x/2, _player->getPosition().y - 100);
    //target->draw(_thought);
}

void SceneCutScene::readLVL(std::string levelName){

    std::string line;
    std::ifstream myfile (LVLDESCIPTPATH+levelName+".txt");

    /*
    std::ifstream mf (OPTIONSPATH+std::string("LANGUAGE.txt"));
    if(mf.is_open()){
        std::getline(mf, LANG);
    }else log("Error on languageFile -> SceneCutScene readLVL");
    */
    LANG = LANGUAGE;
    if (myfile.is_open()) {

        std::getline (myfile,line);
        while(line[0] == '#') std::getline (myfile,line);
        bg.init(line);

        std::getline (myfile,line);
        while(line[0] == '#') std::getline (myfile,line);
        _totalThought = TextBoxManager::getText(std::string(line+LANG));

        while (line[0] != '$') {

            std::getline (myfile,line);
            while(line[0] == '#') std::getline (myfile,line);

            //GET LANGUAGE TODO
            if(line == LANG){

                std::getline (myfile,line);
                while(line[0] == '#') std::getline (myfile,line);

                while(line != "OK"){

                    _texts.push_back(line);
                    do std::getline (myfile,line); while(line[0] == '#');
                }
            }
        }
    myfile.close();

    } else std::cout << "sceneCutScene " << levelName << " file not oppened" << std::endl;

}

