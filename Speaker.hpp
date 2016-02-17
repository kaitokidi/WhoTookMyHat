#ifndef SPEAKER_HPP
#define SPEAKER_HPP
#include "utils.hpp"
#include "Resources.hpp"

class Speaker : public Prop{

public:
    Speaker(int gid, sf::Vector2f pos, std::string textKey);

    bool getSpeaking() const;
    std::string text() const;

    void setSpeaking(bool value);
    void setText(const std::string &text);

private:
    bool _speaking;
    std::string _text;
};

#endif // SPEAKER_HPP
