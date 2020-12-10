#ifndef STRUCTS_GAME_INFO_H
#define STRUCTS_GAME_INFO_H

#include "../flatbuffers/rlbot_generated.h"

namespace rlbot {

class GameInfo
{
  private:
    float m_game_time;
    float m_time_remaining;
    float m_game_speed;

    bool m_is_kickoff_pause;
    bool m_is_overtime;
    bool m_is_round_active;
    bool m_is_match_ended;

  public:
    
    void update(const flat::GameInfo * const info);

    float time() const { return m_game_time; }
    float timeRemaining() const { return m_time_remaining; }
    
    bool isMatchOver() const { return m_is_match_ended; }
    bool isOvertime() const { return m_is_overtime; }
    bool isKickoff() const { return m_is_kickoff_pause; }
    bool isBeforeKickoff() const { return m_is_kickoff_pause && !m_is_round_active; }
    bool isRoundActive() const { return m_is_round_active; }
};

}

#endif