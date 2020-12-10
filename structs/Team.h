#ifndef STRUCTS_TEAM_H
#define STRUCTS_TEAM_H

#include "../flatbuffers/rlbot_generated.h"

namespace rlbot {

class Team
{
  private:
    short m_score;
    short m_index;
  public:
    Team(const short index): m_index(index), m_score(0) { }

    void update(const flat::TeamInfo * const team);
};

}

#endif