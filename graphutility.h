/*
 * graphutility.h
 *
 *  Created on: Oct 3, 2013
 *      Author: nut
 */

#ifndef GRAPHUTILITY_H_
#define GRAPHUTILITY_H_
#include <vector>
#include "point.h"
#include "pointHandler.h"
#include <cmath>
#include <iostream>

/*  Calculate Angle Btw 2 Vectors
 *Turning the points in to vector by x=basex-x and y = basey-y and then angle = arctan(y/x);
*/
double vectorsAngle( double x, double y, double basex, double basey);
bool isRotationClockwise(Point* a,Point* b,Point* c);
//Point* findPointById(vector<Point*> points,int itemToFind);
bool checkCoLinear(Point* a,Point* b,Point* c);
double angleBetweenThreePoint(double x1,double y1,double x2,double y2,double x3,double y3);
bool isClockwise(Point* sweepPoint,Point* b);
bool isLeft(Point* a, Point* b, Point* c);
void fileWrite(Point *a,Point *b);

#endif /* GRAPHUTILITY_H_ */
