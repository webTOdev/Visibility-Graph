#ifndef LINE_H_INCLUDED
#define LINE_H_INCLUDED

#include <iostream>
#include "point.h"
#include "geometry.h"
#include <cmath>
#include <cstdlib>
#include "boostHelper.h"

class Line: public Geometry
{
 public:
	Point * a;
    Point * b;

	bool visitedStartPoint; // has the base/sweep line crossed at least one of
	              // the verticies? 
	bool visited;  // has the sweep line been on the line (as in, maybe it was init on it)

	int id;
	long double dist; // distance from center
	double theta_cache; // used for deciding if the dist cache needs to be refreshed
	double m; // slope of line
	double y_intercept; // y-intercept of line
	
	Line();
	Line(double _x1, double _y1, double _x2, double _y2);
	Line(Point* p1,Point* p2);

	~Line();
	virtual void print();
    virtual double value();

	void updateCalcs();
	void distance();
	void center_intercept(double &xi, double &yi);
};


// This global needs to be visible to classes:
extern Point * center;
extern Line * center_line;
extern double atomic;
extern double atomic_space;

#endif
