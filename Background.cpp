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
    doors.setPosition(0,0);
    background.setPosition(0,0);
    background.setTexture(bTexture);
}

void Background::draw(sf::RenderTarget *target){
    target->draw(background);

    if(doorOpenedL && doorOpenedR){
        doors.setTexture(Resources::doors_OO);
    }
    else if( doorOpenedL && ! doorOpenedR){
        doors.setTexture(Resources::doors_OX);
    }
    else if(! doorOpenedL && ! doorOpenedR){
        doors.setTexture(Resources::doors_XX);
    }
    target->draw(doors);

}



void Background::readLevel(std::string lvlDesc) {
    std::string line;
    std::ifstream myfile (LVLDESCIPTPATH+lvlDesc+".txt");

    if (myfile.is_open()) {

        std::getline (myfile,line);
        while(line[0] == '#') std::getline (myfile,line);
        if(! bTexture.loadFromFile(TEXTURETPATH+line) ) std::cout << "error on loading bacground texture" << std::endl;

        std::getline (myfile,line);
        while (line[0] != '$') {
            if(line[0] != '#'){
                if(line == "doors"){
                    std::getline (myfile,line);
                    while(line[0] == '#') std::getline (myfile,line);
                    if(line == "OO"){
                        doorOpenedL = doorOpenedR = true;
                    }
                    else if(line == "OX"){
                        doorOpenedL = true;
                        doorOpenedR = false;
                    }
                    else if(line == "XX"){
                        doorOpenedL = doorOpenedR = false;
                    }
                }

                if(line == "boundaries"){

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

                        boundaries.push_back(fr);

                        //read next that would be next if ther are more or end (or something else ) if it is done
                        std::getline (myfile,line);
                        while(line[0] == '#') std::getline (myfile,line);

                    }

                }
            }
            std::getline (myfile,line);
            while(line[0] == '#') std::getline (myfile,line);
        }
        myfile.close();
    } else std::cout << "not oppened backgroound file " << lvlDesc << std::endl;
}
