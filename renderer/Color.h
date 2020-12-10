#ifndef RENDERER_COLOR_H
#define RENDERER_COLOR_H

namespace rlbot
{

struct Color
{
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
  
  Color(): r(255), g(255), b(255), a(255) { }
  Color(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a = 255):
    r(_r), g(_g), b(_b), a(_a) { }
};

}

#endif