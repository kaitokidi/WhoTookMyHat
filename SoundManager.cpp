#include "SoundManager.hpp"
#include "utils.hpp"

//PLACE HERE A FORWARD DECLARATION OF YOUR STATIC VARIABLES
//sf::SoundBuffer     SoundManager::SOUND_NAME;
//sf::Music           SoundManager::MUSIC_NAME;

/* Example:
sf::Music           SoundManager::overWorldMusic;
sf::SoundBuffer     SoundManager::attackBuf;
*/
std::string SoundManager::currentMusic;
std::string SoundManager::currentSound;

sf::SoundBuffer SoundManager::soundBuffers [13];

std::map<std::string, sf::Sound> SoundManager::soundMap;
std::map<std::string, sf::Music> SoundManager::musicMap;
std::map<std::string, sf::Sound>::iterator SoundManager::sit;
std::map<std::string, sf::Music>::iterator SoundManager::mit;


void SoundManager::load(){

    //LOAD HERE YOUR SOUNDS AND MUSIC
    //(previously declared static on private and writted the forward declaration on top of this class)

    /* Example:
    musicMap["overWorld"].openFromFile("Resources/Sounds/overWorld.ogg");
    if(!attackBuf.loadFromFile("Resources/Sounds/attack.ogg")){ std::cout << "Fail on loading attack" << std::endl;};
    soundMap["chamaleonTongue"].setBuffer(attackBuf);
    */

    //MUSUIC
    if(! musicMap["end"].openFromFile("Resources/Music/Other/credits.ogg") ) std::cout << "sure for the music and that" << std::endl;
    musicMap["portada"].openFromFile("Resources/Music/Other/portada.ogg");
    musicMap["pressAnyKey"].openFromFile("Resources/Music/Other/pressAnyKey.ogg");
    musicMap["menuButtons"].openFromFile("Resources/Music/Other/menuButtons.ogg");

    musicMap["initialAnimation"].openFromFile("Resources/Music/Other/initialAnimation.ogg");

    musicMap["tunel1"].openFromFile("Resources/Music/tunels/tutorial.ogg");
    musicMap["tunel2"].openFromFile("Resources/Music/follow.ogg");
    musicMap["tunel3"].openFromFile("Resources/Music/follow.ogg");
    musicMap["tunel4"].openFromFile("Resources/Music/follow.ogg");
    musicMap["tunel5"].openFromFile("Resources/Music/follow.ogg");
    musicMap["tunel6"].openFromFile("Resources/Music/tunels/tunel6.ogg");
    musicMap["tunel7"].openFromFile("Resources/Music/tunels/tunel7.ogg");
    musicMap["tunel8"].openFromFile("Resources/Music/tunels/tunel8.ogg");

    musicMap["level1"].openFromFile("Resources/Music/levels/level1.ogg");
        musicMap["level1_1"].openFromFile("Resources/Music/follow.ogg");
        musicMap["level1_2"].openFromFile("Resources/Music/follow.ogg");
        musicMap["level1_3"].openFromFile("Resources/Music/follow.ogg");

    musicMap["level2"].openFromFile("Resources/Music/levels/level2.ogg");
        musicMap["level2_1"].openFromFile("Resources/Music/follow.ogg");
        musicMap["level2_2"].openFromFile("Resources/Music/follow.ogg");
        musicMap["level2_3"].openFromFile("Resources/Music/follow.ogg");

    musicMap["level3"].openFromFile("Resources/Music/levels/level3.ogg");
        musicMap["level3_1"].openFromFile("Resources/Music/follow.ogg");
        musicMap["level3_2"].openFromFile("Resources/Music/follow.ogg");
        musicMap["level3_3"].openFromFile("Resources/Music/follow.ogg");

    musicMap["level4"].openFromFile("Resources/Music/levels/level4.ogg");
        musicMap["level4_1"].openFromFile("Resources/Music/follow.ogg");
        musicMap["level4_2"].openFromFile("Resources/Music/follow.ogg");
        musicMap["level4_3"].openFromFile("Resources/Music/follow.ogg");

    musicMap["level5"].openFromFile("Resources/Music/levels/level5.ogg");
        musicMap["level5_1"].openFromFile("Resources/Music/follow.ogg");
        musicMap["level5_2"].openFromFile("Resources/Music/follow.ogg");
        musicMap["level5_3"].openFromFile("Resources/Music/follow.ogg");


    //SOUNDS
    int i = 0;

    if(!soundBuffers[i].loadFromFile("Resources/Sounds/171696__nenadsimic__picked-coin-echo.ogg")){ std::cout << "Fail on hat1" << std::endl;};
    soundMap["hat1"].setBuffer(soundBuffers[i]); ++i;

    if(!soundBuffers[i].loadFromFile("Resources/Sounds/220184__gameaudio__win-spacey.ogg")){ std::cout << "Fail on hat2" << std::endl;};
    soundMap["hat2"].setBuffer(soundBuffers[i]); ++i;

    if(!soundBuffers[i].loadFromFile("Resources/Sounds/swosh-13.ogg")){ std::cout << "Fail on enemydie" << std::endl;};
    soundMap["enemyDie"].setBuffer(soundBuffers[i]); ++i;

    if(!soundBuffers[i].loadFromFile("Resources/Sounds/72190__snowflakes__whip02.ogg")){ std::cout << "Fail on hook1" << std::endl;};
    soundMap["hook1"].setBuffer(soundBuffers[i]); ++i;

    if(!soundBuffers[i].loadFromFile("Resources/Sounds/191766__underlineddesigns__bamboo-whip-sound-effect.ogg")){ std::cout << "Fail on hook2" << std::endl;};
    soundMap["hook2"].setBuffer(soundBuffers[i]); ++i;

    if(!soundBuffers[i].loadFromFile("Resources/Sounds/123761__vicces1212__jump.ogg")){ std::cout << "Fail on shoot" << std::endl;};
    soundMap["shoot"].setBuffer(soundBuffers[i]); ++i;

    if(!soundBuffers[i].loadFromFile("Resources/Sounds/322533__fran89__bongo.ogg")){ std::cout << "Fail on hit" << std::endl;};
    soundMap["hit"].setBuffer(soundBuffers[i]); ++i;

    if(!soundBuffers[i].loadFromFile("Resources/Sounds/167127__crisstanza__pause.ogg")){ std::cout << "Fail on pause" << std::endl;};
    soundMap["pause"].setBuffer(soundBuffers[i]); ++i;

    if(!soundBuffers[i].loadFromFile("Resources/Sounds/167126__crisstanza__unpause.ogg")){ std::cout << "Fail on unpause" << std::endl;};
    soundMap["unpause"].setBuffer(soundBuffers[i]); ++i;

    if(!soundBuffers[i].loadFromFile("Resources/Sounds/187025__lloydevans09__jump1.ogg")){ std::cout << "Fail on playerhit" << std::endl;};
    soundMap["playerhit"].setBuffer(soundBuffers[i]); ++i;

    if(!soundBuffers[i].loadFromFile("Resources/Sounds/157569__elektroproleter__cartoon-jump.ogg")){ std::cout << "Fail on enembouncy" << std::endl;};
    soundMap["enemyBouncy"].setBuffer(soundBuffers[i]); ++i;

    if(!soundBuffers[i].loadFromFile("Resources/Sounds/187025__lloydevans09__jump1.ogg")){ std::cout << "Fail on playerJump" << std::endl;};
    soundMap["playerJump"].setBuffer(soundBuffers[i]); ++i;

    if(!soundBuffers[i].loadFromFile("Resources/Sounds/270328__littlerobotsoundfactory__hero-death-00.ogg")){ std::cout << "Fail on die" << std::endl;};
    soundMap["playerDeath"].setBuffer(soundBuffers[i]); ++i;

    std::cout << "sounds loaded" << std::endl;
}



void SoundManager::playSound(std::string name){
    sit = soundMap.find(name);
    if (sit != soundMap.end()) {
        (sit->second).play();
        currentSound = name;
    }
}

void SoundManager::playMusic(std::string name){
    if( name != "follow") {
        stopMusic(currentMusic);
        if(name != "none"){
            mit = musicMap.find(name);
            if (mit != musicMap.end()) {
                (mit->second).play();
                currentMusic = name;
            } else log("trying to play wrong music: ", name);
        } else log("none music");
    }
}

void SoundManager::stopMusic(std::string name){
    if(name  != "follow" && name != "none") {
        mit = musicMap.find(name);
        if (mit != musicMap.end()) {
            (mit->second).stop();
            currentMusic = "none";
        }
    }
}

void SoundManager::pauseMusic(std::string name){
    mit = musicMap.find(name);
    if (mit != musicMap.end()) (mit->second).pause();

}

void SoundManager::setLoop(bool loop, std::string name){
    mit = musicMap.find(name);
    if (mit != musicMap.end()) (mit->second).setLoop(loop);

}

void SoundManager::setPitch(float pitch, std::string name){
    mit = musicMap.find(name);
    if (mit != musicMap.end()) (mit->second).setPitch(pitch);
}

void SoundManager::setVolume(float volume, std::string name){
    mit = musicMap.find(name);
    if (mit != musicMap.end()) (mit->second).setVolume(volume);
}

void SoundManager::setPosition(float x, float y, float z, std::string name){
    mit = musicMap.find(name);
    if (mit != musicMap.end()) (mit->second).setPosition(x,y,z);
}


void SoundManager::setGlobalSoundVolumen(float volume) {
    for (auto it = soundMap.begin(); it != soundMap.end(); ++it) (it->second).setVolume(volume);
}

void SoundManager::setGlobalMusicVolumen(float volume) {
    for (auto it = musicMap.begin(); it != musicMap.end(); ++it) (it->second).setVolume(volume);
}
