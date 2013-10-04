#include "point.h"


Point::Point()
{

}
Point::Point(double _x1, double _y1)
{
	x = _x1;
	y = _y1;
	p=tPoint(x,y);
	static int id_counter = 0;
	id = id_counter++;
	index=0;
	Point();
	//std::cout << "Constructing Point x: " << x << " y: " << y << " \t ID: " << id << " index " << index  <<std::endl;

}
void Point::print()
{
	std::cout << "Point x: " << x << " y: " << y << " \t ID: " << id << std::endl;
}
double Point::value()
{
	// this is the angular distance from the base line
	// for point.cpp, we just cache the initial calculation
	return theta;
}
void Point::printVisible()
{
	for(int i=0;i<index;i++){
		if(visible[i]!=NULL){
				std::cout << "Point " << id << " \t can see Point " << visible[i]->id  << std::endl;
		}
	}
}
void Point::addVisible(Point *p)
{

	//std::cout << "At " << x <<"," << y <<"   for  " << p->x <<","<<p->y <<" Index "<<index<<std::endl;
	visible[index]=p;
	index++;
}
/* This function will check whether that Point p is visible to t
*/
bool Point::isVisible(Point* p)
{
      // std::cout<<"Testing is visible "<<id<<" "<<p->id;
       bool found=false;
       for(int i=0;i<index;i++){
              if(visible[i]!=NULL){
                       {
                               if(visible[i]->id == p->id){
                                       found=true;
                                       break;
                       }
               }

               }
       }
      // std::cout<<" Found : "<<found<<std::endl;
       return found;
}

void Point::removeVisible(Point *p)
{
       int i;

       for(i=0;i<index;i++){
                       if(visible[i]!=NULL){
                               if(visible[i]->id == p->id){
                                       visible[i]=NULL;
                                       std::cout << "Point " << id <<" \t removed "<<visible[i]->id<<std::endl;
                                       break;
                               }

                       }
               }
}
