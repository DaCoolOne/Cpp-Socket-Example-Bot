#ifndef RENDERER_RENDER_H
#define RENDERER_RENDER_H

#include "winsock2.h"
#include <vector>
#include <string>
#include "../structs/Vec3.h"
#include "Color.h"

namespace rlbot {

const int DEFAULT_TEXT_SCALE = 2;

class Render
{
  private:
    SOCKET * m_out;

    flatbuffers::FlatBufferBuilder * m_builder;

    Color m_current_color;

    std::vector<flatbuffers::Offset<flat::RenderMessage>> m_render_queue;

    int m_render_group;

  public:
    Render(SOCKET * s, int group): m_out(s), m_render_group(group), m_builder(nullptr),
      m_current_color(), m_render_queue() { }
    ~Render() { delete m_builder; delete m_out; }

    void beginDraw();

    void setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);

    void rect2D(int x, int y, int width, int height, bool fill = true);
    void rect3D(const Vec3 & location, int width, int height, bool fill = true);

    void string2D(const std::string & text, int x, int y,
      int scale_x = DEFAULT_TEXT_SCALE, int scale_y = DEFAULT_TEXT_SCALE);
    void string3D(const std::string & text, const Vec3 & location,
      int scale_x = DEFAULT_TEXT_SCALE, int scale_y = DEFAULT_TEXT_SCALE);
    
    void line2D(const Vec3 & start, const Vec3 & end);
    void line3D(const Vec3 & start, const Vec3 & end);
    void line2D3D(const Vec3 & start, const Vec3 & end);

    void polyline2D(const std::vector<Vec3> & points);
    void polyline3D(const std::vector<Vec3> & points);

    void flush();
};

}

#endif