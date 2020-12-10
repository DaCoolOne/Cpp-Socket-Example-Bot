#ifndef STRUCTS_BALL_PREDICTION_H
#define STRUCTS_BALL_PREDICTION_H

#include "../renderer/Render.h"
#include "../flatbuffers/rlbot_generated.h"
#include "BallPredictionSlice.h"
#include "DynamicBuffer.h"

namespace rlbot {

class BallPrediction
{
  private:
    DynamicBuffer<BallPredictionSlice> m_slices;

    long m_num_slices;

  public:
    BallPrediction(): m_num_slices(0) { }

    void update(const flat::BallPrediction * const bp);

    const BallPredictionSlice & getAtTime(float game_seconds);
    const BallPredictionSlice & getIndex(int index);

    void draw(Render & render, int resolution, float forward_time = 6) const;

    bool hasData() const { return m_num_slices; }
};

}

#endif

