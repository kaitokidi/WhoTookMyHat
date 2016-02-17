#ifndef VLAYOUT_HPP
#define VLAYOUT_HPP

#include "Layout.hpp"

class VLayout : public Layout {

public:

    VLayout(const VLayout&) = delete;
    VLayout(Widget* parent = nullptr);
    VLayout& operator=(const VLayout&) = delete;

    ~VLayout();

    void add(Widget* widget);

    Widget* at(unsigned int index)const;

    virtual sf::Vector2f getSize()const override;

    int getNWidgets();


    bool centered() const;
    void setCentered(bool centered);

protected:

    virtual bool processEvent(const sf::Event& event,
                              const sf::Vector2f& parent_pos,
                              const sf::RenderTarget& target) override;

    virtual void processEvents(const sf::Vector2f& parent_pos) override;


private:
    bool _centered;
    std::vector<Widget*> _widgets;
    virtual void updateShape() override;
    virtual void draw(sf::RenderTarget& target,
                      sf::RenderStates states) const override;
};

#endif // VLAYOUT_HPP
