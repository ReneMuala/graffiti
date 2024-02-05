#pragma once

#include "Font.hpp"
#include <blend2d/context.h>
#include <blend2d/geometry.h>
#include <blend2d/pattern.h>
#include <blend2d/rgba.h>
#include <memory>

class TextPath {
    double size;
    std::shared_ptr<Font> font;
    std::string text;
    BLPoint point;
    public:
    TextPath(std::string text, std::shared_ptr<Font> font, double size, double x, double y):
    text(text), font(font), size(size), point(x, y) {}

    template<typename Style>
    void fill(BLContext & context, const Style & style){
        context.setFillStyle(style);
        context.fillUtf8Text(point,font->getSized(size),text.c_str());
        context.setFillStyle(BLRgba32(0));
    }

    template<typename Style>
    void stroke(BLContext & context, const Style & style){
        context.setStrokeStyle(style);
        context.strokeUtf8Text(point,font->getSized(size),text.c_str());
        context.setFillStyle(BLRgba32(0));
    }
};