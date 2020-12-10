

#include <cmath>
#include "Vec3.h"
using namespace rlbot;

float Vec3::dot(const Vec3 & a, const Vec3 & b)
{
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

float Vec3::mag() const
{
  return sqrt(x * x + y * y + z * z);
}

float Vec3::angle() const
{
  return atan2(y, x);
}

// Todo: Check handedness of this function
Vec3 Vec3::cross(const Vec3 & a, const Vec3 & b)
{
  return Vec3(
    a.y * b.z - a.z * b.y,
    a.z * b.x - a.x * b.z,
    a.x * b.y - a.y * b.x
  );
}

Vec3 & Vec3::operator+=(const Vec3 & rhs)
{
  x += rhs.x;
  y += rhs.y;
  z += rhs.z;

  return (*this);
}

Vec3 & Vec3::operator-=(const Vec3 & rhs)
{
  x -= rhs.x;
  y -= rhs.y;
  z -= rhs.z;

  return (*this);
}

Vec3 rlbot::operator+(const Vec3 & a, const Vec3 & b)
{
  Vec3 result(a);
  return result += b;
}

Vec3 rlbot::operator-(const Vec3 & a, const Vec3 & b)
{
  Vec3 result(a);
  return result -= b;
}

flat::Vector3 Vec3::__construct_flat() const
{
  return flat::Vector3(x, y, z);
}

