/*
 * VisibilityGraph.cpp
 *
 *  Created on: Oct 3, 2013
 *      Author: nut
 */

#include "VisibilityGraphController.h"
#include <map>

//Using multi_index_container to store <angle,Point*>
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

//Using multi_index_container to store <intersectedDistance,Point*>
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
tLinestring createLineString(Line* line);
edgeContainer findIntersectionWithEdge(angleContainer angles,vector<Obstacle*> obstacleList,tLinestring sweepLine,Point* ori,edgeContainer edges);
bool isVisible(Point* w);
vector<Line*> generateVisibleEdge(angleContainer angles,vector<Obstacle*> obstacleList,Point* ori,edgeContainer edges);

VisibilityGraphController::VisibilityGraphController() {
	// TODO Auto-generated constructor stub

}
VisibilityGraphController::VisibilityGraphController(vector<Obstacle*> obstacleList,Point* p){
	obstacleList=obstacleList;
	p=p;
}

VisibilityGraphController::~VisibilityGraphController() {
	// TODO Auto-generated destructor stub
}

vector<Line*> VisibilityGraphController::visibleVertices(vector<Obstacle*> obstacleList,Point* ori){
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
	     edgeContainer bstEdges;
	     bstEdges = findIntersectionWithEdge(angles,obstacleList,centerLine,ori,bstEdges);
	     vector<Line*> visibleEdges=generateVisibleEdge(angles,obstacleList,ori,bstEdges);

	return visiblePoints;

}


edgeContainer findIntersectionWithEdge(angleContainer angles,vector<Obstacle*> obstacleList,tLinestring sweepLine,Point* ori,edgeContainer e){
	vector<Line*> obsEdges;
	edgeContainer edges=e;
	for(int m=0;m<obstacleList.size();m++){
			Obstacle* o=obstacleList[m];
			obsEdges=o->getEdges();
			//Find intersection of sweep line with obstacle edges
			for(int n=0;n<obsEdges.size();n++){
				 Line* currentLine =obsEdges[n];
				 tLinestring currentEdge = createLineString(currentLine);
				 bool b = boost::geometry::intersects(sweepLine,currentEdge);
				 if(b){
					 std::deque<tPoint> intersection;
					 boost::geometry::intersection(sweepLine,currentEdge,intersection);
					 //If intersects then insert the edge in edgeContainer according to intersecting points distance
					 BOOST_FOREACH(tPoint const& p, intersection)
					 {
						 double dist=bg::distance(boost::make_tuple(ori->x, ori->y),p);
						 std::cout << "Intersection at (" <<get<0>(p) << "," << get<1>(p)<<") with line "<<currentLine->id<<std::endl;
						 std::cout << "Distance between "<<ori->x<<","<<ori->y<<" and "<<get<0>(p)<<","<<get<1>(p)<<" : "<<dist<<std::endl;
						 edges.insert(double_line(dist,currentLine));
					 }
				 }

			}
	}
	return edges;

}

vector<Line*> generateVisibleEdge(angleContainer angles,vector<Obstacle*> obstacleList,Point* ori,edgeContainer edges){
	vector<Line*> obsEdges;
	vector<Point*> obsVertices;
	vector<Line*> visibleEdges;
	//Find
	  key_index_t& kindex = angles.get<key_tag>();
	  for( key_index_t::iterator k = kindex.begin(); k != kindex.end(); ++k ){
	       // std::cout << k->first << " ==> " << k->second->id << std::endl;
		  Point* w_i=k->second;
		  if(isVisible(w_i))
		  {
			  ori->addVisible(w_i);
			  visibleEdges.push_back(new Line(ori->x,ori->y,w_i->x,w_i->y));
		  }
	  }
		return visibleEdges;
}

bool isVisible(Point* w){
	return true;
}

//LineString creation sample one
tLinestring createHorizontalLine(Point* p){

	 bg::model::linestring<tPoint> line;
	 const double c[][2] = { {p->x, p->y}, {(p->x)+1000, p->y}};
	 bg::assign_points(line, c);
	 return line;
}
//LineString creation sample two
tLinestring createLineString(Line* line){
	 tLinestring edge = boost::assign::tuple_list_of(line->a->x, line->a->y)(line->b->x, line->b->y);
	 return edge;
}

/*void pointsAndAssociatedEdge(vector<Obstacle*> obsList){
	for(int i=0;i<obsList.size();ob)
}*/



