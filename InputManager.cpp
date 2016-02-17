#include "InputManager.hpp"

std::map<int, InputManager::helperM> InputManager::mouseBinds;
std::map<int, InputManager::helperK> InputManager::keyboardBinds;
std::map<int, InputManager::helperJA> InputManager::joystickAxisBinds;
std::map<int, InputManager::helperJB> InputManager::joystickButtonBinds;

void InputManager::bind(int s, sf::Keyboard::Key k) {
    if (keyboardBinds.find(s) == keyboardBinds.end()) keyboardBinds.insert(std::make_pair(s,helperK(k)));
    else keyboardBinds.at(s) = helperK(k);
}

void InputManager::bind(int s, sf::Mouse::Button m) {
    if (mouseBinds.find(s) == mouseBinds.end()) mouseBinds.insert(std::make_pair(s,helperM(m)));
    else mouseBinds.at(s) = helperM(m);
}

void InputManager::bind(int s, int nPad, sf::Joystick::Axis ja) {
    if (joystickAxisBinds.find(s) == joystickAxisBinds.end()) joystickAxisBinds.insert(std::make_pair(s,helperJA(ja,nPad)));
    else joystickAxisBinds.at(s) = helperJA(ja, nPad);
}

void InputManager::bind(int s, int nPad, int nButton) {
    if (joystickButtonBinds.find(s) == joystickButtonBinds.end()) joystickButtonBinds.insert(std::make_pair(s,helperJB(nPad,nButton)));
    else joystickButtonBinds.at(s) = helperJB(nPad,nButton);
}

bool InputManager::isBinded(int s) {
    return (keyboardBinds.find(s) != keyboardBinds.end())
            || (mouseBinds.find(s) != mouseBinds.end()
            || joystickAxisBinds.find(s) != joystickAxisBinds.end()
            || joystickButtonBinds.find(s) != joystickButtonBinds.end());
}

bool InputManager::isKeyboardBinded(int s) {
    return (keyboardBinds.find(s) != keyboardBinds.end());
}

bool InputManager::isMouseBinded(int s) {
    return (mouseBinds.find(s) != mouseBinds.end());
}

bool InputManager::isJoystickBinded(int s) {
    return (joystickAxisBinds.find(s) != joystickAxisBinds.end() || joystickButtonBinds.find(s) != joystickButtonBinds.end());
}

float InputManager::action(int s) {
    auto itK = keyboardBinds.find(s);
    if (itK != keyboardBinds.end() && (*itK).second.b) return true;
    else {
        auto itM = mouseBinds.find(s);
        if (itM != mouseBinds.end() && (*itM).second.b) return true;
        else {
            auto itJA = joystickAxisBinds.find(s);
            if (itJA != joystickAxisBinds.end() && (*itJA).second.pos) return (*itJA).second.pos/100.f;
            else {
                auto itJB = joystickButtonBinds.find(s);
                if (itJB != joystickButtonBinds.end()) return (*itJB).second.b;
                else return false;
            }
        }
    }
}

void InputManager::update() {
    for (auto& kb : keyboardBinds) {
        kb.second.b = sf::Keyboard::isKeyPressed(kb.second.k);
    }
    for (auto& ms : mouseBinds) {
        ms.second.b = sf::Mouse::isButtonPressed(ms.second.m);
    }
    for (auto& jas : joystickAxisBinds) {
        jas.second.pos = sf::Joystick::getAxisPosition(jas.second.nPad,jas.second.j);
    }
    for (auto& jbs : joystickButtonBinds) {
        jbs.second.b = sf::Joystick::isButtonPressed(jbs.second.nPad,jbs.second.nButton);
    }
}
