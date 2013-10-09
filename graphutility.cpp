/*
 * graphutility.cpp
 *
 *  Created on: Oct 3, 2013
 *      Author: nut
 */

#include "graphutility.h"
#include <cmath>
#include <iostream>

double vectorsAngle( double x, double y, double basex, double basey)
{
	// Convert input point x & y to be vectors relative to base point
	double x2 = double(x - basex);
	double y2 = double(y - basey);
/*
	// Hard code scan line to point right:
	double x1 = sqrt( x2*x2 + y2*y2 ); // make it with ratio?
	double y1 = 0.0;

	//cout << "x1: " << x1 << " - y1: " << y1 << endl;
	//cout << "x2: " << x2 << " - y2: " << y2 << endl;

	double stuff = (  (x1*x2)+(y1*y2)   ) / (  sqrt(x1*x1+y1*y1)  *  sqrt(x2*x2+y2*y2) );
	//cout << "Stuff: " << stuff << endl;

	// Calculate angle:
	double result = acos( stuff );
	//cout << "Result: " << result << endl;

	// Now add PI if below middle line:
	if( y >= basey ){
		result = 2*M_PI - result;
	}

	//cout << "Result: " << result*180/M_PI << " degrees" << endl;

	 */
	double result=std::atan2(y2,x2);
	//std::cout << "Result: " << result << std::endl;

	return result;
}

bool isRotationClockwise(Point* a,Point* b,Point* c){
	//Sum over the edges, (x2-x1)(y2+y1). If the result is positive the curve is clockwise
	double x1=a->x;
	double y1=a->y;
	double x2=b->x;
	double y2=b->y;
	double x3=c->x;
	double y3=c->y;

	double s1=(x2-x1)*(y2+y1);
	double s2=(x3-x2)*(y3+y2);
	double s3=(x1-x3)*(y1+y3);

	double sum=s1+s2+s3;
	bool clockwise=false;
	if(sum>0)
		clockwise=true;
	return clockwise;

}

bool isClockwise(Point* sweepPoint,Point* b){
	//Sum over the edges, (x2-x1)(y2+y1). If the result is positive the curve is clockwise
	double sweepPointTheta = sweepPoint->theta;
	double angle=b->theta;

	std::cout<<"Sweep theta "<<sweepPointTheta<<" and Point "<<b->id<<" theta "<<angle<<std::endl;
	bool clockwise=false;
	/*
	 * if at clockwise then the theta with horizontal X axis will be greater
	 * if sweepPoint is below b then just opposite that is theta wil X axis is smaller
	 *
	 */

	/*	if(angle>sweepPointTheta)
			clockwise=true;
			*/

		if (angle < sweepPointTheta && !(angle < 0 && sweepPointTheta > 0)) {
		    // is going counter clockwise
			clockwise=false;
		} else {
		    // is going clockwise
			clockwise=true;
		}
	return clockwise;

}

bool checkCoLinear(Point* a,Point* b,Point* c){
	//Sum over the edges, (x2-x1)(y2+y1). If the result is positive the curve is clockwise
	double x1=a->x;
	double y1=a->y;
	double x2=b->x;
	double y2=b->y;
	double x3=c->x;
	double y3=c->y;

	double s1=(y1-y2)/(x1-x2);
	double s2=(y2-y3)/(x2-x3);


	bool colinear=false;
	if(s1 == s2 )
		colinear=true;
	return colinear;

}

double angleBetweenThreePoint(double x1,double y1,double x2,double y2,double x3,double y3){
	float dx21 = x2-x1;
	float dx31 = x3-x1;
	float dy21 = y2-y1;
	float dy31 = y3-y1;
	float m12 = sqrt( dx21*dx21 + dy21*dy21 );
	float m13 = sqrt( dx31*dx31 + dy31*dy31 );
	float theta = acos( (dx21*dx31 + dy21*dy31) / (m12 * m13) );

	return theta;
}

bool isLeft(Point* a, Point* b, Point* c){
     return ((b->x - a->x)*(c->y - a->y) - (b->y - a->y)*(c->x - a->x)) > 0;
}



