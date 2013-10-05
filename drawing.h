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
#include <cstring>

using namespace cimg_library;
using namespace std;


CImg<unsigned char> img(screen_size,screen_size,1,3,20);
CImgDisplay disp(img, "Obstacle Shortest Path Using Visibility Graph");      // Display the modified image on the screen

void drawPolygon(CImg<double> points){

	img.draw_polygon(points,GREY,0.4);
	disp.display(img);

}
void drawCircle(double x,double y){
	img.draw_circle(x, y, 1.5, WHITE);
	disp.display(img);
}

void drawText(double x,double y,int id){
	char result[100];
	itoa(id,result,10); //itoa(int num,char * buffer,10)
	img.draw_text((x-3)*scale, (y-15)*scale,result,WHITE);
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
void drawEdge(Line* a){

	img.draw_line(a->a->x,a->a->y,a->b->x,a->b->y,BLUE);

	disp.display(img);


}


#endif /* DRAWING_H_ */

