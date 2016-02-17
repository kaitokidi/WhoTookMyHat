#include "Effect.hpp"

Effect::Effect() {
    activated = true;
    automatic = true;
    timeCounter = 0;
    actualAnimation = 0;
    timeBetweenAnimations = 1;
}

Effect::~Effect() { }

int Effect::loadAnimation(std::string name, int qtty, std::string ext) {
    animation.clear();
    int errorPos = -1;
    for(int i = 0; i < qtty; ++i){
        std::stringstream s;
        s << name << i;
        std::string path = s.str();
        if(!loadFrame(path+"."+ext)) return errorPos = i;
    }
    return errorPos;//return -1;
}


bool Effect::loadAnimation(std::vector<sf::Texture>& vector) {
    animation.clear();
    animation = vector;
    return true;
}

bool Effect::loadHorizontalSpriteSheet(std::string name, float qtty){
    sf::Image spriteSheetImage;
    if(! spriteSheetImage.loadFromFile(name)) return false;
    else {
        float height = spriteSheetImage.getSize().y;
        float width  = spriteSheetImage.getSize().x/qtty;
        sf::Texture auxText;
        for(int i = 0; i < qtty; ++i){
            if(i*width > spriteSheetImage.getSize().x) return false;
            auxText.loadFromImage(spriteSheetImage, sf::IntRect(i*width,0,width, height));
            animation.push_back(auxText);
        }
    }
    return true;
}

bool Effect::loadHorizontalSpriteSheet(sf::Image image, float qtty){
    float height = image.getSize().y;
    float width  = image.getSize().x/qtty;
    sf::Texture auxText;
    for(int i = 0; i < qtty; ++i){
        if(i*width > image.getSize().x) return false;
        auxText.loadFromImage(image, sf::IntRect(i*width,0,width, height));
        animation.push_back(auxText);
    }
    return true;
}

bool Effect::loadVerticalSpriteSheet(std::string name,float qtty){
    sf::Image spriteSheetImage;
    if(! spriteSheetImage.loadFromFile(name)) return false;
    else {
        float width = spriteSheetImage.getSize().x;
        float height = spriteSheetImage.getSize().y/qtty;
        sf::Texture auxText;
        for(int i = 0; i < qtty; ++i){
            if(i*height > spriteSheetImage.getSize().y) return false;
            auxText.loadFromImage(spriteSheetImage, sf::IntRect(0,i*height,width, height));
            animation.push_back(auxText);
        }
    }
    return true;
}
bool Effect::loadVerticalSpriteSheet(sf::Image image,float qtty){

    float width = image.getSize().x;
    float height = image.getSize().y/qtty;
    sf::Texture auxText;
    for(int i = 0; i < qtty; ++i){
        if(i*height > image.getSize().y) return false;
        auxText.loadFromImage(image, sf::IntRect(0,i*height,width, height));
        animation.push_back(auxText);
    }
    return true;
}

bool Effect::loadSpriteSheet(std::string name, float rows, float columns, int lastRowQtty){
    int lastRow = lastRowQtty;
    if(lastRowQtty < 0) lastRow = columns;

    sf::Image spriteSheetImage;
    if(! spriteSheetImage.loadFromFile(name)) return false;
    else {
        float width = spriteSheetImage.getSize().x/columns;
        float height = spriteSheetImage.getSize().y/rows;
        sf::Texture auxText;
        int qttyColumns = columns;
        for(int k = 0; k < rows; ++k){
            if(k*height > spriteSheetImage.getSize().y) return false;
            if(k == rows -1) qttyColumns = lastRow;
            for(int i = 0; i < qttyColumns; ++i){
                if(i*width > spriteSheetImage.getSize().x) return false;
                auxText.loadFromImage(spriteSheetImage, sf::IntRect(i*width,k*height,width, height));
                animation.push_back(auxText);
            }
        }
    }
    return true;
}

bool Effect::loadSpriteSheet(sf::Image image, float rows, float columns, int lastRowQtty){
    int lastRow = lastRowQtty;
    if(lastRowQtty < 0) lastRow = columns;

    float width = image.getSize().x/columns;
    float height = image.getSize().y/rows;
    sf::Texture auxText;
    int qttyColumns = columns;
    for(int k = 0; k < rows; ++k){
        if(k*height > image.getSize().y) return false;
        if(k == rows -1) qttyColumns = lastRow;
        for(int i = 0; i < qttyColumns; ++i){
            if(i*width > image.getSize().x) return false;
            auxText.loadFromImage(image, sf::IntRect(i*width,k*height,width, height));
            animation.push_back(auxText);
        }
    }
    return true;
}


bool Effect::loadFrame(std::string name, int position) {
    if(position >= animation.size()) return false;
    return animation[position].loadFromFile(name);
}

bool Effect::loadFrame(std::string name) {
    sf::Texture text;
    if(! text.loadFromFile(name)) return false;
    else animation.push_back(text);
    return true;
}

bool Effect::loadFrame(sf::Texture & text, int position) {
    if(position >= animation.size()) return false;
    animation[position] = sf::Texture(text);
    return true;
}

bool Effect::loadFrame(sf::Texture & text) {
    animation.push_back(text);
    return true;
}

void Effect::updateAnimation(float deltatime) {
    timeCounter += deltatime;
    if(timeCounter > timeBetweenAnimations){
        timeCounter = 0;
        if(automatic){
            inc_actualAnim();
            this->setTexture(animation[actualAnimation], false);
        }
    }
}

void Effect::drawEffect(sf::RenderTarget& target) {
    if(activated){
        target.draw((*this));
    }
}

void Effect::setActualAnimation(int newPosition)    {
    actualAnimation = newPosition%animation.size();
}

void Effect::inc_actualAnim() {
    actualAnimation = (actualAnimation+1)%animation.size();
}

void Effect::dec_actualAnim() {
    actualAnimation = (actualAnimation-1)%animation.size();
}

void Effect::active()   { activated = true;  }
void Effect::inactive() { activated = false; }

void Effect::enableAutomaticAnimation()     { automatic = true;  }
void Effect::disableAutomaticAnimation()    { automatic = false; }

int Effect::getActualAnimation()                    { return actualAnimation;       }
float Effect::getTimeBetweenAnimations()            { return timeBetweenAnimations; }
void Effect::setTimeBetweenAnimations(float time)   { timeBetweenAnimations = time; }
