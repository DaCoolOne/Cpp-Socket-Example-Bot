#ifndef AGENT_H
#define AGENT_H

#include <string>

#include "renderer/Render.h"
#include "structs/all_structs.h"

class Agent
{
  private:
    short m_team;
    short m_index;
    std::string m_name;

    rlbot::Render m_renderer;

    rlbot::BallPrediction m_ball_prediction;

  public:
    Agent(const std::string & name, short team, short index, SOCKET * s):
      m_name(name), m_team(team), m_index(index), m_renderer(s, index) { }

    ControllerState process(const GameTickPacket & packet);

    short getBotIndex() const { return m_index; }

    void updateBallPrediction(const rlbot::flat::BallPrediction * bp) { m_ball_prediction.update(bp); }
};

#endif