#ifndef STRUCTS_PHYSICS_H
#define STRUCTS_PHYSICS_H

#include "../flatbuffers/rlbot_generated.h"

#include "Rotation.h"
#include "Vec3.h"

namespace rlbot {

class Physics
{
  private:
    Vec3 m_position;
    Vec3 m_velocity;
    Vec3 m_angular_velocity;
    Rotation m_rotation;

  public:
    
    void update(const flat::Physics * const phys);

    Vec3 & getLocation() { return m_position; }
    const Vec3 & getLocation() const { return m_position; }

    Vec3 & getVelocity() { return m_velocity; }
    const Vec3 & getVelocity() const { return m_velocity; }

    Vec3 & getAngularVelocity() { return m_angular_velocity; }
    const Vec3 & getAngularVelocity() const { return m_angular_velocity; }
    
    Rotation & getRotation() { return m_rotation; }
    const Rotation & getRotation() const { return m_rotation; }
};

}

#endif