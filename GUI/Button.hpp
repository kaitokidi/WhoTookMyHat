#ifndef BUTTON_HPP
#define BUTTON_HPP

#ifdef _WIN32
#define NOMINMAX
#define M_PI 3.14159
#define and &&
#define or ||
#define not !
#endif

#include <iostream>
#include <functional>
#include "Widget.hpp"

class Button : public Widget {

    public:
        using FuncType = std::function<void(const sf::Event& event,Button& self)>;

        FuncType onClick;
        static FuncType defaultFunc;

        virtual ~Button();
        Button(Widget* parent=nullptr);


    protected:

        virtual bool processEvent(const sf::Event& event,
                                  const sf::Vector2f& parent_pos,
                                  const sf::RenderTarget& target)override;
        virtual void onMouseEntered();
        virtual void onMouseLeft();

    private:

        enum Status {None = 0,Hover = 1};
        int _status;
};

#endif // BUTTON_HPP
