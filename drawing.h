/*
 * drawing.h
 *
 *  Created on: Sep 20, 2013
 *      Author: nut
 */

#ifndef DRAWING_H_
#define DRAWING_H_

#include "CImg.h"// Include CImg library header.
#include "utility.h"
using namespace cimg_library;
using namespace std;

CImg<unsigned char> img(screen_size,screen_size,1,3,20);
CImgDisplay disp(img, "Obstacle Shortest Path Using Visibility Graph");      // Display the modified image on the screen

void drawPolygon(CImg<double> points){

	img.draw_polygon(points,RED,1);

	disp.display(img);


}

void showPolygon(){

	while (!disp.is_closed()) {
							if (disp.is_keyESC() )
								break;
							disp.wait();
				}
				img.save("r-tree.bmp"); // save the image


}

void drawLine(double x1,double y1,double x2,double y2){

	img.draw_line(x1,y1,x2,y2,GREEN);

	disp.display(img);


}


#endif /* DRAWING_H_ */

