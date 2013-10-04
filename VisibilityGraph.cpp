/*
 * VisibilityGraph.cpp
 *
 *  Created on: Oct 3, 2013
 *      Author: nut
 */

#include "VisibilityGraph.h"
#include <map>

//Using multi_index_container to store <angle,Point*> and <intersectedDistance,Point*>
struct key_tag {};
struct value_tag {};

typedef std::pair< double, Point* > double_point;
typedef boost::multi_index_container<
    double_point,
    boost::multi_index::indexed_by<
      boost::multi_index::ordered_non_unique< boost::multi_index::tag< key_tag >,
          boost::multi_index::member< double_point, double, &double_point::first > >,
      boost::multi_index::ordered_unique< boost::multi_index::tag< value_tag >,
          boost::multi_index::member< double_point, Point*, &double_point::second > >
> >  angleContainer;

typedef angleContainer::index<key_tag>::type  key_index_t;
typedef angleContainer::index<value_tag>::type value_index_t;

typedef std::pair< double, Line* > double_line;
typedef boost::multi_index_container<
		double_line,
    boost::multi_index::indexed_by<
      boost::multi_index::ordered_non_unique< boost::multi_index::tag< key_tag >,
          boost::multi_index::member< double_line, double, &double_line::first > >,
      boost::multi_index::ordered_unique< boost::multi_index::tag< value_tag >,
          boost::multi_index::member< double_line, Line*, &double_line::second > >
> >  edgeContainer;

typedef edgeContainer::index<key_tag>::type  key_index_edge;
typedef edgeContainer::index<value_tag>::type value_index_edge;

tLinestring createHorizontalLine(Point* p);
edgeContainer findIntersectionWithEdge(angleContainer angles,vector<Obstacle*> obstacleList,tLinestring sweepLine);

VisibilityGraph::VisibilityGraph() {
	// TODO Auto-generated constructor stub

}
VisibilityGraph::VisibilityGraph(vector<Obstacle*> obstacleList,Point* p){
	obstacleList=obstacleList;
	p=p;
}

VisibilityGraph::~VisibilityGraph() {
	// TODO Auto-generated destructor stub
}

vector<Line*> VisibilityGraph::visibleVertices(vector<Obstacle*> obstacleList,Point* ori){
	vector<Line*> visiblePoints;
	tLinestring centerLine = createHorizontalLine(ori); //SweepLine initialize to horizontal
	point pt=ori->p; //The point around which the SweepLine rotates
	angleContainer angles;

	//Iterate over each of the obstacles and sort all the points
	for(int m=0;m<obstacleList.size();m++){
		Obstacle* o=obstacleList[m];
		vector<Point*> points = o->getVertices();
		for(int i=0;i<points.size();i++){
			// Calculate the angle from center line:
			double angle =vectorsAngle(ori->x,ori->y,points[i]->x,points[i]->y);
			points[i]->theta=angle;
			angles.insert( double_point( angle, points[i] ) );
		}
	}
	//Took help from  multi index facility of boost
	  //   std::cout << "Angle List :" << std::endl;
	     key_index_t& kindex = angles.get<key_tag>();
	     for( key_index_t::iterator k = kindex.begin(); k != kindex.end(); ++k ){
	       // std::cout << k->first << " ==> " << k->second->id << std::endl;
	     }

	     //Search in the container for a point with given angle
	    /* anglesContainer::iterator it = angles.get<0>().find(2.59543);
	     Point* found=it->second;
	     std::cout << "Found 2.59543 ==> " << found->id << std::endl;
*/
	     edgeContainer edges = findIntersectionWithEdge(angles,obstacleList,centerLine);

	return visiblePoints;

}

tLinestring createHorizontalLine(Point* p){

	 bg::model::linestring<tPoint> line;
	 const double c[][2] = { {p->x, p->y}, {(p->x)+1000, p->y}};
	  bg::assign_points(line, c);
	  return line;
}

edgeContainer findIntersectionWithEdge(angleContainer angles,vector<Obstacle*> obstacleList,tLinestring sweepLine){
	vector<Line*> obsEdges;
	edgeContainer edges;
	for(int m=0;m<obstacleList.size();m++){
			Obstacle* o=obstacleList[m];
			obsEdges=o->getEdges();
			for(int n=0;n<obsEdges.size();n++){
				Line* currentLine =obsEdges[n];
				tLinestring currentEdge = boost::assign::tuple_list_of(currentLine->a->x, currentLine->a->y)(currentLine->b->x, currentLine->b->y);
				 std::deque<tPoint> intersection;
				       boost::geometry::intersection(sweepLine,currentEdge,intersection);
				       BOOST_FOREACH(tPoint const& p, intersection)
				          {
				    	   	   std::cout << "Intersection at (" <<get<0>(p) << "," << get<0>(p)<<") with line "<<currentLine->id<<std::endl;
				       }
			}
	}
	return edges;

}


