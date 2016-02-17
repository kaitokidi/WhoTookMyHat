#ifndef __DATAMANAGER_HPP__
#define __DATAMANAGER_HPP__

#include <map>
#include <SFML/System.hpp>
#include "utils.hpp"


class DataManager {
public:
    static void load();
    static void save();
    static void reset();

    static bool getBool(std::string key, bool defaultValue = false);
    static float getFloat(std::string key, float defaultValue = 0.0f);
    static std::string getString(std::string key, std::string defaultValue = "");
    static sf::Vector2f getVector2f(std::string key, sf::Vector2f defaultValue = sf::Vector2f(0,0));

    static void setBool(std::string key, bool value);
    static void setFloat(std::string key, float value);
    static void setString(std::string key, std::string value);
    static void setVector2f(std::string key, sf::Vector2f value);

private:
    static std::map<std::string, bool> bMap;
    static std::map<std::string, float> fMap;
    static std::map<std::string, std::string> sMap;
    static std::map<std::string, sf::Vector2f> f2Map;
};


#endif