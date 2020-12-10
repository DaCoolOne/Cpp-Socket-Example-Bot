

#include "../networking/socket_lib.h"
#include "../structs/enums.h"
#include "Render.h"
using namespace rlbot;
using namespace rlbot::networking;

void Render::beginDraw()
{
  delete m_builder;
  m_builder = new flatbuffers::FlatBufferBuilder();
  m_render_queue.clear();
}

void Render::setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
  m_current_color = Color(r, g, b, a);
}

void Render::line3D(const Vec3 & start, const Vec3 & end)
{
  auto start_pos = start.__construct_flat();
  auto end_pos = end.__construct_flat();

  auto color = flat::CreateColor(*m_builder, m_current_color.a, m_current_color.r, m_current_color.g, m_current_color.b);

  m_render_queue.push_back(flat::CreateRenderMessage(*m_builder, flat::RenderType_DrawLine3D, color, &start_pos,
    &end_pos));
}

void Render::line2D(const Vec3 & start, const Vec3 & end)
{
  auto start_pos = start.__construct_flat();
  auto end_pos = end.__construct_flat();

  auto color = flat::CreateColor(*m_builder, m_current_color.a, m_current_color.r, m_current_color.g, m_current_color.b);

  m_render_queue.push_back(flat::CreateRenderMessage(*m_builder, flat::RenderType_DrawLine2D, color, &start_pos,
    &end_pos));
}

void Render::line2D3D(const Vec3 & start, const Vec3 & end)
{
  auto start_pos = start.__construct_flat();
  auto end_pos = end.__construct_flat();

  auto color = flat::CreateColor(*m_builder, m_current_color.a, m_current_color.r, m_current_color.g, m_current_color.b);

  m_render_queue.push_back(flat::CreateRenderMessage(*m_builder, flat::RenderType_DrawLine2D_3D, color, &start_pos,
    &end_pos));
}

void Render::rect2D(int x, int y, int width, int height, bool fill)
{
  auto pos = Vec3(x, y).__construct_flat();

  auto color = flat::CreateColor(*m_builder, m_current_color.a, m_current_color.r, m_current_color.g, m_current_color.b);

  m_render_queue.push_back(flat::CreateRenderMessage(*m_builder, flat::RenderType_DrawRect2D, color, &pos,
    0, width, height, 0, fill));
}


void Render::rect3D(const Vec3 & location, int width, int height, bool fill)
{
  auto pos = location.__construct_flat();

  auto color = flat::CreateColor(*m_builder, m_current_color.a, m_current_color.r, m_current_color.g, m_current_color.b);

  m_render_queue.push_back(flat::CreateRenderMessage(*m_builder, flat::RenderType_DrawRect3D, color, &pos,
    0, width, height, 0, fill));
}

void Render::string2D(const std::string & text, int x, int y, int scale_x, int scale_y)
{
  auto pos = Vec3(x, y).__construct_flat();

  auto color = flat::CreateColor(*m_builder, m_current_color.a, m_current_color.r, m_current_color.g, m_current_color.b);

  auto flat_text = m_builder->CreateString(text);

  m_render_queue.push_back(flat::CreateRenderMessage(*m_builder, flat::RenderType_DrawString2D, color, &pos,
    0, scale_x, scale_y, flat_text));
}

void Render::string3D(const std::string & text, const Vec3 & location, int scale_x, int scale_y)
{
  auto pos = location.__construct_flat();

  auto color = flat::CreateColor(*m_builder, m_current_color.a, m_current_color.r, m_current_color.g, m_current_color.b);

  auto flat_text = m_builder->CreateString(text);

  m_render_queue.push_back(flat::CreateRenderMessage(*m_builder, flat::RenderType_DrawString3D, color, &pos,
    0, scale_x, scale_y, flat_text));
}


void Render::polyline2D(const std::vector<Vec3> & points)
{
  for(int i = 0; i < points.size() - 1; ++i)
  {
    line2D(points[i], points[i+1]);
  }
}

void Render::polyline3D(const std::vector<Vec3> & points)
{
  for(int i = 0; i < points.size() - 1; ++i)
  {
    line3D(points[i], points[i+1]);
  }
}

void Render::flush()
{
  MakeBlocking(*m_out);

  // Todo: Render groups.
  // Flush all of the render messages to a single render group.
  auto render_group = flat::CreateRenderGroup(*m_builder, m_builder->CreateVector(m_render_queue), m_render_group);

  m_builder->Finish(render_group);

  uint16_t size = m_builder->GetSize();

  uint8_t header_buffer[4];
  
  MakeHeader(header_buffer, SEND_PACKET::RENDER_GROUP, size);

  // Send the resulting render group.
  int result = send(*m_out, reinterpret_cast<char*>(header_buffer), 4, 0);
  result = send(*m_out, reinterpret_cast<char*>(m_builder->GetBufferPointer()), size, 0);
}

