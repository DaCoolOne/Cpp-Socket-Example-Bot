

#define _USE_MATH_DEFINES
#include <math.h>

#include <ctime>
#include "Agent.h"

using namespace rlbot;

ControllerState Agent::process(const GameTickPacket & packet)
{
  ControllerState controller;

  Vec3 ball_loc = packet.getBall().getPhysics().getLocation();
  
  Physics car_phys = packet.getCar(m_index).physics();

  Vec3 car_loc = car_phys.getLocation();

  Vec3 car_to_ball = ball_loc - car_loc;

  float target_angle = car_to_ball.angle();

  float current_angle = car_phys.getRotation().getYaw();

  float da = target_angle - current_angle;

  while(da > M_PI)
    da -= M_PI * 2.0;
  while(da < -M_PI)
    da += M_PI * 2.0;
  
  controller.withSteer(da * 3.0).withThrottle(1).withBoost(car_to_ball.mag() > 1000.0)
    .withHandbrake(abs(da) > M_PI * 0.7);

  m_renderer.beginDraw();
  m_renderer.setColor(255, 0, 0);
  m_renderer.line3D(ball_loc, car_loc);
  m_renderer.string3D("HELLO WORLD!", car_loc + Vec3(0, 0, 100));

  // m_ball_prediction.draw(m_renderer, 10);

  m_renderer.flush();

  // Simple for testing purposes.
  return controller;
}
