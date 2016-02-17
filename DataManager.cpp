#include "DataManager.hpp"

std::map <std::string, bool>         DataManager::bMap;
std::map <std::string, float>        DataManager::fMap;
std::map <std::string, std::string>  DataManager::sMap;
std::map <std::string, sf::Vector2f> DataManager::f2Map;

void DataManager::load() {
    std::ifstream file(DATAPATH+std::string("savefile"));
    if (!file.is_open()) return;

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
    int dataType = -1; // 0-> bool, 1 -> float, 2 -> string, 3->Vector2f
    int numberOfelements = 0;
    for (int  i = 0; i < int(v.size()); ++i) {
        if (numberOfelements == 0) {
            numberOfelements = myStoi(v[i].second);
            ++dataType;
            continue;
        }
        --numberOfelements;
        // std::cout << v[i].second << std::endl;
        switch(dataType){
            case 0:
                bMap.insert(std::make_pair(v[i].second,myStob(v[i+1].second)));
                i += 1;
                break;
            case 1:
                fMap.insert(std::make_pair(v[i].second,std::stof(v[i+1].second)));
                i += 1;
                break;
            case 2:
                sMap.insert(std::make_pair(v[i].second,v[i+1].second));
                i += 1;
                break;
            case 3:
                f2Map.insert(std::make_pair(v[i].second,sf::Vector2f(std::stof(v[i+1].second),std::stof(v[i+2].second))));
                i += 2;
                break;
            default:
                exit(EXIT_FAILURE);
        }
    }
}

void DataManager::save() {
    std::ofstream file;
    file.open(DATAPATH+std::string("savefile"));
    int boolSize = bMap.size();
    int floatSize = fMap.size();
    int stringSize = sMap.size();
    int vec2fSize = f2Map.size();

    file << boolSize << std::endl;
    for (auto it = bMap.begin(); it != bMap.end(); ++it) file << it->first << " " << it->second << std::endl;

    file << floatSize << std::endl;
    for (auto it = fMap.begin(); it != fMap.end(); ++it) file << it->first << " " << it->second << std::endl;

    file << stringSize << std::endl;
    for (auto it = sMap.begin(); it != sMap.end(); ++it) file << it->first << " " << it->second << std::endl;

    file << vec2fSize << std::endl;
    for (auto it = f2Map.begin(); it != f2Map.end(); ++it) file << it->first << " " << it->second.x << " " << it->second.y << std::endl;
}

void DataManager::reset() {
    // TODO: First we must to save all the data that is not of the play (options, achivements, etc..) 
    bMap.clear();
    fMap.clear();
    sMap.clear();
    f2Map.clear();
    save();
}

bool DataManager::getBool(std::string key, bool defaultValue) {
    auto it = bMap.find(key);
    if (it == bMap.end()) return defaultValue;
    else return it->second;
}
float DataManager::getFloat(std::string key, float defaultValue) {
    auto it = fMap.find(key);
    if (it == fMap.end()) return defaultValue;
    else return it->second;
}
std::string DataManager::getString(std::string key, std::string defaultValue) {
    auto it = sMap.find(key);
    if (it == sMap.end()) return defaultValue;
    else return it->second;
}
sf::Vector2f DataManager::getVector2f(std::string key, sf::Vector2f defaultValue) {
    auto it = f2Map.find(key);
    if (it == f2Map.end()) return defaultValue;
    else return it->second;
}

void DataManager::setBool(std::string key, bool value) {
    if (bMap.find(key) == bMap.end()) bMap.insert(std::make_pair(key,value));
    else bMap.at(key) = value;
}

void DataManager::setFloat(std::string key, float value) {
    if (fMap.find(key) == fMap.end()) fMap.insert(std::make_pair(key,value));
    else fMap.at(key) = value;
}

void DataManager::setString(std::string key, std::string value) {
    if (sMap.find(key) == sMap.end()) sMap.insert(std::make_pair(key,value));
    else sMap.at(key) = value;
}

void DataManager::setVector2f(std::string key, sf::Vector2f value) {
    if (f2Map.find(key) == f2Map.end()) f2Map.insert(std::make_pair(key,value));
    else f2Map.at(key) = value;
}