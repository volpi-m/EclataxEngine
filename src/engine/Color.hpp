#pragma once

#include <iostream>

namespace ECL
{
    struct Color
    {
        Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha = 255) : r(red), g(green), b(blue), a(alpha) {}

        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;
    
        static const Color White;
        static const Color Black;
        static const Color Red;
        static const Color Green;
        static const Color Blue;
        static const Color Yellow;
        static const Color Magenta;
        static const Color Purple;
        static const Color Cyan;
    };
}

// std::ostream &operator<<(std::ostream &os, const ECL::Color &color)
// {
//     os << "color {" << color.r << ", " << color.g << ", " << color.b << ", " << color.a << "}" << std::endl;
//     return os;
// }