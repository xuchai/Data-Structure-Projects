//
//  polygons.cpp
//  hw10_prictise
//
//  Created by Chelsey on 15-5-6.
//  Copyright (c) 2015年 Chelsey. All rights reserved.
//

#include <iostream>
#include "polygons.h"

using namespace std;

// equalities
bool Polygon::HasAllEqualSides(){
    Vector base_vec(points_[points_.size() - 1], points_[0]);
    for(int i = 0; i < points_.size()-1; ++i){
        Vector tmp_vec(points_[i], points_[i + 1]);
        if (!EqualSides(base_vec.Length(), tmp_vec.Length()))
            return false;
    }
    return true;
}
bool Polygon::HasAllEqualAngles(){
    double angle1 = Angle(points_[points_.size() - 1], points_[0], points_[1]);
    double angle2 = Angle(points_[points_.size() - 2], points_[points_.size() - 1], points_[0]);
    if (!EqualAngles(angle1, angle2))
        return false;
    for(int i = 0; i < points_.size()-2; ++i){
        double tmp_angle = Angle(points_[i], points_[i + 1], points_[i + 2]);
        if (!EqualAngles(angle1, tmp_angle))
            return false;
    }
    return true;
}

// angles
bool Polygon::HasARightAngle(){
    double angle1 = Angle(points_[points_.size() - 1], points_[0], points_[1]);
    double angle2 = Angle(points_[points_.size() - 2], points_[points_.size() - 1], points_[0]);
    if (RightAngle(angle1) || RightAngle(angle2))
        return true;
    for(int i = 0; i < points_.size() - 2; ++i){
        double tmp_angle = Angle(points_[i], points_[i + 1], points_[i + 2]);
        if (RightAngle(tmp_angle))
            return true;
    }
    return false;
}

bool Polygon::HasAnObtuseAngle(){
    double angle1 = Angle(points_[points_.size() - 1], points_[0], points_[1]);
    double angle2 = Angle(points_[points_.size() - 2], points_[points_.size() - 1], points_[0]);
    if (ObtuseAngle(angle1) || ObtuseAngle(angle2))
        return true;
    for(int i = 0; i < points_.size()-2; ++i){
        double tmp_angle = Angle(points_[i], points_[i + 1], points_[i + 2]);
        if (ObtuseAngle(tmp_angle))
            return true;
    }
    return false;
}

bool Polygon::HasAnAcuteAngle(){
    double angle1 = Angle(points_[points_.size() - 1], points_[0], points_[1]);
    double angle2 = Angle(points_[points_.size() - 2], points_[points_.size() - 1], points_[0]);
    if (AcuteAngle(angle1) || AcuteAngle(angle2))
        return true;
    for(int i = 0; i < points_.size()-2; ++i){
        double tmp_angle = Angle(points_[i], points_[i + 1], points_[i + 2]);
        if (AcuteAngle(tmp_angle))
            return true;
    }
    return false;
}

// concavity
bool Polygon::IsConcave(){
    double angle1 = Angle(points_[points_.size() - 1], points_[0], points_[1]);
    double angle2 = Angle(points_[points_.size() - 2], points_[points_.size() - 1], points_[0]);
    if (ReflexAngle(angle1) || ReflexAngle(angle2))
        return true;
    for(int i = 0; i < points_.size()-2; ++i){
        double tmp_angle = Angle(points_[i], points_[i + 1], points_[i + 2]);
        if (ReflexAngle(tmp_angle))
            return true;
    }
    return false;
}

bool Polygon::IsConvex(){
    return (!IsConcave());
}

