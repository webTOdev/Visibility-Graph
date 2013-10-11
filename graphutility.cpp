/*
 * graphutility.cpp
 *
 *  Created on: Oct 3, 2013
 *      Author: nut
 */

#include "graphutility.h"

double vectorsAngle( double x, double y, double basex, double basey)
{
	// Convert input point x & y to be vectors relative to base point
	double x2 = double(x - basex);
	double y2 = double(y - basey);


	double result=std::atan2(y2,x2);
	//std::cout << "Result: " << result <<" at point "<<basex<<","<<basey<< std::endl;
	if( result == 0 && x<basex) //At same line and  origin to the left
	{
			result = -M_PI;

	}
	if( result == M_PI) //At same line and to the right
		{
				result = -M_PI;

		}



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

		if (angle < sweepPointTheta && !(angle < 0 && sweepPointTheta > 0)) {
		    // is going counter clockwise
			clockwise=false;
		} else {
		    // is going clockwise
			clockwise=true;
		}
	return clockwise;

}

//Checks whether the 3 points represents a straight line
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
void fileWrite(Point* a,Point* b){

	double dist = distance(a,b);
	FILE *fp;
	fp=fopen("test.txt", "a");
	fprintf(fp, "%d" , a->id);
	fprintf(fp, " %d" , b->id);
	fprintf(fp, " %f" , dist);
	fprintf(fp, "\n");
	fclose(fp);
}




