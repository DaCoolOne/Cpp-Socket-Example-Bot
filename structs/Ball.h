#ifndef STRUCTS_BALL_H
#define STRUCTS_BALL_H

#include "Physics.h"
#include "../flatbuffers/rlbot_generated.h"

namespace rlbot {

class Ball
{
  private:
    Physics m_physics;
  
  public:
    
    const Physics & getPhysics() const { return m_physics; }

    void update(const flat::BallInfo * const ball);
};

}


#endif