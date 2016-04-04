#ifndef _MY_UTILITIES_H_
#define _MY_UTILITIES_H_

#include <iostream>
#include <cmath>
#include <cassert>
#include <string>
#include <vector>
#include "utilities.h"
using namespace std;

/* This header file contains the utility functions for distinguishing different shapes */

#define DISTANCE_EPSILON 0.0001
#define ANGLE_EPSILON 0.1

//-------------------------------------------------
// check if it is a polygon
//-------------------------------------------------
inline bool is_polygon(const vector<Point> &points) {
    // check to see if these points are in a same line
    double angle1 = Angle(points[points.size() - 1], points[0], points[1]);
    double angle2 = Angle(points[points.size() - 2],points[points.size() - 1], points[0]);
    if (EqualAngles(angle1, 180.0) || EqualAngles(angle1, 0.0) ||
        EqualAngles(angle2, 180.0)   || EqualAngles(angle2, 0.0))
        return false;
    for(int i = 0; i < points.size() - 2; ++i){
        double tmp_angle = Angle(points[i], points[i + 1], points[i + 2]);
        if (EqualAngles(tmp_angle, 180.0) || EqualAngles(tmp_angle, 0.0))
            return false;
    }
    return true;
}

//-------------------------------------------------
// check if all edges are equal or angles are equal
//-------------------------------------------------
inline bool all_edges_equal(const std::vector<Point> &points){
    Vector base_vec(points[points.size() - 1], points[0]);
    for(int i = 0; i < points.size()-1; ++i){
        Vector tmp_vec(points[i], points[i + 1]);
        if (!EqualSides(base_vec.Length(), tmp_vec.Length()))
            return false;
    }
    return true;
}

inline bool all_angles_equal(const std::vector<Point> &points){
    double angle1 = Angle(points[points.size() - 1], points[0], points[1]);
    double angle2 = Angle(points[points.size() - 2], points[points.size() - 1], points[0]);
    if (!EqualAngles(angle1, angle2))
        return false;
    for(int i = 0; i < points.size()-2; ++i){
        double tmp_angle = Angle(points[i], points[i + 1], points[i + 2]);
        if (!EqualAngles(angle1, tmp_angle))
            return false;
    }
    return true;
}

//-------------------------------------------------
// check different shapes of triangles
//-------------------------------------------------

inline bool is_isosceles_triangle(const std::vector<Point> &points){
    assert(points.size()==3);
    double angle1 = Angle(points[0], points[1], points[2]);
    double angle2 = Angle(points[1], points[2], points[0]);
    double angle3 = Angle(points[2], points[0], points[1]);
    if (EqualAngles(angle1, angle2) || EqualAngles(angle2, angle3) ||
        EqualAngles(angle3, angle1))
        return true;
    return false;
}

inline bool is_right_triangle(const std::vector<Point> &points){
    assert(points.size()==3);
    double angle1 = Angle(points[0], points[1], points[2]);
    double angle2 = Angle(points[1], points[2], points[0]);
    double angle3 = Angle(points[2], points[0], points[1]);
    if (RightAngle(angle1) || RightAngle(angle2) || RightAngle(angle3))
        return true;
    return false;
}

inline bool is_obtuse_triangle(const std::vector<Point> &points){
    assert(points.size()==3);
    double angle1 = Angle(points[0], points[1], points[2]);
    double angle2 = Angle(points[1], points[2], points[0]);
    double angle3 = Angle(points[2], points[0], points[1]);
    if (ObtuseAngle(angle1) || ObtuseAngle(angle2) || ObtuseAngle(angle3))
        return true;
    return false;
}

//-------------------------------------------------
// check different shapes of Quadrilaterals
//-------------------------------------------------

inline bool is_trapezoid(const std::vector<Point> &points){
    Vector edge1(points[0],points[1]);
    Vector edge2(points[1],points[2]);
    Vector edge3(points[2],points[3]);
    Vector edge4(points[3],points[0]);
    if(Parallel(edge1, edge3) || Parallel(edge2, edge4))
        return true;
    return false;
}

inline bool is_parallelogram(const std::vector<Point> &points){
    Vector edge1(points[0],points[1]);
    Vector edge2(points[1],points[2]);
    Vector edge3(points[2],points[3]);
    Vector edge4(points[3],points[0]);
    if (!Parallel(edge1, edge3) || !Parallel(edge2, edge4))
        return false;
    return true;
}

inline bool is_rectangle(const std::vector<Point> &points){
    double angle1 = Angle(points[0], points[1], points[2]);
    double angle2 = Angle(points[1], points[2], points[3]);
    double angle3 = Angle(points[2], points[3], points[0]);
    double angle4 = Angle(points[3], points[0], points[1]);
    if (!RightAngle(angle1) || !RightAngle(angle2) ||
        !RightAngle(angle3) || !RightAngle(angle4))
        return false;
    return true;
}

inline bool is_isosceles_trapezoid(const std::vector<Point> &points){
    if (!is_trapezoid(points)) return false;
    Vector edge1(points[0],points[1]);
    Vector edge2(points[1],points[2]);
    Vector edge3(points[2],points[3]);
    Vector edge4(points[3],points[0]);
    bool isIsosceles = false;
    if (Parallel(edge1, edge3)){
        double angle1 = Angle(points[3], points[0], points[1]);
        double angle2 = Angle(points[0], points[1], points[2]);
        if (EqualAngles(angle1, angle2))
            isIsosceles = true;
    } else if (Parallel(edge2, edge4)){
        double angle2 = Angle(points[0], points[1], points[2]);
        double angle3 = Angle(points[1], points[2], points[3]);
        if (EqualAngles(angle2, angle3))
            isIsosceles = true;
    }
    return isIsosceles;
}

inline bool is_kite(const std::vector<Point> &points){
    bool convexity = true;
    bool edgeEqual = false;
    // first check if it is convex
    int size = points.size();
    double angle1 = Angle(points[size - 1], points[0], points[1]);
    double angle2 = Angle(points[size - 2],points[size - 1], points[0]);
    if (ReflexAngle(angle1) || ReflexAngle(angle2))
        convexity = false;
    else {
        for(int i = 0; i < size - 2; ++i){
            double tmp_angle = Angle(points[i], points[i + 1], points[i + 2]);
            if (ReflexAngle(tmp_angle))
            convexity = false;
        }
    }
    // then check two pairs of equal edges
    if (convexity) {
        Vector edge1(points[0],points[1]);
        Vector edge2(points[1],points[2]);
        Vector edge3(points[2],points[3]);
        Vector edge4(points[3],points[0]);
        if (EqualSides(edge1.Length(), edge2.Length())){
            if (EqualSides(edge3.Length(), edge4.Length()))
            edgeEqual = true;
        } else if (EqualSides(edge2.Length(), edge3.Length())){
            if (EqualSides(edge1.Length(), edge4.Length()))
                edgeEqual = true;
        }
    }
    return convexity && edgeEqual;
}

inline bool is_arrow(const std::vector<Point> &points){
    // first check if it is concave
    bool concavity = false;
    bool edgeEqual = false;
    int size = points.size();
    double angle1 = Angle(points[size - 1], points[0], points[1]);
    double angle2 = Angle(points[size - 2],points[size - 1], points[0]);
    if (ReflexAngle(angle1) || ReflexAngle(angle2))
        concavity =  true;
    else {
        for(int i = 0; i < size - 2; ++i){
        double tmp_angle = Angle(points[i], points[i + 1], points[i + 2]);
        if (ReflexAngle(tmp_angle))
            concavity = true;
        }
    }
    // check two pairs of equal edges
    if (concavity) {
        Vector edge1(points[0],points[1]);
        Vector edge2(points[1],points[2]);
        Vector edge3(points[2],points[3]);
        Vector edge4(points[3],points[0]);
        if (EqualSides(edge1.Length(), edge2.Length())){
            if (EqualSides(edge3.Length(), edge4.Length()))
                edgeEqual = true;;
        } else if (EqualSides(edge2.Length(), edge3.Length()) && EqualSides(edge4.Length(), edge1.Length()))
            edgeEqual = true;
    }
    return concavity && edgeEqual;
}

#endif
