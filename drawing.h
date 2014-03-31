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

unsigned int flip_y( unsigned int y, unsigned int height ) {
    return height - y;
}
void drawPolygon(CImg<double> points){

	img.draw_polygon(points,GREY,0.4);
	disp.display(img);

}
void drawCircle(double x,double y,int radius,const unsigned char color[]){
	img.draw_circle(x*scale, y*scale, radius, color);
	disp.display(img);
}

void drawText(double x,double y,int id,const unsigned char color[]){
	char result[100];
	itoa(id,result,10); //itoa(int num,char * buffer,10)
	img.draw_text((x-3)*scale, (y-15)*scale,result,color);
	disp.display(img);
}

void writeText(double x,double y,char text[],const unsigned char color[]){

	img.draw_text((x-3)*scale, (y-15)*scale,text,color);
	disp.display(img);
}

void displayImage() {

	while (!disp.is_closed()) {
		if (disp.is_keyESC())
			break;
		disp.wait();
	}
	img.save("r-tree.bmp"); // save the image

}

void drawLine(double x1,double y1,double x2,double y2,const unsigned char color[]){

	img.draw_line(x1*scale,y1*scale,x2*scale,y2*scale,color);

	disp.display(img);


}
void drawEdge(Line* a,const unsigned char color[]){

	img.draw_line(a->a->x*scale,a->a->y*scale,a->b->x*scale,a->b->y*scale,color);

	disp.display(img);
}




#endif /* DRAWING_H_ */

