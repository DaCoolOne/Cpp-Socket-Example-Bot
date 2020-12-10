#ifndef STRUCTS_ROTATION_H
#define STRUCTS_ROTATION_H

#include "../flatbuffers/rlbot_generated.h"

// Todo: Transform this from quaternion to matrix.
namespace rlbot {
class Rotation
{
  private:
    float m_pitch;
    float m_yaw;
    float m_roll;

  public:
    Rotation(float pitch = 0, float yaw = 0, float roll = 0):
      m_pitch(pitch), m_yaw(yaw), m_roll(roll) { }

    float getPitch() const { return m_pitch; }
    float getRoll() const { return m_roll; }
    float getYaw() const { return m_yaw; }

    // Todo
    // void update(const flat::Quaternion * const quat);
    
    void update(const flat::Rotator * const rot);
};
}

#endif