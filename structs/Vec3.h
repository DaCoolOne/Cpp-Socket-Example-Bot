

#ifndef STRUCTS_VEC3_H
#define STRUCTS_VEC3_H

#include <iostream>

#include "../flatbuffers/rlbot_generated.h"

namespace rlbot {

struct Vec3
{
  float x;
  float y;
  float z;

  Vec3(const float _x = 0, const float _y = 0, const float _z = 0):
    x(_x), y(_y), z(_z) { }
  
  Vec3(const flat::Vector3 * const vec): x(vec->x()), y(vec->y()), z(vec->z()) { }

  float angle() const;

  float mag() const;

  static float dot(const Vec3 & a, const Vec3 & b);
  static Vec3 cross(const Vec3 & a, const Vec3 & b);

  flat::Vector3 __construct_flat() const;

  void update(const flat::Vector3 * const vector);

  Vec3 & operator+=(const Vec3 & rhs);
  Vec3 & operator-=(const Vec3 & rhs);

  friend std::ostream& operator<< (std::ostream & out, const Vec3 & vec)
  {
    out << "Vec3(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return out;
  }
};

Vec3 operator+(const Vec3 & a, const Vec3 & b);
Vec3 operator-(const Vec3 & a, const Vec3 & b);

}

#endif