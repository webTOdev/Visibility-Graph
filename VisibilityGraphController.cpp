/*
 * VisibilityGraph.cpp
 *
 *  Created on: Oct 3, 2013
 *      Author: nut
 */

#include "VisibilityGraphController.h"
#include <map>


tLinestring createHorizontalLine(Point* p);
tLinestring createLineString(Line* line);
edgeContainer findIntersectionWithEdge(angleContainer angles,vector<Obstacle*> obstacleList,tLinestring sweepLine,Point* ori,edgeContainer edges);
Point* findPointById( vector<Point*> points,int itemToFind);
Line* searchLineContainingPoint(Point* pt,int *lineIds,vector<Line*> lines);
Obstacle* getObsCoveringPoint(Point* w_i,vector<Obstacle*> obsList);
bool doesLineAndPolygonIntersects(tLinestring ls,tPolygon p,Point* w_i,Point* ori,vector<Obstacle*> obsList);
void printEdgeList(edgeContainer edges);
bool doesTwoLineTouches(tLinestring ls1,tLinestring ls2,Point* w_i,Point* ori,vector<Obstacle*> obsList);
edgeContainer eraseOneEdgeFromEdgeList(edgeContainer edges,Line* ln);
edgeContainer insertOneEdgeInEdgeList(edgeContainer edges,Line* ln,double dist,Point* ori,Point* w_i,Point* c);


VisibilityGraphController::VisibilityGraphController() {
	// TODO Auto-generated constructor stub

}
VisibilityGraphController::VisibilityGraphController(vector<Obstacle*> obstacleList,Point* p){
	obstacleList=obstacleList;
	p=p;
}
VisibilityGraphController::VisibilityGraphController(VisibilityGraph* vg){
	visGraph=vg;
	obstacleList=visGraph->obstacles;
}

VisibilityGraphController::~VisibilityGraphController() {
	// TODO Auto-generated destructor stub
}

vector<Line*> VisibilityGraphController::constructVisGraph(){

	vector<Line*> temp;
	vector<Line*> visEdges=visGraph->edges;
	visEdges.clear();
	//Iterate over eahc of the nodes and generate visibility for them
	for(int i=0;i<visGraph->nodes.size();i++){
		Point* p=visGraph->nodes[i];
		temp.clear();
		temp = visibleVertices(p);
		visEdges.insert(visEdges.end(),temp.begin(),temp.end());
	}
	visGraph->setEdges(visEdges);
	std::cout << "Initial Visibility Graph Constructed Successfully "<<std::endl;
	return visEdges;

}

vector<Line*> VisibilityGraphController::visibleVertices(Point* ori){
	tLinestring centerLine = createHorizontalLine(ori); //SweepLine initialize to horizontal
	angleContainer angles;

	//std::cout << "Origin at Point: "<<ori->id<<std::endl;
	//Iterate over each of the obstacles and sort all the points
	//Took help from  multi index facility of boost for angular sorting
	for(int m=0;m<obstacleList.size();m++){
		Obstacle* o=obstacleList[m];
		vector<Point*> points = o->getVertices();
		for(int i=0;i<points.size();i++){
			// Calculate the angle from center line:
			if(points[i]->id == ori->id)
				continue;
			double angle =vectorsAngle(ori->x,ori->y,points[i]->x,points[i]->y);
			points[i]->theta=angle;
			angles.insert( double_point( angle, points[i] ) );
		}
	}
		 //Print the angles
	    // std::cout << "Points sorted List by Angle: " << std::endl;
	     key_index_t& kindex = angles.get<key_tag>();
	     for( key_index_t::iterator k = kindex.begin(); k != kindex.end(); ++k ){
	        //std::cout << "Point :"<< k->second->id << " ==> " << k->first << std::endl;
	     }

	     edgeContainer bstEdges;
	     //Create the Horizontal Line from given Point
	     bstEdges = findIntersectionWithEdge(angles,obstacleList,centerLine,ori,bstEdges);
	     //Generate the visible Edges and Points from the given Point
	     vector<Line*> visibleEdges=generateVisibleEdge(angles,obstacleList,ori,bstEdges,visGraph);

	return visibleEdges;

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
						 //std::cout << "Intersection at (" <<get<0>(p) << "," << get<1>(p)<<") with line "<<currentLine->id<<std::endl;
						 double dist=bg::distance(boost::make_tuple(ori->x, ori->y),p);
						 if(dist!=0){//This is the case where intersection point is the origin and we have two edges from this origin
							 edges.insert(double_line(dist,currentLine));
						 }
					 }
				 }

			}
	}
	return edges;

}

//Generates Visibility Graphs Edges
vector<Line*> VisibilityGraphController::generateVisibleEdge(angleContainer angles,vector<Obstacle*> obstacleList,Point* ori,edgeContainer edges,VisibilityGraph* vg){
	vector<Line*> obsEdges; //Represents the Edges of the Visibility Graph
	vector<Point*> obsVertices;//Represents the Nodes of the Visibility Graph
	vector<Line*> visibleEdges;//Visible Edges of the Visibility Graph
	Line* sweepLine; //The sweep line from Point p to w_i

	int index=1;
	//Keep the earlier Point
	Point* w_i_1;
	//Find the visibility of other points for a given point
	  key_index_t& kindex = angles.get<key_tag>();
	  for( key_index_t::iterator k = kindex.begin(); k != kindex.end(); ++k ){
		  //Prints the edge list before each iteration
		  //  printEdgeList(edges);

		  Point* w_i=k->second;
		  if(index!=1){
			  w_i_1=(--k)->second;
			  ++k;
		  }
		 // std::cout << "Sweeps at "<<w_i->id<<std::endl;
		  index++;

		  sweepLine=new Line(ori,w_i);
		  if(isVisible(w_i,ori,sweepLine,w_i_1,index,edges))
		  {
			  w_i->visited=true;
			  ori->addVisible(w_i);
			  visibleEdges.push_back(new Line(ori,w_i));
			 // std::cout<<"Visible Edges "<<ori->id<<"->"<<w_i->id<<std::endl;
		  }
		  //Check for clockwise side edges
		  //Each points has two edge associated and thats why two new points
		  int* otherEnds=vg->getOtherEndOfThisPoint(w_i);
   		  // std::cout<<"Other Ends at w_i "<<w_i->id<<" ->"<<otherEnds[0]<<","<<otherEnds[1]<<std::endl;
		  //Each points has two edge associated
		  int* es=vg->getEdgesOfThisPoint(w_i);
		  // std::cout<<"Edges at w_i "<<w_i->id<<" ->"<<es[0]<<","<<es[1]<<std::endl;

		  //Update the Edge List for clockwise or anti-clockwise edges
		  edges= updateEdgeList(edges,otherEnds,es,ori,w_i);
	  }

		return visibleEdges;
}

//Used for erasing an edge from edge list
edgeContainer eraseOneEdgeFromEdgeList(edgeContainer edges,Line* ln){
	key_index_edge& kin = edges.get<key_tag>();
	for( key_index_edge::iterator k = kin.begin(); k != kin.end(); ++k ){
		if(k->second->id == ln->id){
			//std::cout << "Erasing Line :" <<k->second->id<< std::endl;
			//std::cout << "Dist :" <<k->first<< std::endl;
			kin.erase(k++);
			break;
		}
	}
	return edges;
}

edgeContainer insertOneEdgeInEdgeList(edgeContainer edges,Line* ln,double dist,Point* ori,Point* w_i,Point* c){
	key_index_edge& kin = edges.get<key_tag>();
	bool found=false;
	//Handle edges that have same distance
	for( key_index_edge::iterator k = kin.begin(); k != kin.end(); ++k ){
		//Don't add same edge twice
		if(k->second->id == ln->id)
			continue;
		//Two edge is at same distance so Edge that makes smaller angle is added first
		//May happen in case of adjacent edges from a node
		if(k->first == dist){
			found=true;
			Line* oldLine=k->second;
			//std::cout << "Found Line :" <<oldLine->id<< " in same distance "<<std::endl;

			Point* c2;
			if(oldLine->a->id == w_i->id){
				c2=oldLine->b;
			}
			else
			c2=oldLine->a;

			double angleNew=angleBetweenThreePoint(ori->x,ori->y,w_i->x,w_i->y,c->x,c->y);
			//std::cout << "Angle between :" <<ln->id<<" and sweepline "<<angleNew<< std::endl;
			double anglePre=angleBetweenThreePoint(ori->x,ori->y,w_i->x,w_i->y,c2->x,c2->y);
			//std::cout << "Angle between :" <<oldLine->id<<" and sweepline "<<anglePre<< std::endl;
			//As the two distance is similar we will insert the edge according to the angle between sweepline and edge
			if(angleNew>anglePre){
				//Making a very small difference in the distance so that we can sort
				edges.insert(double_line(dist+.00001,ln));
			}
			else
				edges.insert(double_line(dist-.00001,ln));

		}
	}

	if(!found)
		edges.insert(double_line(dist,ln));
	return edges;
}

//Updates the edge list
edgeContainer VisibilityGraphController::updateEdgeList(edgeContainer edges,int* otherEnds,int* es,Point* ori,Point* w_i){

	Line* ln;
	//Loop continues twice because at each update of edge list atmost 2 operation
	//There may be two inserts, two deletes, or an insert and a delete.
	for(int i=0;i<2;i++){

				  Point* c=findPointById(visGraph->nodes,otherEnds[i]);
				  ln = searchLineContainingPoint(c,es,visGraph->obsSides);
				  //If clockwise side insert in edge list else delete
				  if(isLeft(ori,w_i,c)){
					  tLinestring lineS=createLineString(ln);
					  //std::cout<<"Line "<<ln->id<< " is at clockwise side of Point "<<ori->id<<","<<w_i->id<<std::endl;
					  double dist=bg::distance(boost::make_tuple(ori->x, ori->y),lineS);
					  //std::cout<<"Distance : "<<ln->id<<" and "<<ori->id<<" : "<<dist<<std::endl;
					  edges = insertOneEdgeInEdgeList(edges,ln,dist,ori,w_i,c);

				  }else{
					  //std::cout<<"Line "<<ln->id<<" is at anti-clockwise side of "<<ori->id<<","<<w_i->id<<std::endl;
					  edges = eraseOneEdgeFromEdgeList(edges,ln);
				  }

	}

	return edges;
}

void printEdgeList(edgeContainer edges){
	std::cout << "Edge List :" << std::endl;
	key_index_edge& kin = edges.get<key_tag>();
	for( key_index_edge::iterator k = kin.begin(); k != kin.end(); ++k ){
		k->second->print();
		std::cout << "Dist :" <<k->first<< std::endl;
	}
}
Point* findPointById( vector<Point*> points,int itemToFind){
	for (std::vector<Point*>::iterator it = points.begin() ; it != points.end(); ++it){
		if((*it)->id==itemToFind){
			return *it;
		}
	}
	return NULL;
}
Line* findLineById( vector<Line*> lines,int itemToFind){
	for (std::vector<Line*>::iterator it = lines.begin() ; it != lines.end(); ++it){
		//std::cout<<"Searching "<<itemToFind<<" Line check "<<(*it)->id<<std::endl;
		if((*it)->id==itemToFind){
			return *it;
		}
	}
	return NULL;
}
//From a given point find in which edge this point is
Line* searchLineContainingPoint(Point* pt,int *lineIds,vector<Line*> lines){
	Line* l=findLineById(lines,lineIds[0]);
	//l->print();
	if((l->a->id) == (pt->id) || (l->b->id)==(pt->id)){
	return l;
	}

	l=findLineById(lines,lineIds[1]);
	if((l->a->id) == (pt->id) || (l->b->id)==(pt->id)){
		return l;
	}


}

//Checks the Visibility of a point from a given point
bool VisibilityGraphController::isVisible(Point* w_i,Point* ori,Line* sweepLine,Point* w_i_1,int i,edgeContainer edges){
	//If sweepline intersects interior of the polygon of which w_i is a vertex
	tLinestring line=createLineString(sweepLine);
	//std::cout <<"Sweep Line " << " ==> " << sweepLine->a->id<<","<<sweepLine->b->id << std::endl;
	tPolygon poly=getObsCoveringPoint(w_i,obstacleList)->poly;
	if(doesLineAndPolygonIntersects(line,poly,w_i,ori,obstacleList)){
		// std::cout <<"At Line 1" << std::endl;
		return false;
	}
	if(i==1 || !checkCoLinear(sweepLine->a,w_i_1,sweepLine->b)){
		 //std::cout <<"At Line 2" << std::endl;
		 Line* e;

		 if(!edges.empty()){
			 key_index_edge& kindex = edges.get<key_tag>();
			 e=kindex.begin()->second;
			// std::cout <<"First Line in Edge List " << " ==> " << e->id << std::endl;
			 tLinestring eLine=createLineString(e);
			 bool b = boost::geometry::intersects(line,eLine);

			 if(b){
				 //Two line just touched does not intersects
				 if(!doesTwoLineTouches(line,eLine,w_i,ori,obstacleList)){
					// std::cout <<"At Line 4" << std::endl;
					 return false;
				 }
				 else{
					// std::cout <<"At Line 5.1" << std::endl;
					 return true;
				 }
			 }
			 else{
				// std::cout <<"At Line 4.5 and edge list not empty" << std::endl;
				 return true;
			 }
		 }
		 else{
			// std::cout <<"At Line 5.2" << std::endl;
			 return true;

		 }
	}
	else{
		// std::cout <<"At Line 6" << std::endl;
		if(!ori->isVisible(w_i_1)){
			return false;
		}
		else
		{
			tLinestring w_1_to_w=createLineString(new Line(w_i_1->x,w_i_1->y,w_i->x,w_i->y));
			key_index_edge& kindex1 = edges.get<key_tag>();
			bool b=false;
			//Check if the any line in edge list intersects w_i,w_i_1
			for( key_index_edge::iterator k = kindex1.begin(); k != kindex1.end(); ++k ){
				tLinestring edgeLine=createLineString(k->second);
				b = boost::geometry::intersects(w_1_to_w,edgeLine);
				if(b)
				{
					break;
				}
			}
			if(b)
				return false;
			else
				return true;
		}
	}
	return true;
}

//Search in which Obstacle this point lies
Obstacle* getObsCoveringPoint(Point* w_i,vector<Obstacle*> obsList){
	for(int i=0;i<obsList.size();i++){
		if(obsList[i]->searchPoint(w_i->x,w_i->y)){
			return obsList[i];
		}
	}
}

//Checks whether two lines just touched does not intersect
bool doesTwoLineTouches(tLinestring ls1,tLinestring ls2,Point* w_i,Point* ori,vector<Obstacle*> obsList){
	std::deque<tPoint> output;
	bool touches=false;
	boost::geometry::intersection(ls1, ls2, output);
	BOOST_FOREACH(tPoint const& p, output)
	{
			double x1=get<0>(p);
			double y1=get<1>(p);
			//two Line Touches at w_i not internally Intersects
			if(x1==w_i->x && y1==w_i->y){
				touches=true;
			}
			if(x1==ori->x && y1==ori->y){
				touches=true;
			}
		   // std::cout <<  "Intersects at : " << x1<<","<<y1<<" and Point at: "<<w_i->x<<","<<w_i->y<<" and Origin at: "<<ori->x<<","<<ori->y  << std::endl;
    }
	return touches;
}

//Checks whether the line and the polygon intersects
bool doesLineAndPolygonIntersects(tLinestring ls,tPolygon p,Point* w_i,Point* ori,vector<Obstacle*> obsList){
	std::vector<turn_info> turns;
	bg::detail::get_turns::no_interrupt_policy policy;
	bg::get_turns<false, false, bg::detail::overlay::assign_null_policy>(ls, p, turns, policy);
	bool intersect=false;
    if(turns.size()>1){
    	intersect=true;
    }

    //If the two points is in the same obstacle then they cannot see each other
    if(turns.size()==1){
		int obsOri=getObsCoveringPoint(ori,obsList)->id;
		int obsW_i=getObsCoveringPoint(w_i,obsList)->id;
		if(obsOri==obsW_i)
			intersect=true;
    }
    return intersect;

}

//Find whether the new obstacle intersect with the line : for Incremental Vis Graph
bool VisibilityGraphController::findEdgeAndObsIntersects(Line* line,Obstacle* o){
	tLinestring ls = createLineString(line);
	tPolygon p = o->poly;
	std::vector<turn_info> turns;
	bg::detail::get_turns::no_interrupt_policy policy;
	bg::get_turns<false, false, bg::detail::overlay::assign_null_policy>(ls, p, turns, policy);
	bool intersect=false;
    if(turns.size()>1){
    	intersect=true;
    }
    return intersect;

}
//Creating Horizontal center Line
tLinestring createHorizontalLine(Point* p){
	//std::cout << "Creating Horizontal center Line starting from "<<p->id<<std::endl;
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

VisibilityGraph* VisibilityGraphController::addNewObstacleForIncrementalVisGraph(
		VisibilityGraph* vGraph,Obstacle* obs) {

	Obstacle* o = vGraph->addObstacle(obs);
	vector<Point*> obsVertices = o->getVertices();
	setVisGraph(vGraph);

	//Remove existing edges of graph that intersects with this obstacle
	for (int i = 0; i < vGraph->edges.size(); i++) {
		Line* l = vGraph->edges[i];
		if (findEdgeAndObsIntersects(l, o)) {
			vGraph->removeEdgeFromVisGraph(l);
			//Also remove the opposite edge , for example after removing 1->13 also remove 13->1
			Line* line = vGraph->findEdgeWithPoints(l->b, l->a);
			if (line != NULL) {
				vGraph->removeEdgeFromVisGraph(line);
			}
		}
	}

	//Search for the visible edges from the new obstacle's nodes and Insert them
	for (int i = 0; i < obsVertices.size(); i++) {
		Point* point = obsVertices[i];
		vector<Line*> temp = visibleVertices(point);
		vGraph->insertEdgeInVisGraph(temp);
	}

	std::cout << "***Incremental Vis Graph*** "<<"Obstacle with ID "<<obs->id<<" added successfully in Visibility Graph"<<std::endl;

	return vGraph;
}

VisibilityGraph* VisibilityGraphController::removeDataPointFromVisGraph(
		VisibilityGraph* vGraph, Obstacle* obs) {

	vector<Point*> obsVertices = obs->vertices;
	//Find the Edges with this vertices and remove them from Graph
	for (int i = 0; i < obsVertices.size(); i++) {
		vector<Line*> visEdges = vGraph->findEdgesWithThisPoint(obsVertices[i]);
		for (int j = 0; j < visEdges.size(); j++) {
			vGraph->removeEdgeFromVisGraph(visEdges[j]);
		}

		//Now remove the vertex
		vGraph->removeNodeFromVisGraph(obsVertices[i]);
	}

	//Now remove the Sides of this Obstacle , in case of data point there is only side with same point eg : side=point->point
	vector<Line*> visObsSide = obs->edges;
	for(int k=0;k<visObsSide.size();k++){
		vGraph->removeObsSideFromVisGraph(visObsSide[k]);
	}
	//Now remove the data point
	vGraph->removeObstacleFromVisGraph(obs);
	std::cout << "***Incremental Vis Graph*** "<<"Obstacle with ID "<<obs->id<<" removed successfully from Visibility Graph"<<std::endl;


	return vGraph;
}




