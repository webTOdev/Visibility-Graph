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



