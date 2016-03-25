#include "TextBoxManager.hpp"

TextBox                             TextBoxManager::_textBox;
std::map<std::string, std::string>  TextBoxManager::texts;

void TextBoxManager::loadTexts(std::string fileName){

    std::string filePath = TEXTPATH + fileName;
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cout << "Error opening fileof texts loadtexts TextBoxManager " << filePath << std::endl;
        exit(EXIT_FAILURE);
    }
    bool ended = false;
    std::string line, line2, Hashtack;
    while (getline(file,line) && (!ended)) {

        if (line == "END"){
            ended = true;
        }else {
            getline(file, line2);
            getline(file, Hashtack);
            texts[line] = line2;
        }

    }
}

void TextBoxManager::load() {

    texts["none"] = " ";
    texts["default"] = "Who Took My Hat!?!";
    texts["penguins"] = "Penguin penguin penguin niugnep There are believed to be 17 species of penguins.  This includes the Aptendytes (Great penguins), Pygoscelis (Brush-Tailed penguins), Eudyptula (Little penguins), Megadyptes (Only 1 kind of Megadypte penguin survives), and Eudyptes (Crested penguins) Nobody really knows the root of the word penguin. The word has no English, French, Spanish or other romantic language roots. As there are no penguins in the Northern Hemisphere, it wasn’t until European explorers discovered them in the South that the world first appeared. It’s first referenced in English and Dutch as pen gwyn which in Welsh means white head.Through evolution, the penguin’s wings have evolved into flippers which are more adapted to aquatic life. Most penguins can move at a total speed of up to 6 to 12 km/h (3.7 to 7.5 mph) while underwater, but the fastest penguin (The Gentoo Penguin) can achieve a remarkable top speeds of 36 Km/h (22 mph). Emperor penguins have also been known to dive as deep as 565 meters (1,870 feet) for 22 minutes – an absolutely incredible feat for a diving bird. Most penguins species however only stay underwater for around 4-5 minutes at a time, as most of their food can be gathered from very low depths.";
    //TextBoxManager::loadTexts("TextsFile.txt");

    _textBox.setTexture(Resources::talkBox);
    _textBox.setTextColor(sf::Color::Black);
    _textBox.setFont(Resources::pauseMenuFont);
    setText("default",30);

}

void TextBoxManager::setTexture(int value){
    switch (value){
    case(0):
        _textBox.setTexture(Resources::talkBox);
        break;
    default:
        _textBox.setTexture(Resources::talkBox);
        break;
    }
}
void TextBoxManager::setSize(float sizeX, float sizeY){
    _textBox.setSize(sizeX, sizeY);
}

void TextBoxManager::processEvent(sf::Event event){
    _textBox.handleEvent(event);
}

void TextBoxManager::setText(std::string name){
    _textBox.setTextBestFit(texts[name],30);
}

void TextBoxManager::setText(std::string name, int charSize = 100){
    _textBox.setTextBestFit(texts[name], charSize);
}

void TextBoxManager::drawText(sf::RenderTarget *window){
    _textBox.draw(*window);
}

void TextBoxManager::drawText(sf::RenderTarget *window, float posX, float posY){
    _textBox.setPosition(posX, posY);
    _textBox.draw(*window);
}

bool TextBoxManager::getTextFinished(){
    return _textBox.getTextFinished();
}

sf::Vector2f TextBoxManager::getSize(){
    return _textBox.getSize();
}




