#ifndef STRUCTS_FIELD_INFO_H
#define STRUCTS_FIELD_INFO_H

#include "Boost.h"

#include "../flatbuffers/rlbot_generated.h"

namespace rlbot {

class FieldInfo
{
  private:
    Boost * m_boosts;

    short m_num_boosts;
    
    FieldInfo(FieldInfo & source);

  public:
    FieldInfo(): m_num_boosts(0), m_boosts(nullptr) { }
    ~FieldInfo() { delete[] m_boosts; }

    void update(const flat::FieldInfo * const field);
    void updateTick(const flat::GameTickPacket * const packet);

};

}

#endif