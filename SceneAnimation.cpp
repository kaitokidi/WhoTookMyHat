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
        std::string order = _orders[0][0];
        std::string name = _orders[0][1];
        std::string time = _orders[0][_orders[0].last];
        if(name == "NONE" && order == "wait"){
            _waiting = true;
            _timer = myStoi(time);
        }else {
            for(size_t i = 0; i < _names.size(); ++i){
                if(_names[i] == name){
                    //log(name,"----->",order);
                    if(_elements[i]->currentAction.size() > 0){
                        _elements[i]->actionQueue.push(_orders[0]);
                    }else {
                        _elements[i]->currentAction = _orders[0];
                        _elements[i]->myTimer = myStof(time);
                    }
                }
            }
            //log("end loop");
        }
        _orders.erase(_orders.begin());
    }

    if(_waiting) {
        _timer -= deltaTime;
        if(_timer <= 0) _waiting = false;
    }

    auto nameit = _names.begin();
    for (auto it = _elements.begin(); it != _elements.end();){
        if((*it)->currentAction.size() > 0){

            (*it)->myTimer -= deltaTime;

            if((*it)->currentAction[0] == "move"){
                float diffx = myStof((*it)->currentAction[2]) - (*it)->getPosition().x;
                float diffy = myStof((*it)->currentAction[3]) - (*it)->getPosition().y;
                (*it)->move(diffx/((*it)->myTimer/deltaTime), diffy/((*it)->myTimer/deltaTime));
            }
            else if ((*it)->currentAction[0] == "die"){
                if((*it)->myTimer <= 0) (*it)->dead = true;
            }
            else if ((*it)->currentAction[0] == "hide"){
                (*it)->visible = false;
            }
            else if ((*it)->currentAction[0] == "show"){
                (*it)->visible = true;
            }

            if((*it)->myTimer <= 0){
                if((*it)->actionQueue.size() > 0){
                    (*it)->currentAction = (*it)->actionQueue.front();
                    (*it)->actionQueue.pop();
                    (*it)->myTimer = myStof((*it)->currentAction[(*it)->currentAction.last]);
                }
            }
        }

        if((*it)->dead){
            delete(*it);
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
    //int i = 0;
    for (auto it = _elements.begin(); it != _elements.end();++it){
        if((*it)->visible) {
            //log("let's draw : ", _names[i]);
            target->draw(*(*it));
        } //else log("let's NOT draw ; ", _names[i]);
        //++i;
    }
}

void readLine(std::ifstream& myfile, std::string& line){
    std::getline (myfile,line);
    while(line.size() == 0 || line[0] == '#') std::getline(myfile,line);
}
void SceneAnimation::readLVL(std::string levelName){
    std::string line;
    std::ifstream myfile (LVLDESCIPTPATH+levelName+".txt");

    if (myfile.is_open()) {

        newLine
        while(line == "Sprite"){

            newLine
            _names.push_back(line);

            newLine
            //log("sprite -> ", line);
            _textures.push_back(new sf::Texture());
            _elements.push_back(new Element());
            //log("-");
            //log(_textures.last, &_textures[_textures.last]);
            //log(_elements.last, &_elements[_elements.last]);
            //log("__");
            if(! _textures[_textures.last]->loadFromFile(TEXTURETPATH+line) ) log("OnSceneAnimation ",line," not loaded");
            else _elements[_elements.last]->setTexture(*_textures[_textures.last], true);

            newLine
            _elements[_elements.last]->setVisible(line != "hide");

            newLine
        }

        while(line[0] != '$'){
            //log("action -> ", line);
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
