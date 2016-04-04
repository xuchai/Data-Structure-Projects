// =========================================
//
//  IMPORTANT NOTE: DO NOT EDIT THIS FILE
//
// =========================================

#ifndef _UTILITIES_H_
#define _UTILITIES_H_

#include <iostream>
#include <cmath>
#include <cassert>

// epsilon values used in comparing the edge lengths & angles between
// edges note that these values are dependent on the precision of
// the coordinates and the overall scale of the objects
#define DISTANCE_EPSILON 0.0001
#define ANGLE_EPSILON 0.1

// -----------------------------------------------------------------

// Stores a 2D coordinate
class Point {
public:
  Point(double _x, double _y) : x(_x),y(_y) {}
  double x;
  double y;
};

// Stores a 2D vector, constructed from 2 Points
class Vector {
public:
  Vector(const Point &a, const Point &b) { dx = b.x-a.x; dy = b.y-a.y; }
  double Length() { return sqrt(dx*dx+dy*dy); }
  void Normalize() {
    // make this a unit vector (length = 1)
    double length = Length();
    if (length < DISTANCE_EPSILON) throw std::string("LENGTH = 0");
    assert (length > DISTANCE_EPSILON);
    dx /= length;
    dy /= length;
  }
  // representation
  double dx;
  double dy;
};


inline std::ostream& operator<< (std::ostream &ostr, const Vector &v) {
  ostr << "<" << v.dx << "," << v.dy << ">";
  return ostr;
}


// -----------------------------------------------------------------

// calculate the length of an edge, the distance between 2 points
inline double DistanceBetween(const Point &a, const Point &b) { 
  Vector v(a,b);
  return v.Length();
}

// Calculate the angle at vertex b in degrees, that is, the angle
// between edges ab and bc.  This will return a positive number
// measured as the clockwise rotation in the xy plane from point c to
// point a (rotating around point b).
inline double Angle(const Point &a, const Point &b, const Point &c) {
  // make unit vector along each of the edges
  Vector ba(b,a);  ba.Normalize();
  Vector bc(b,c);  bc.Normalize();
  // calculate the angle in radians
  double dot_product = ba.dx * bc.dx + ba.dy * bc.dy;

  if (dot_product < -1 || dot_product > 1) throw std::string("DOT PRODUCT RANGE");

  assert (dot_product >= -1 && dot_product <= 1);
  float perpDot = ba.dx * bc.dy - ba.dy * bc.dx;
  // using atan2 to ensure than we get a signed answer.
  double angle_in_radians = atan2(perpDot, dot_product);
  // convert to degrees
  double answer = angle_in_radians * 180.0 / M_PI;
  if (answer < 0) {
    answer += 360;
  }
  assert (answer >= 0 && answer <= 360);
  return answer;
}

// returns true if these two vectors are parallel
inline bool Parallel(const Vector &a, const Vector &b) {
  Vector a2 = a; a2.Normalize();
  Vector b2 = b; b2.Normalize();
  double dot_product = a2.dx * b2.dx + a2.dy * b2.dy;
  // parallel vectors have dot product == 1
  if (fabs(dot_product) > 1-DISTANCE_EPSILON) return true;
  return false;
}


// -----------------------------------------------------------------
// simple comparison functions for angles & sides

inline bool EqualSides(double a, double b) {
  return (fabs(a-b) < DISTANCE_EPSILON);
}

inline bool EqualAngles(double a, double b) {
  assert (a >= 0.0 && a < 360.0);
  assert (b >= 0.0 && b < 360.0);
  return (fabs(a-b) < ANGLE_EPSILON);
}

// -----------------------------------------------------------------
// categorizing angles

inline bool AcuteAngle(double a) {
  assert (a >= 0.0 && a < 360.0);
  return (a < 90.0 - ANGLE_EPSILON);
}

inline bool RightAngle(double a) {
  assert (a >= 0.0 && a < 360.0);
  return (fabs(a-90.0)  < ANGLE_EPSILON);
}

inline bool ObtuseAngle(double a) {
  assert (a >= 0.0 && a < 360.0);
  return (a > 90.0+ANGLE_EPSILON && a < 180.0-ANGLE_EPSILON);
}

inline bool ReflexAngle(double a) {
  assert (a >= 0.0 && a < 360.0);
  return (a > 180.0+ANGLE_EPSILON);
}

// -----------------------------------------------------------------

#endif
