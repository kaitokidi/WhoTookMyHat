#include "Resources.hpp"
#include "ScenePlayable.hpp"

scenePlayable::scenePlayable(Game *g, sf::RenderWindow *w, std::string next, std::string levelName, Player *player)
                                                    : Scene(g, w, sceneTypes::testScene, levelName)  {
    _view = _window->getDefaultView();
    initView(&_view, sf::Vector2i(1024,768));

    _player = player;
    _player->setHookPos(100,100);
    _player->setPosition(200,200);
    _next = next;
    readLVL(levelName);

    init();
}

scenePlayable::~scenePlayable(){}

void scenePlayable::init(sf::Vector2f aux){
    _timer = 0;
}

void scenePlayable::update(float deltaTime){
    _timer += deltaTime;
    _player->update(deltaTime);
}

void scenePlayable::processInput(){
    sf::Event event;
    while(_window->pollEvent(event)){
        if (event.type == sf::Event::Closed) {_window->close(); exit(0);}
    }
    InputManager::update();
}

void scenePlayable::render(sf::RenderTarget *target){
    bg.draw(target);
    _player->draw(target);
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
            _hatsOwned = myStoi(line);

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
        }
        myfile.close();
    }
    else std::cout << "scenePlayable file not oppened" << std::endl;


}
