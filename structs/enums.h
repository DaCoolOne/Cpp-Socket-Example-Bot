#ifndef STRUCTS_ENUMS_H
#define STRUCTS_ENUMS_H

#include "../flatbuffers/base.h"

enum class RECIEVE_PACKET {
  GAME_PACKET = 1,
  FIELD_INFO = 2,
  MATCH_SETTINGS = 3,
  
  // Should not be recieved
  // PLAYER_INPUT = 4,

  // Depreciated
  // ACTOR_MAPPING = 5,
  // COMPUTER_ID = 6,

  // Todo
  // DESIRED_GAME_STATE = 7,
  // QUICK_CHAT = 9,

  BALL_PREDICTION = 10,
};

enum class SEND_PACKET {
  PLAYER_INPUT = 4,
  RENDER_GROUP = 8,
};

enum class RECIEVE_FLAGS {
  NONE = 0,

  GAME_PACKET         = 1 << 0,
  FIELD_INFO          = 1 << 1,
  MATCH_SETTINGS      = 1 << 2,

  DESIRED_GAME_STATE  = 1 << 4,
  RENDER_GROUP        = 1 << 5,
  QUICK_CHAT          = 1 << 6,

  BALL_PREDICTION     = 1 << 7,
};

inline RECIEVE_FLAGS operator|(RECIEVE_FLAGS a, RECIEVE_FLAGS b)
{
  return static_cast<RECIEVE_FLAGS>(static_cast<uint16_t>(a) | static_cast<uint16_t>(b));
}

inline RECIEVE_FLAGS operator&(RECIEVE_FLAGS a, RECIEVE_FLAGS b)
{
  return static_cast<RECIEVE_FLAGS>(static_cast<uint16_t>(a) & static_cast<uint16_t>(b));
}

inline RECIEVE_FLAGS operator^(RECIEVE_FLAGS a, RECIEVE_FLAGS b)
{
  return static_cast<RECIEVE_FLAGS>(static_cast<uint16_t>(a) ^ static_cast<uint16_t>(b));
}

inline bool operator==(uint16_t a, RECIEVE_PACKET b)
{
  return a == static_cast<uint16_t>(b);
}

inline bool operator==(RECIEVE_PACKET a, uint16_t b)
{
  return static_cast<uint16_t>(a) == b;
}

#endif // ENUMS_H