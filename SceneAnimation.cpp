#include "SceneAnimation.hpp"
#include "TextBoxManager.hpp"

#define newLine readLine(myfile,line);
#define last size()-1


Element::Element(){
    dead = false;
    visible = true;
    myTimer = 0;
}

bool Element::getVisible() const { return visible; }
void Element::setVisible(bool value) { visible = value; }



SceneAnimation::SceneAnimation(Game *g, sf::RenderWindow *w, std::string previous, std::string levelName, std::string next)
    : Scene(g, w, sceneTypes::testScene, levelName)  {
    _next = next;
    _prev = previous;
    _levelName = levelName;
    //init();
}

void SceneAnimation::init(sf::Vector2f aux){
    aux = aux; //per treure el warning de unused variable -_-
    _timer = 0;
    _view = _window->getDefaultView();
    initView(&_view, sf::Vector2i(1024,768));
    readLVL(_levelName);
}

void SceneAnimation::resizing() { }

void SceneAnimation::processInput() {
    sf::Event event;
    while(_window->pollEvent(event)){
        if (event.type == sf::Event::Closed) {_window->close(); exit(0);}
        if (event.type == sf::Event::KeyReleased) changeScene(_next);//{_window->close(); exit(0);}
    }
    InputManager::update();
}

void SceneAnimation::update(float deltaTime){
    while(!_waiting && _orders.size() > 0){
        log("_numofOrders ", _orders.size());
        static std::string order = _orders[0][0];
        static std::string name = _orders[0][1];
        static std::string time = _orders[0][_orders[0].last];
        if(name == "NONE" && order == "wait"){
            _waiting = true;
            _timer = myStoi(time);
        }else {
            for(size_t i = 0; i < _names.size(); ++i){
                log("names size", _names.size());
                if(_names[i] == name){
                    if(_elements[i].currentAction.size() > 0){
                        log(name, "queueaction", _elements[i].currentAction.size());
                        _elements[i].actionQueue.push(_orders[0]);
                    }else {
                        log(name, "currentActiohn", _orders[0][0]);
                        _elements[i].currentAction = _orders[0];
                        _elements[i].myTimer = myStoi(time);
                    }
                }
            }
        }
        _orders.erase(_orders.begin());
        log("elements actions on finishe the oop",_elements[0].currentAction.size());
    }

    if(_waiting) {
        _timer -= deltaTime;
        if(_timer <= 0) _waiting = false;
    }

    auto nameit = _names.begin();
    for (auto it = _elements.begin(); it != _elements.end();){
        if(it->currentAction.size() > 0){
            log("dooing", it->currentAction[0]);

            it->myTimer -= deltaTime;

            if(it->currentAction[0] == "move"){
                float diffx = myStoi(it->currentAction[2]) - it->getPosition().x;
                float diffy = myStoi(it->currentAction[3]) - it->getPosition().y;
                log("moving",diffx/(deltaTime*it->myTimer), diffy/(deltaTime*it->myTimer));
                it->move(diffx/(it->myTimer/deltaTime), diffy/(it->myTimer/deltaTime));
            }
            else if (it->currentAction[0] == "die"){
                if(it->myTimer <= 0) it->dead = true;
            }

            if(it->myTimer <= 0){
                if(it->actionQueue.size() > 0){
                    it->currentAction = it->actionQueue.front();
                    it->actionQueue.pop();
                    it->myTimer = myStoi(it->currentAction[it->currentAction.last]);
                }
            }

        }

        if(it->dead){
            log("element dead");
            it = _elements.erase(it);
            nameit = _names.erase(nameit);
        }else {
            ++it;
            ++nameit;
        }
    }
    if(_orders.size() == 0 && !_waiting && _elements.size() == 0) changeScene(_next);
}


void SceneAnimation::render(sf::RenderTarget *target) {
    for (auto it = _elements.begin(); it != _elements.end();++it){
        log("renderino");
        target->draw(*it);
    }
}

void readLine(std::ifstream& myfile, std::string& line){
    std::getline (myfile,line);
    while(line.size() == 0 || line[0] == '#') std::getline(myfile,line);
}
void SceneAnimation::readLVL(std::string levelName){
    log("MOOOLT BE");
    std::string line;
    std::ifstream myfile (LVLDESCIPTPATH+levelName+".txt");

    if (myfile.is_open()) {

        newLine
        while(line == "Sprite"){

            newLine
            _names.push_back(line);

            newLine
            sf::Texture t;
            _textures.push_back(t);
            Element e;
            _elements.push_back(e);
            if(! _textures[_textures.last].loadFromFile(TEXTURETPATH+line) ) log("OnSceneAnimation ",line," not loaded");
            else _elements[_elements.last].setTexture(_textures[_textures.last]);

            newLine
            _elements[_elements.last].setVisible(line == "hide");

            newLine
        }

        while(line[0] != '$'){
//            _orders.push_back(std::vector<std::string>());
//            _orders[0].push_back(line);

            if(line == "move"){
                _orders.push_back(std::vector<std::string>());
                _orders[_orders.last].push_back(line);
                newLine
                _orders[_orders.last].push_back(line); //name
                newLine
                _orders[_orders.last].push_back(line); //posx
                newLine
                _orders[_orders.last].push_back(line); //posy
                newLine
                _orders[_orders.last].push_back(line); //time
            }
            else if(line == "show"){
                _orders.push_back(std::vector<std::string>());
                _orders[_orders.last].push_back(line);
                newLine
                _orders[_orders.last].push_back(line); //name
                _orders[_orders.last].push_back("0");  //no time
            }
            else if(line == "hide"){
                _orders.push_back(std::vector<std::string>());
                _orders[_orders.last].push_back(line);
                newLine
                _orders[_orders.last].push_back(line); //name
                _orders[_orders.last].push_back("0");  //no time
            }
            else if(line == "wait"){
                _orders.push_back(std::vector<std::string>());
                _orders[_orders.last].push_back(line);
                _orders[_orders.last].push_back("NONE");//noone
                newLine
                _orders[_orders.last].push_back(line); //time
            }
            else if(line == "rotate"){
                _orders.push_back(std::vector<std::string>());
                _orders[_orders.last].push_back(line);
                newLine
                _orders[_orders.last].push_back(line); //name
                newLine
                _orders[_orders.last].push_back(line); //angle
                newLine
                _orders[_orders.last].push_back(line); //right/left
                newLine
                _orders[_orders.last].push_back(line); //time
            }
            else if(line == "scale"){
                _orders.push_back(std::vector<std::string>());
                _orders[_orders.last].push_back(line);
                newLine
                _orders[_orders.last].push_back(line); //name
                newLine
                _orders[_orders.last].push_back(line); //factor
                newLine
                _orders[_orders.last].push_back(line); //time
            }
            else if(line == "fade"){
                _orders.push_back(std::vector<std::string>());
                _orders[_orders.last].push_back(line);
                newLine
                _orders[_orders.last].push_back(line); //name
                newLine
                _orders[_orders.last].push_back(line); //time
            }
            else if(line == "die"){
                _orders.push_back(std::vector<std::string>());
                _orders[_orders.last].push_back(line);
                newLine
                _orders[_orders.last].push_back(line); //name
                newLine
                _orders[_orders.last].push_back(line); //time
            }

            newLine

        }
        myfile.close();
    }
    else std::cout << "SceneAnimation " << levelName << " file not oppened" << std::endl;

}
