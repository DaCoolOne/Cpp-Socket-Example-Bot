

#include <stdexcept>
#include <string>
#include "GameTickPacket.h"
using namespace rlbot;

const Car & GameTickPacket::getCar(short index) const
{
  if(index < 0 || index >= m_num_cars)
    throw std::invalid_argument(
      "const Car & GameTickPacket::getCar(short index) invalid argument. "
      "Index " + std::to_string(index) + " is out of range");
  return m_players[index];
}

GameTickPacket::~GameTickPacket()
{
  delete[] m_players;
}
