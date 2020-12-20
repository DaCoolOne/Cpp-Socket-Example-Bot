

#include <stdexcept>
#include <algorithm>
#include "BallPrediction.h"
#include "../constants.h"
using namespace rlbot;

#include <iostream>
using std::cout; using std::endl; using std::cerr;

void BallPrediction::update(const flat::BallPrediction * const bp)
{
  uint8_t buf[2048];

  flatbuffers::Verifier verifier(buf, 2048);

  if(bp == nullptr)
  {
    cout << "NULL PTR" << endl;
  }
  else if(bp->Verify(verifier))
  {
    auto slices = bp->slices();

    m_num_slices = slices->Length();
    m_slices.upscale(m_num_slices);

    // Update prediction.
    // Todo: Make this have less overhead.
    for(long i = 0; i < m_num_slices; ++i)
    {
      // cout << i << endl;
      m_slices.get()[i].update((*slices)[i]);
    }
  }
  else
  {
    cout << "Verification failed for some reason." << endl;
  }
}

void BallPredictionSlice::update(const flat::PredictionSlice * const slice)
{
  cout << "bps update" << endl;
  m_phys.update(slice->physics());
  cout << "bps mid" << endl;
  m_seconds = slice->gameSeconds();
  cout << "e bps update" << endl;
}

const BallPredictionSlice & BallPrediction::getAtTime(float game_seconds)
{
  long target = (game_seconds - m_slices.get()[0].getTime()) * BALL_PRED_SLICES_PER_SEC;

  target = std::min(std::max(target, 0L), m_num_slices);
  
  return m_slices.get()[target];
}

const BallPredictionSlice & BallPrediction::getIndex(int index)
{
  if(index < 0 || index >= m_num_slices)
    throw std::out_of_range("BallPrediction::getIndex(int index): Index is out of bounds");
  return m_slices.get()[index];
}

void BallPrediction::draw(Render & render, int resolution, float forward_time) const
{
  int step_size = std::max(1.0f, BALL_PRED_SLICES_PER_SEC / resolution);
  
  long end_index = forward_time * BALL_PRED_SLICES_PER_SEC;
  end_index = std::min(std::max(end_index, 0L), m_num_slices);

  for(int i = step_size; i < end_index; i += step_size)
  {
    render.line3D(m_slices.get()[i - step_size].getPhys().getLocation(),
      m_slices.get()[i].getPhys().getLocation());
  }
}

