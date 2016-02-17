#include "Layout.hpp"


Layout::Layout(Widget *parent): Widget(parent), _space(5){}

Layout::~Layout(){}

void Layout::setSpace(float pixels) {
    if(pixels >= 0) {
        _space = pixels;
        updateShape();
    }
    else throw std::invalid_argument("pixelvalue must be >= 0");
}

