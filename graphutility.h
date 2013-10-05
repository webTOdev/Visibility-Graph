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

//-------------------------------------------------------------------------------
//  Calculate Angle Btw 2 Vectors
//Turning the points in to vector by x=basex-x and y = basey-y and then angle = arctan(y/x);
//-------------------------------------------------------------------------------
double vectorsAngle( double x, double y, double basex, double basey);
bool isRotationClockwise(Point* a,Point* b,Point* c);
//Point* findPointById(vector<Point*> points,int itemToFind);
bool checkCoLinear(Point* a,Point* b,Point* c);

#endif /* GRAPHUTILITY_H_ */
