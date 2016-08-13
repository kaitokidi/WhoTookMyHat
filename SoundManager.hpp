#ifndef SOUNDMANAGER_HPP
#define SOUNDMANAGER_HPP

#include <map>
#include <iostream>
#include <SFML/Audio.hpp>

class SoundManager {

public:
    static void load();

    static void playSound(std::string name);
    static void playMusic(std::string name);
    static void stopMusic(std::string name);
    static void pauseMusic(std::string name);
    static void setLoop(bool loop, std::string name);
    static void setPitch(float pitch, std::string name);
    static void setVolume(float volume, std::string name);
    static void setPosition(float x, float y, float z, std::string name);
    static void setGlobalSoundVolumen(float volume);
    static void setGlobalMusicVolumen(float volume);

private:


    //INITIALIZE YOUR VARIABLES AS STATIC sf::Music or sf::SoundBuffer
    /* Example:
     static sf::Music   overWorldMusic;
     static sf::SoundBuffer     attackBuf;
    */
    static sf::SoundBuffer soundBuffers [13];
/*    static sf::SoundBuffer      playerJump;
    static sf::SoundBuffer      a;
    static sf::SoundBuffer      aa;
    static sf::SoundBuffer      aaa;
    static sf::SoundBuffer      aaaa;
    static sf::SoundBuffer      aaaaa;
    static sf::SoundBuffer      aaaaaa;
    static sf::SoundBuffer      aaaaaaa;
    static sf::SoundBuffer      aaaaaaaa;
    static sf::SoundBuffer      aaaaaaaaa;
    static sf::SoundBuffer      b;
    static sf::SoundBuffer      c;
    static sf::SoundBuffer      d;*/


     static std::map<std::string, sf::Sound> soundMap;
     static std::map<std::string, sf::Music> musicMap;
     static std::map<std::string, sf::Sound>::iterator sit;
     static std::map<std::string, sf::Music>::iterator mit;

};

#endif // SOUNDMANAGER_HPP
