#ifndef STRUCTS_BALL_PREDICTION_SLICE_H
#define STRUCTS_BALL_PREDICTION_SLICE_H

#include "Physics.h"

namespace rlbot
{

class BallPredictionSlice
{
  private:
    Physics m_phys;
    float m_seconds;
  public:
    
    float getTime() const { return m_seconds; }
    const Physics & getPhys() const { return m_phys; }

    void update(const flat::PredictionSlice * const slice);
};

}

#endif

