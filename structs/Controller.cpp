

#include "../constants.h"
#include "Controller.h"
using namespace rlbot;

flatbuffers::Offset<flat::ControllerState> ControllerState::serialize(flatbuffers::FlatBufferBuilder & builder)
{
  return flat::CreateControllerState(builder, m_throttle, m_steer,
    m_pitch, m_yaw, m_roll, m_jump, m_boost, m_handbrake, m_use_item);
}

