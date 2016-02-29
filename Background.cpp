#include "Background.hpp"

Background::Background() {
}

Background::Background(std::string lvlDesc) {
    init(lvlDesc);
}

Background::~Background() {

}

void Background::init(std::string lvlDesc) {
    readLevel(lvlDesc);
    _doors.setPosition(0,0);
    _background.setPosition(0,0);
    _background.setTexture(_bTexture);
}

bool Background::colision(float x, float y){
    return colision(sf::Vector2f(x,y));
}

bool Background::colision(sf::Vector2f pos) {
    for(int i = 0; i < _boundaries.size(); ++i){
        if(_boundaries[i].contains(pos)) return true;
    }
    return false;
}

void Background::draw(sf::RenderTarget *target){
    target->draw(_background);

    if(_doorOpenedL && _doorOpenedR){
        _doors.setTexture(Resources::doors_OO);
    }
    else if( _doorOpenedL && ! _doorOpenedR){
        _doors.setTexture(Resources::doors_OX);
    }
    else if(! _doorOpenedL && ! _doorOpenedR){
        _doors.setTexture(Resources::doors_XX);
    }
    target->draw(_doors);

 /* //DEBUG DRAW RED RECTANGLES
    for(int i = 0; i < _boundaries.size(); ++i){
        sf::RectangleShape RS(sf::Vector2f(_boundaries[i].width,_boundaries[i].height));
        RS.setPosition(sf::Vector2f(_boundaries[i].left,_boundaries[i].top));
        RS.setFillColor(sf::Color::Red);
        target->draw(RS);
    }
    */
}

bool Background::circleColision(sf::Vector2i pos, float rad) {
    for(int i = 0; i < _boundaries.size(); ++i){

        if(    _boundaries[i].contains(sf::Vector2f(pos.x+rad, pos.y))
            || _boundaries[i].contains(sf::Vector2f(pos.x-rad, pos.y))
            || _boundaries[i].contains(sf::Vector2f(pos.x, pos.y+rad))
            || _boundaries[i].contains(sf::Vector2f(pos.x, pos.y-rad))
                                                                    ){
            return true;
        }
        else if(       getModule(sf::Vector2f(pos), sf::Vector2f(_boundaries[i].left,_boundaries[i].top)) < rad
                    || getModule(sf::Vector2f(pos), sf::Vector2f(_boundaries[i].left+_boundaries[i].width,_boundaries[i].top)) < rad
                    || getModule(sf::Vector2f(pos), sf::Vector2f(_boundaries[i].left,_boundaries[i].top+_boundaries[i].height)) < rad
                    || getModule(sf::Vector2f(pos), sf::Vector2f(_boundaries[i].left+_boundaries[i].width,_boundaries[i].top+_boundaries[i].height)) < rad
                       ){
            return true;
        }
        return false;
    }
}

sf::Vector2i Background::getIntersection(sf::Vector2i mousePos){

    sf::Vector2i ret(1,1);

    for(int i = 0; i < _boundaries.size(); ++i){
        if(_boundaries[i].contains(sf::Vector2f(mousePos.x,mousePos.y))){
            //ret.x = _boundaries[i].left;
            //ret.y = _boundaries[i].top;
            ret.x = mousePos.x;
            ret.y = mousePos.y;
        }
    }
    return ret;

}



void Background::readLevel(std::string lvlDesc) {
    std::string line;
    std::ifstream myfile (LVLDESCIPTPATH+lvlDesc+".txt");

    if (myfile.is_open()) {

        std::getline (myfile,line);
        while(line[0] == '#') std::getline (myfile,line);
        if(! _bTexture.loadFromFile(TEXTURETPATH+line) ) std::cout << "error on loading bacground texture" << std::endl;

        std::getline (myfile,line);
        while (line[0] != '$') {
            if(line[0] != '#'){
                if(line == "doors"){
                    std::getline (myfile,line);
                    while(line[0] == '#') std::getline (myfile,line);
                    if(line == "OO"){
                        _doorOpenedL = _doorOpenedR = true;
                    }
                    else if(line == "OX"){
                        _doorOpenedL = true;
                        _doorOpenedR = false;
                    }
                    else if(line == "XX"){
                        _doorOpenedL = _doorOpenedR = false;
                    }

                }

                if(line == "boundaries"){
                    //log("boundaries");

                    std::getline (myfile,line);
                    while(line[0] == '#') std::getline (myfile,line);

                    while(line == "next"){

                        sf::FloatRect fr;
                        std::getline (myfile,line);
                        while(line[0] == '#') std::getline (myfile,line);
                        fr.left = myStoi(line);
                        std::getline (myfile,line);
                        while(line[0] == '#') std::getline (myfile,line);
                        fr.top = myStoi(line);
                        std::getline (myfile,line);
                        while(line[0] == '#') std::getline (myfile,line);
                        fr.width = myStoi(line);
                        std::getline (myfile,line);
                        while(line[0] == '#') std::getline (myfile,line);
                        fr.height = myStoi(line);

                        _boundaries.push_back(fr);

                        //read next that would be next if ther are more or end (or something else ) if it is done
                        std::getline (myfile,line);
                        while(line[0] == '#') std::getline (myfile,line);

                    }

                }
            }
            std::getline (myfile,line);
            while(line[0] == '#') std::getline (myfile,line);
        }
        //std::cout << "bg finishes with line  " << line << std::endl;
        myfile.close();
    } else std::cout << "not oppened backgroound file " << lvlDesc << std::endl;
}
