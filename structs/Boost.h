#ifndef STRUCTS_BOOST_H
#define STRUCTS_BOOST_H

#include "Vec3.h"
#include "../flatbuffers/rlbot_generated.h"

namespace rlbot {

class Boost
{
  private:
    Vec3 m_position;

    bool m_is_full_boost;
    bool m_is_active;
  
  public:
    
    void updateTick(const flat::BoostPadState * const boost);
    void update(const flat::BoostPad * const boostpad);

};

}

#endif