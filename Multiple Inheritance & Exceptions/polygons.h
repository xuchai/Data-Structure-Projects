#include <iostream>
#include "utilities.h"
#include "my_utilities.h"
#include <string>
#include <vector>

using namespace std;

class Polygon{
public:
    // constructor
    Polygon(const std::string & name, const std::vector<Point> & points): name_(name), points_(points){
        if (points.size() < 3) throw -1;
        if (!is_polygon(points)) throw -1;
    };
    // accessor
    std::string getName(){return name_;}
    // equity
    virtual bool HasAllEqualSides();
    virtual bool HasAllEqualAngles();
    // angle
    virtual bool HasARightAngle();
    virtual bool HasAnObtuseAngle();
    virtual bool HasAnAcuteAngle();
    // concavity
    virtual bool IsConvex();
    virtual bool IsConcave();
    // destructure
    virtual ~Polygon(){}
protected:
    std::string name_;
    std::vector<Point> points_;
};

//-------------------------------------------------
// Triangles
//-------------------------------------------------
//
class Triangle : public Polygon {
public:
    Triangle(const std::string & name, const std::vector<Point> &points) : Polygon(name, points){
        if (points.size() != 3) throw -1;
    }
    virtual bool HasAnAcuteAngle() {return true;}
    virtual bool IsConvex() {return true;}
    virtual bool IsConcave() {return false;}
};

class IsoscelesTriangle : virtual public Triangle{
public:
    IsoscelesTriangle(const std::string & name, const std::vector<Point> & points) : Triangle(name, points){
        if (points.size() != 3) throw -1; // do we still need this? will try later!
        if (!is_isosceles_triangle(points)) throw -1;
    }
};

class RightTriangle : virtual public Triangle{
public:
    RightTriangle(const std::string & name, const std::vector<Point> & points) : Triangle(name, points){
        if (points.size()!=3) throw -1; // do we still need this? will try later!
        if (!is_right_triangle(points)) throw -1;
    }
    virtual bool HasARightAngle() {return true;}
    virtual bool HasAnObtuseAngle() {return false;}
    virtual bool HasAllEqualSides() {return false;}
    virtual bool HasAllEqualAngles() {return false;}
};

class IsoscelesRightTriangle : public IsoscelesTriangle, public RightTriangle{
public:
    IsoscelesRightTriangle(const std::string &name, const std::vector<Point> &points)
    : Triangle(name, points), IsoscelesTriangle(name, points), RightTriangle(name, points){
        if (points.size() != 3) throw -1; // do we still need this? will try later!
        if (!is_isosceles_triangle(points)) throw -1;
        if (!is_right_triangle(points)) throw -1;
    }
};

class ObtuseTriangle : virtual public Triangle{
public:
    ObtuseTriangle(const std::string & name, const std::vector<Point> & points) : Triangle(name, points){
        if (points.size() != 3) throw -1; // do we still need this? will try later!
        if (!is_obtuse_triangle(points)) throw -1;
    }
    virtual bool HasAnObtuseAngle() {return true;}
    virtual bool HasARightAngle() {return false;}
    virtual bool HasAllEqualSides() {return false;}
    virtual bool HasAllEqualAngles() {return false;}
};

class IsoscelesObtuseTriangle : public IsoscelesTriangle, public ObtuseTriangle{
public:
    IsoscelesObtuseTriangle(const std::string &name, const std::vector<Point> &points)
    : Triangle(name, points), IsoscelesTriangle(name, points), ObtuseTriangle(name, points){
        if (points.size() != 3) throw -1; // do we still need this? will try later!
        if (!is_isosceles_triangle(points)) throw -1;
        if (!is_obtuse_triangle(points)) throw -1;
    }
};

class EquilateralTriangle : public IsoscelesTriangle{
public:
    EquilateralTriangle(const std::string &name, const std::vector<Point> &points)
    : Triangle(name, points), IsoscelesTriangle(name, points){
        if (points.size() != 3) throw -1;
        if (!is_isosceles_triangle(points)) throw -1;
        if (!all_angles_equal(points)) throw -1;
        
    }
    virtual bool HasAllEqualSides() {return true;}
    virtual bool HasAllEqualAngles() {return true;}
    virtual bool HasARightAngle() {return false;}
    virtual bool HasAnObtuseAngle() {return false;}
};

//------------------------------------------------
// Quadrilaterals
//-------------------------------------------------
//
class Quadrilateral : public Polygon{
public:
    Quadrilateral(const std::string &name, const std::vector<Point> &points) : Polygon(name, points){
        if (points.size() != 4) throw -1;
    }
};

class Trapezoid : virtual public Quadrilateral{
public:
    Trapezoid(const std::string &name, const std::vector<Point> &points) : Quadrilateral(name, points){
        if (points.size() != 4) throw -1;
        if (!is_trapezoid(points)) throw -1;
    }
    virtual bool IsConvex() {return true;}
    virtual bool IsConcave() {return false;}
};

class Kite : virtual public Quadrilateral{
public:
    Kite(const std::string &name, const std::vector<Point> &points): Quadrilateral(name, points) {
        if (points.size() != 4) throw -1;
        if (!is_kite(points)) throw -1;
    }
    virtual bool IsConvex() {return true;}
    virtual bool IsConcave() {return false;}
};

class Arrow : public Quadrilateral{
public:
    Arrow(const std::string &name, const std::vector<Point> &points): Quadrilateral(name, points){
        if (points.size() != 4) throw -1;
        if (!is_arrow(points)) throw -1;
    }
    virtual bool IsConvex() {return false;}
    virtual bool IsConcave() {return true;}
};

class Parallelogram : virtual public Trapezoid{
public:
    Parallelogram(const std::string &name, const std::vector<Point> &points)
    : Quadrilateral(name, points), Trapezoid(name, points){
        if (points.size() != 4) throw -1;
        if(!is_parallelogram(points)) throw -1;
    }
};

class IsoscelesTrapezoid : virtual public Trapezoid{
public:
    IsoscelesTrapezoid(const std::string &name, const std::vector<Point> &points)
    : Quadrilateral(name, points), Trapezoid(name, points){
        if (points.size() != 4) throw -1;
        if (!is_isosceles_trapezoid(points)) throw -1;
    }
};

class Rhombus : public Kite, virtual public Parallelogram{
public:
    Rhombus(const std::string &name, const std::vector<Point> &points)
    : Quadrilateral(name, points), Trapezoid(name, points),
    Parallelogram(name, points), Kite(name,points){
        if (points.size() != 4) throw -1;
        if (!HasAllEqualSides()) throw -1;
    }
    virtual bool HasAllEqualSides() {return true;}
    virtual bool IsConvex() {return true;}
    virtual bool IsConcave() {return false;}
};

class Rectangle : public IsoscelesTrapezoid, virtual public Parallelogram{
public:
    Rectangle(const std::string &name, const std::vector<Point> &points)
    : Quadrilateral(name, points), Trapezoid(name, points),
    Parallelogram(name, points), IsoscelesTrapezoid(name, points){
        if (points.size() != 4) throw -1;
        if (!is_rectangle(points)) throw -1;
    }
    virtual bool HasARightAngle(){return true;}
    virtual bool HasAnAcuteAngle(){return false;}
    virtual bool HasAnObtuseAngle(){return false;}
    virtual bool HasAllEqualAngles(){return true;}
};

class Square : public Rectangle, public Rhombus{
public:
    Square(const std::string &name, const std::vector<Point> &points)
    : Quadrilateral(name, points), Trapezoid(name,points), Parallelogram(name, points),
    Rhombus(name, points), Rectangle(name, points){
        if(points.size() != 4) throw -1;
        if (!HasAllEqualSides()) throw -1;
        if (!HasAllEqualSides()) throw -1;
    }
};


