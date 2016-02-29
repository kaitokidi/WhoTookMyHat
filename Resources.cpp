#include "Resources.hpp"

//PLACE HERE THE RESOURCES YOU WANT TO LOAD

// sf::Texture        Resources::....
sf::Texture            Resources::key;
sf::Texture            Resources::eyes;
sf::Texture            Resources::chain;
sf::Texture            Resources::talkBox;
sf::Texture            Resources::doors_OX;
sf::Texture            Resources::doors_OO;
sf::Texture            Resources::doors_XX;

sf::Shader             Resources::cInvert;

sf::Font               Resources::pauseMenuFont;

std::vector<SpriteSheetDescription> Resources::descriptions;


void printError(std::string s){
    std::cout << "Resources:: Error loading... " << s << std::endl;
}

void Resources::load() {
    //LOAD THE INFORMATION IN THE VARIABLES
    //...loadFromFile(); or whatever
    if(! key.loadFromFile                    (TEXTURETPATH+std::string("key.png"))      ) printError("keyTex");
    if(! eyes.loadFromFile                   (TEXTURETPATH+std::string("eyes.png"))     ) printError("eyes");
    if(! chain.loadFromFile                  (TEXTURETPATH+std::string("hook.png"))    ) printError("chainTex");
    if(! talkBox.loadFromFile                (TEXTURETPATH+std::string("talkBox.png"))  ) printError("talkbTex");
    if(! doors_OX.loadFromFile               (TEXTURETPATH+std::string("doors_OX.png")) ) printError("doorOXTex");
    if(! doors_OO.loadFromFile               (TEXTURETPATH+std::string("doors_OO.png")) ) printError("doorOOTex");
    if(! doors_XX.loadFromFile               (TEXTURETPATH+std::string("doors_XX.png")) ) printError("doorXXTex");

   // descriptions = std::vector<SpriteSheetDescription>(spriteDescriptionsQtt);
   // descriptions[linkSpritesDescriptions]       = loadDescription("linkSheet");

    if (!cInvert.loadFromFile           (SHADERPATH+std::string("invert.frag"), sf::Shader::Fragment)) exit(EXIT_FAILURE);

    if (!pauseMenuFont.loadFromFile("Resources/Fonts/font.ttf")) exit(EXIT_FAILURE);

    std::cout << " Resources Loaded " << std::endl;
}


//ONLY USED IF USING DESCRIPTORS
SpriteSheetDescription Resources::loadDescription(std::string) {
/*    std::string filePath = TEXTURETPATH + fileName + TEXTUREDESCRIPTIONEXTENSION;
    SpriteSheetDescription ret;
    // leer el fichero
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cout << "Error opening file on resources loadDescription " << filePath << std::endl;
        exit(EXIT_FAILURE);
    }
    std::vector<std::pair<int, std::string> > v;
    int lineNum = 0;
    std::string line;
    while (getline(file,line)) {
        ++lineNum;
        for (int i = 0; i < int(line.size()-1); ++i) {
            if (line[i] == '/' && line[i+1] == '/') {
                line = line.substr(0,i);
                break;
            }
        }
        std::istringstream aux(line);
        std::string s;
        while(aux >> s) 
            v.push_back(std::make_pair(lineNum,s));
    }
    SpriteSheetDescription ssd;
    std::map<std::string, int> positions;
    for (int  i = 0; i < int(v.size()); ++i) {
        lineNum = v[i].first;
        std::string key = v[i].second;
        int descriptorPosition;
        if (positions.find(key) == positions.end()) {
            descriptorPosition = positions.size();
            positions.insert(std::make_pair(key,descriptorPosition));
            ssd.push_back(std::vector<sf::IntRect>());
        }
        else {
            descriptorPosition = positions[key];
        }
        //std::cout << "insertando la key " << key << " en la posicion " << descriptorPosition << std::endl;

        if (i+4 >= int(v.size()) || 
            !isInt(v[i+1].second) || 
            !isInt(v[i+2].second) || 
            !isInt(v[i+3].second) || 
            !isInt(v[i+4].second)) {
            std::cout << "Error in line " << lineNum << ": four integers are needed" << std::endl;
            exit(EXIT_FAILURE);
        }
        sf::IntRect intRect(myStoi(v[i+1].second),
            myStoi(v[i+2].second),
            myStoi(v[i+3].second),
            myStoi(v[i+4].second));
        ssd[descriptorPosition].push_back(intRect);
        i += 4;
    }

    return ssd;*/
}
