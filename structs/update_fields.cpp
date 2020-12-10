

#include "Ball.h"
#include "Boost.h"
#include "Car.h"
#include "FieldInfo.h"
#include "GameInfo.h"
#include "GameTickPacket.h"
#include "Physics.h"
#include "Team.h"
using namespace rlbot;

void Ball::update(const flat::BallInfo * const ball)
{
  m_physics.update(ball->physics());
}

void Boost::updateTick(const flat::BoostPadState * const boost)
{
  m_is_active = boost->isActive();

  // Depreciated
  // m_timer = boost->timer();
}

void Boost::update(const flat::BoostPad * const boostpad)
{
  m_position.update(boostpad->location());
  m_is_full_boost = boostpad->isFullBoost();
}

void Car::update(const flat::PlayerInfo * const player)
{
  m_physics.update(player->physics());
  
  m_is_demolished = player->isDemolished();
  m_is_supersonic = player->isSupersonic();
  m_has_wheel_contact = player->hasWheelContact();
}

void FieldInfo::update(const flat::FieldInfo * const field)
{
  m_num_boosts = field->boostPads()->Length();
  
  delete[] m_boosts;
  m_boosts = new Boost[m_num_boosts];
  
  for(short i = 0; i < m_num_boosts; i++)
    m_boosts[i].update(field->boostPads()->Get(i));

}

void FieldInfo::updateTick(const flat::GameTickPacket * const packet)
{
  for(short i = 0; i < m_num_boosts; i++)
    m_boosts[i].updateTick(packet->boostPadStates()->Get(i));
}

void GameInfo::update(const flat::GameInfo * const info)
{
  m_is_kickoff_pause = info->isKickoffPause();
  m_is_overtime = info->isOvertime();
  m_is_round_active = info->isRoundActive();
  m_is_match_ended = info->isMatchEnded();

  m_game_speed = info->gameSpeed();

  m_game_time = info->secondsElapsed();
  m_time_remaining = info->gameTimeRemaining();
}

void GameTickPacket::update(const flat::GameTickPacket * const packet)
{
  short num_cars = packet->players()->Length();

  // Resize array if need be.
  if(m_num_cars != num_cars)
  {
    m_num_cars = num_cars;

    delete[] m_players;
    m_players = new Car[num_cars];
  }

  for(short i = 0; i < m_num_cars; i ++)
  {
    m_players[i].update(packet->players()->Get(i));
  }

  m_ball.update(packet->ball());

  m_has_been_initialized = true;
}

void Physics::update(const flat::Physics * const phys)
{
  m_rotation.update(phys->rotation());
  m_velocity.update(phys->velocity());
  m_position.update(phys->location());
  m_angular_velocity.update(phys->angularVelocity());
}

void Rotation::update(const flat::Rotator * const rot)
{
  m_pitch = rot->pitch();
  m_yaw = rot->yaw();
  m_roll = rot->roll();
}

void Team::update(const flat::TeamInfo * const team)
{
  m_score = team->score();
}

void Vec3::update(const flat::Vector3 * const vec)
{
  x = vec->x();
  y = vec->y();
  z = vec->z();
}



