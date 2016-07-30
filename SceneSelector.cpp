#include "SceneSelector.hpp"
#include "Resources.hpp"
#include "MyButton.hpp"

SceneSelector::SceneSelector() {
    open = true;
}

SceneSelector::~SceneSelector(){}

void SceneSelector::notAnimation(){
    wantAnimation = false;
}
void SceneSelector::animation(){
    wantAnimation = true;
}

int SceneSelector::select(sf::RenderWindow* window, std::vector<std::string> &buttonNames){
    window->setMouseCursorVisible(true);
    int qttyButtons = buttonNames.size();
    sf::Vector2f buttonSize(window->getSize().x/(qttyButtons+2), window->getSize().y/6);

    std::vector<Button> buttons(qttyButtons);
    for(int i = 0; i < qttyButtons; ++i){
        buttons[i].setFont(Resources::pauseMenuFont);
        buttons[i].setTexture("Resources/Textures/bullet2.png");
        buttons[i].setPressedTexture("Resources/Textures/bullet3.png");
        buttons[i].setText(buttonNames[i]);
        buttons[i].setSize(buttonSize.x, buttonSize.y);
        buttons[i].setPosition(buttonSize.x*(i+1), buttonSize.y*3-buttonSize.y/2);
    }

    open = true;
    while(open){

        sf::Event event;
        while (window->pollEvent(event)) {
            for(int i = 0; i < qttyButtons; ++i){
                buttons[i].handleEvent(event);
            }
            switch (event.type) {
            case sf::Event::Closed:
                window->close();
                exit(0);
                break;
            case sf::Event::JoystickButtonPressed:
                window->setMouseCursorVisible(false);
                return 0;
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape) { window->close(); exit(0); }
                else { window->setMouseCursorVisible(false); return 0; }
                break;
            default:
                break;
            }
            for(int i = 0; i < qttyButtons; ++i){
                if(!buttons[i].isClicked() && buttons[i].hasBeenClicked()){
                    window->setMouseCursorVisible(false);
                    return i;
                }
            }
        }
        window->clear();
        for(int i = 0; i < qttyButtons; ++i){
            buttons[i].draw(*window);
        }
        window->display();
    }
    return 0;
}

void SceneSelector::display(sf::RenderWindow* window, std::string pathImage){
    open = true;
        t.loadFromFile(pathImage);
        s = sf::Sprite();
        s.setTexture(t);
        s.scale(window->getSize().y/s.getGlobalBounds().height,window->getSize().y/s.getGlobalBounds().height);
        s.setPosition(window->getSize().x/2 - s.getGlobalBounds().width/2, 0);
    while(open){

        sf::Event event;
        while (window->pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window->close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape) window->close();
                break;
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    open = false;
                }
                break;
            default:
                break;
            }
            //ANDROID
//                     if(event.type == sf::Event::TouchEnded)  open = false;
//                     break;
        }

        window->clear();
        window->draw(s);

        window->display();

    }

    sf::Clock timer;
    sf::Sprite dark;
    sf::Texture text;
    bool closing = true;
    text.loadFromFile("res/pics/black.png");

    dark.setTexture(text);
    dark.setOrigin(dark.getLocalBounds().width/2,dark.getLocalBounds().height/2);
    dark.setPosition(window->getSize().x/2,window->getSize().y/2);
    float scale = 1/dark.getGlobalBounds().width;;

    float time = 0;
    while(closing and wantAnimation){
        dark.setScale(scale,scale);
        time += timer.restart().asSeconds();
        if(time > 0.1){
            scale *= 1.5;
            time = 0;
        }
        window->clear();
        window->draw(s);
        window->draw(dark);
        window->display();
        if(dark.getGlobalBounds().width > window->getSize().x) closing = false;
    }
    //clean events
    sf::Event e; while (window->pollEvent(e)) { }
}
