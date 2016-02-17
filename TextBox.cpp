#include "TextBox.hpp"
#include "Resources.hpp"

TextBox::TextBox(){

    lecturePointer = 0;

    clicked = false;
    is_clicked = false;
    textFinished = false;

    setPosition(0,0);
    text.setString("");

}

std::string TextBox::getFractionText(std::string text, int ini, int end){
    std::string ret = "";
    for(int i = ini; i < end; ++i){
        if(i >= int(text.size())) {
            textFinished = true;
            ret += " ";
        }
        else ret += text[i];
    }
    return ret;
}

bool TextBox::getTextFinished(){return textFinished;}

TextBox::TextBox(std::string myText, std::string texturePath, std::string fontPath, float sizeX, float sizeY): boxTexts(4, ""){

    totalText = myText;

    text.setString("OnCreationText");

    clicked = false;
    is_clicked = false;
    textFinished = false;

    if(!texture.loadFromFile(texturePath)) std::cerr << "Failed on load texture from " << texturePath << std::endl;
    else sprite.setTexture(texture);
    setSize(sizeX, sizeY);

    if(!font.loadFromFile(fontPath)){ std::cerr << "Can't find the font file" << std::endl; }
    else setFont(font);  
    setTextColor(sf::Color::Black);
    
}

void TextBox::setText(float charSize){

    sf::FloatRect totalSpace;
    totalSpace = sprite.getGlobalBounds();

    sf::Vector2f spaces( totalSpace.width/10, totalSpace.height/8);

    sf::IntRect box(totalSpace.left+spaces.x, totalSpace.top+spaces.y,
                    totalSpace.width-spaces.x, totalSpace.height-spaces.y);

    sf::Vector2f writted(box.left,box.top);

    int row = 0;
    sf::Text aux;
    aux.setCharacterSize(charSize);
    aux.setFont(Resources::pauseMenuFont);
    boxTexts = std::vector<std::string>();

    while(! textFinished &&  writted.y+charSize < box.top+box.height){

        float maxYsize = 1;
        writted.x = box.left;
        boxTexts.push_back("");

        while(! textFinished && writted.x+charSize < box.left+box.width){

            boxTexts[row] += (totalText[lecturePointer]);

            aux.setString(totalText[lecturePointer]);

            ++lecturePointer;
            if(lecturePointer > totalText.size()) textFinished = true;
            writted.x += aux.getGlobalBounds().width;
            if(aux.getGlobalBounds().height > maxYsize) maxYsize = aux.getGlobalBounds().height;

        }

        //remove and move the pointer to the last ' '
        int last = boxTexts[row].size()-1;
        while(! textFinished && boxTexts[row][last] != ' '){
            --last;
            --lecturePointer;
            boxTexts[row].pop_back();
            //if we are deletting the char which setted the size on max, it will not be recalculated, get reckt
        }

        ++row;
        writted.y += maxYsize;

    }

    //if(boxTexts.size() > 0) std::cout <<"first text "<< boxTexts[0] << std::endl;
}

void TextBox::setTextBestFit(std::string s = "Click", float charSize = 100){

    totalText = s;
    lecturePointer = 0;
    textFinished = false;
    text.setCharacterSize(charSize);

    setText(charSize);


}

std::string TextBox::getText(){ return text.getString();}

void TextBox::draw(sf::RenderTarget& w){

    w.draw(sprite);

    sf::FloatRect totalSpace;
    totalSpace = sprite.getGlobalBounds();
    sf::Vector2f spaces( totalSpace.width/10, totalSpace.height/8);
    float yPos = totalSpace.top;

    for(int i = 0; i < int(boxTexts.size()); ++i){

        text.setString(boxTexts[i]);
 
        text.setPosition(sprite.getPosition().x+spaces.x, yPos+spaces.y/2 );

        sf::Vector2f textSize(text.getLocalBounds().width, text.getLocalBounds().height);
        float oldSize = text.getCharacterSize();
        text.setCharacterSize(50);
        text.setScale(textSize.x/text.getLocalBounds().width, textSize.y/text.getLocalBounds().height);
        w.draw(text);
        text.setCharacterSize(oldSize);
        yPos += textSize.y;

    }

}

void TextBox::setOrigin(sf::Vector2f origin){
    sprite.setOrigin(origin);
}

void TextBox::setTexture(std::string name){
    float sizeX = getSize().x;
    float sizeY = getSize().y;
    if(!texture.loadFromFile(name)) std::cerr << " texture not loaded on setTexture" << std::endl;
    else sprite.setTexture(texture, true);
    setSize(sizeX, sizeY);
}
void TextBox::setTexture(sf::Texture tex){
    texture = tex;
    sprite.setTexture(texture, true);
}

//TODO change it so with a key it can be skiped and not with mouse and so.
void TextBox::handleEvent(sf::Event e){
    float delayx, delayy;
    delayx = sprite.getOrigin().x*sprite.getScale().x;
    delayy = sprite.getOrigin().y*sprite.getScale().y;
    sprite.move(-delayx, -delayy);
    if(e.type == sf::Event::MouseButtonPressed){


    }
    if(e.type == sf::Event::MouseButtonReleased){
        if (e.mouseButton.button == sf::Mouse::Left) {
            is_clicked = false;

        }
    }
    if(e.type == sf::Event::KeyPressed) {
        if(e.key.code == sf::Keyboard::Space) {
            clicked = true;
            is_clicked = true;
        }
    }
    if(e.type == sf::Event::KeyReleased) {
        if(e.key.code == sf::Keyboard::Space && !textFinished) {
            is_clicked = false;
            setText(getCharacterSize());
        }
    }
    sprite.move(delayx, delayy);
}


void TextBox::setTextColor(sf::Color c){text.setColor(c); }
sf::Color TextBox::getTextColor(){ return text.getColor();}

void TextBox::setCharacterSize(int u){ text.setCharacterSize(u); }
int TextBox::getCharacterSize(){ return text.getCharacterSize(); }

void TextBox::setFont(sf::Font f){ font = f; text.setFont(font); }

sf::Vector2f TextBox::getPosition(){ return sprite.getPosition(); }
void TextBox::setPosition(float x, float y){ setPosition(sf::Vector2f(x, y)); }
void TextBox::setPosition(sf::Vector2f position){
    sprite.setPosition(position);
    text.setPosition(position.x - (sprite.getGlobalBounds().width * (sprite.getOrigin().x/sprite.getLocalBounds().width) ) +
                     sprite.getGlobalBounds().width/2 -
                     text.getGlobalBounds().width/2,
        position.y - (sprite.getGlobalBounds().height * (sprite.getOrigin().y/sprite.getLocalBounds().height) ) + sprite.getGlobalBounds().height/2 - (text.getGlobalBounds().height/2));
}


sf::Vector2f TextBox::getSize(){ return sf::Vector2f(sprite.getGlobalBounds().width,sprite.getGlobalBounds().height); }

bool TextBox::hasBeenClicked(){
    bool r = clicked;
    if(clicked) clicked = false;
    return r;
}

void TextBox::setSize(float x, float y){ setSize(sf::Vector2f(x,y)); }
void TextBox::setSize(sf::Vector2f size){
    //std::cout << "setSize" << std::endl;
    sprite.setScale(size.x/sprite.getLocalBounds().width, size.y/sprite.getLocalBounds().height);
}
