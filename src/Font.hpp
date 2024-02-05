#pragma once

#include <blend2d.h>
#include <blend2d/api.h>
#include <blend2d/font.h>
#include <optional>
#include <string>
#include <stdexcept>
#include <format>

class Font {
    BLFontFace face;
    public:

    Font(std::string filename){
        if(face.createFromFile(filename.c_str()) != BL_SUCCESS){
            throw std::runtime_error(std::format("{}: {} \"{}\"", __FUNCTION__,
                                         "Unable to read font face from ",
                                         filename));
        }
    }

    BLFont getSized(double size){
        BLFont font;
        font.createFromFace(face, size);
        return font;
    }
};