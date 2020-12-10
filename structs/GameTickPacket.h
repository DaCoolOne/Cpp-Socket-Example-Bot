#ifndef STRUCTS_GAME_TICK_PACKET_H
#define STRUCTS_GAME_TICK_PACKET_H

#include "../constants.h"
#include "Car.h"
#include "Ball.h"
#include "GameInfo.h"

#include "../flatbuffers/rlbot_generated.h"

namespace rlbot {

/*
table GameTickPacket {
  players:[PlayerInfo];
  boostPadStates:[BoostPadState];
  ball:BallInfo;
  gameInfo:GameInfo;
  tileInformation:[DropshotTile];
  teams:[TeamInfo];
}
*/

class GameTickPacket
{
  private:
    Car * m_players;
    short m_num_cars;
    GameInfo m_game_info;
  
    Ball m_ball;
    
    // Disallow copying of game tick packet.
    GameTickPacket& operator=(const GameTickPacket & source);
    GameTickPacket(GameTickPacket & source);

    bool m_has_been_initialized;

  public:
    GameTickPacket(): m_players(nullptr), m_num_cars(0), m_ball(),
      m_has_been_initialized(false) { }
    ~GameTickPacket();

    void update(const flat::GameTickPacket * const packet);

    const Ball & getBall() const { return m_ball; }
    const Car & getCar(short index) const;

    bool hasBeenInitialized() const { return m_has_been_initialized; }

    const GameInfo & getGameInfo() const { return m_game_info; }

};

}

#endif