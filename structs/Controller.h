#ifndef STRUCTS_CONTROLLER_STATE_H
#define STRUCTS_CONTROLLER_STATE_H

#include "../flatbuffers/rlbot_generated.h"

namespace rlbot {

class ControllerState
{
  private:
    float m_roll;
    float m_pitch;
    float m_yaw;

    float m_throttle;
    float m_steer;

    bool m_handbrake;
    bool m_jump;
    bool m_boost;
    bool m_use_item;
  
  public:
    ControllerState(float throttle = 0, float steer = 0, bool boost = false, bool jump = false,
      bool handbrake = false, float roll = 0, float pitch = 0, float yaw = 0, bool use_item = false):
      m_throttle(throttle), m_steer(steer), m_boost(boost), m_jump(jump), m_handbrake(handbrake),
      m_pitch(pitch), m_yaw(yaw), m_roll(roll), m_use_item(use_item) { }
    
    flatbuffers::Offset<flat::ControllerState>  serialize(flatbuffers::FlatBufferBuilder & out);

    // Todo: Add bounds checks for these.
    ControllerState & withRoll(float roll) { m_roll = roll; return (*this); }
    ControllerState & withPitch(float pitch) { m_pitch = pitch; return (*this); }
    ControllerState & withYaw(float yaw) { m_yaw = yaw; return (*this); }
    ControllerState & withSteer(float steer) { m_steer = steer; return (*this); }
    ControllerState & withThrottle(float throttle) { m_throttle = throttle; return (*this); }

    ControllerState & withHandbrake(bool handbrake) { m_handbrake = handbrake; return (*this); }
    ControllerState & withJump(bool jump) { m_jump = jump; return (*this); }
    ControllerState & withBoost(bool boost) { m_boost = boost; return (*this); }
    ControllerState & withUseItem(bool use_item) { m_use_item = use_item; return (*this); }

};

}

#endif