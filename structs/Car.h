#ifndef STRUCTS_CAR_H
#define STRUCTS_CAR_H

#include "Physics.h"

#include "../flatbuffers/rlbot_generated.h"

namespace rlbot {
class Car
{
  private:
    Physics m_physics;

    bool m_is_demolished;
    bool m_is_supersonic;

    bool m_has_wheel_contact;

  public:
  
    void update(const flat::PlayerInfo * const player);

    const Physics & physics() const { return m_physics; }

    bool isDemolished() const { return m_is_demolished; }
    bool isSupersonic() const { return m_is_supersonic; }
    bool hasWheelContact() const { return m_has_wheel_contact; }
};
}

#endif