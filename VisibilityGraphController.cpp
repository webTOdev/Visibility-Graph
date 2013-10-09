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
//bool isVisible(Point* w);
//vector<Line*> generateVisibleEdge(angleContainer angles,vector<Obstacle*> obstacleList,Point* ori,edgeContainer edges,VisibilityGraph* vg);
Point* findPointById( vector<Point*> points,int itemToFind);
Line* searchLineContainingPoint(Point* pt,int *lineIds,vector<Line*> lines);
Obstacle* getObsCoveringPoint(Point* w_i,vector<Obstacle*> obsList);
bool doesLineAndPolygonIntersects(tLinestring ls,tPolygon p,Point* w_i,Point* ori,vector<Obstacle*> obsList);
void printEdgeList(edgeContainer edges);
bool doesTwoLineTouches(tLinestring ls1,tLinestring ls2,Point* w_i,Point* ori);
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
	for(int i=0;i<visGraph->nodes.size();i++){
		Point* p=visGraph->nodes[i];
		temp.clear();
		temp = visibleVertices(p);
		visEdges.insert(visEdges.end(),temp.begin(),temp.end());
	}
	return visEdges;

}

vector<Line*> VisibilityGraphController::visibleVertices(Point* ori){
	tLinestring centerLine = createHorizontalLine(ori); //SweepLine initialize to horizontal
	tPoint pt=ori->p; //The point around which the SweepLine rotates
	angleContainer angles;

	std::cout << "Origin at id "<<ori->id<<"==>"<<ori->x<<","<<ori->y<<std::endl;
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
	     std::cout << "Angle List :" << std::endl;
	     key_index_t& kindex = angles.get<key_tag>();
	     for( key_index_t::iterator k = kindex.begin(); k != kindex.end(); ++k ){
	        std::cout << k->first << " ==> " << k->second->id << std::endl;
	     }

	     //Search in the container for a point with given angle
	    /* anglesContainer::iterator it = angles.get<0>().find(2.59543);
	     Point* found=it->second;
	     std::cout << "Found 2.59543 ==> " << found->id << std::endl;
*/
	     edgeContainer bstEdges;
	     bstEdges = findIntersectionWithEdge(angles,obstacleList,centerLine,ori,bstEdges);
	     //Decided to store edges in vector :(
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
						 double dist=bg::distance(boost::make_tuple(ori->x, ori->y),p);
						// std::cout << "Intersection at (" <<get<0>(p) << "," << get<1>(p)<<") with line "<<currentLine->id<<std::endl;
						 //std::cout << "Distance between "<<ori->x<<","<<ori->y<<" and "<<get<0>(p)<<","<<get<1>(p)<<" : "<<dist<<std::endl;
						 edges.insert(double_line(dist,currentLine));
					 }
				 }

			}
	}
	return edges;

}

vector<Line*> VisibilityGraphController::generateVisibleEdge(angleContainer angles,vector<Obstacle*> obstacleList,Point* ori,edgeContainer edges,VisibilityGraph* vg){
	vector<Line*> obsEdges;
	vector<Point*> obsVertices;
	vector<Line*> visibleEdges;
	Line* sweepLine;

	//for i=1 checkingat Visible(wi) 2nd line
	int index=1;
	//Keep w_i -1 th Point
	Point* w_i_1;
	//Find
	  key_index_t& kindex = angles.get<key_tag>();
	  for( key_index_t::iterator k = kindex.begin(); k != kindex.end(); ++k ){
	       // std::cout << k->first << " ==> " << k->second->id << std::endl;
		  printEdgeList(edges);

		  Point* w_i=k->second;
		  if(index!=1){
			  w_i_1=(--k)->second;
			  ++k;
			 // std::cout << "Sweeps at Point w_i: "<<w_i->id<<" - "<<w_i->x<<","<<w_i->y<<" w_i-1 "<<w_i_1->id<<std::endl;
			  std::cout << "Sweeps at "<<w_i->id<<std::endl;
		  }
		  else
			  std::cout << "Sweeps starts at Point w_i: "<<w_i->id<<std::endl;
		  index++;
		//  sweepLine=new Line(ori->x,ori->y,w_i->x,w_i->y);
		  sweepLine=new Line(ori,w_i);
		  if(isVisible(w_i,ori,sweepLine,w_i_1,index,edges))
		  {
			  w_i->visited=true;
			  ori->addVisible(w_i);
			  visibleEdges.push_back(new Line(ori->x,ori->y,w_i->x,w_i->y));
			  std::cout<<"Visible Edges "<<ori->id<<"->"<<w_i->id<<std::endl;
		  }
			  //Check for clockwise side edges
			  //Each points has two edge associated and thats why two new points
			  int* otherEnds=vg->getOtherEndOfThisPoint(w_i);
			 // std::cout<<"Other Ends at w_i "<<w_i->id<<" ->"<<otherEnds[0]<<","<<otherEnds[1]<<std::endl;
			  //Each points has two edge associated
			  int* es=vg->getEdgesOfThisPoint(w_i);
			 // std::cout<<"Edges at w_i "<<w_i->id<<" ->"<<es[0]<<","<<es[1]<<std::endl;


			  edges= updateEdgeList(edges,otherEnds,es,ori,w_i);
	  }

		return visibleEdges;
}

edgeContainer eraseOneEdgeFromEdgeList(edgeContainer edges,Line* ln){
	key_index_edge& kin = edges.get<key_tag>();
	for( key_index_edge::iterator k = kin.begin(); k != kin.end(); ++k ){
		if(k->second->id == ln->id){
			std::cout << "Erasing Line :" <<k->second->id<< std::endl;
			std::cout << "Dist :" <<k->first<< std::endl;
			kin.erase(k++);
			break;
		}
	}
	return edges;
}

edgeContainer insertOneEdgeInEdgeList(edgeContainer edges,Line* ln,double dist,Point* ori,Point* w_i,Point* c){
	key_index_edge& kin = edges.get<key_tag>();
	bool found=false;
	for( key_index_edge::iterator k = kin.begin(); k != kin.end(); ++k ){
		//Don't add same edge twice
		if(k->second->id == ln->id)
			continue;
		if(k->first == dist){
			found=true;
			Line* oldLine=k->second;
			std::cout << "Found Line :" <<oldLine->id<< " in same distance "<<std::endl;

			Point* c2;
			if(oldLine->a->id == w_i->id){
				c2=oldLine->b;
			}
			else
			c2=oldLine->a;

			double angleNew=angleBetweenThreePoint(ori->x,ori->y,w_i->x,w_i->y,c->x,c->y);
			std::cout << "Angle between :" <<ln->id<<" and sweepline "<<angleNew<< std::endl;
			double anglePre=angleBetweenThreePoint(ori->x,ori->y,w_i->x,w_i->y,c2->x,c2->y);
			std::cout << "Angle between :" <<oldLine->id<<" and sweepline "<<anglePre<< std::endl;
			//As the two distance is similar we will insert the edge according to the angle between sweepline and edge
			if(angleNew>anglePre){
				edges.insert(double_line(dist+.00001,ln));
			}
			else
				edges.insert(double_line(dist-.00001,ln));

			//kin.erase(k++);
		}
	}

	if(!found)
		edges.insert(double_line(dist,ln));
	return edges;
}

edgeContainer VisibilityGraphController::updateEdgeList(edgeContainer edges,int* otherEnds,int* es,Point* ori,Point* w_i){

	Line* ln;
	//Loop continues twice because at each update of edge list atmost 2 operation
	for(int i=0;i<2;i++){

				  Point* c=findPointById(visGraph->nodes,otherEnds[i]);
				 // double dist=bg::distance(boost::make_tuple(c->x, c->y),w_i->p);
				  ln = searchLineContainingPoint(c,es,visGraph->obsSides);
			//	  if(isRotationClockwise(ori,w_i,c)){
				  if(isLeft(ori,w_i,c)){
					  //CONFUSED ABOUT DIST currently storing as origin to obsSide distance
					  tLinestring lineS=createLineString(ln);
					  std::cout<<"Line "<<ln->id<<" and Point "<<c->x<<","<<c->y<< " is at clockwise side of Point "<<ori->id<<","<<w_i->id<<std::endl;
					  double dist=bg::distance(boost::make_tuple(ori->x, ori->y),lineS);
					  std::cout<<"Distance : "<<ln->id<<" and "<<ori->id<<" : "<<dist<<std::endl;
					  edges = insertOneEdgeInEdgeList(edges,ln,dist,ori,w_i,c);

				  }else{
					  std::cout<<"Line "<<ln->id<<" and Point "<<c->x<<","<<c->y<<" is at anti-clockwise side of "<<ori->id<<","<<w_i->id<<std::endl;
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
bool VisibilityGraphController::isVisible(Point* w_i,Point* ori,Line* sweepLine,Point* w_i_1,int i,edgeContainer edges){
	//If sweepline insectes interio of the polygon of which w_i is a vertex
	tLinestring line=createLineString(sweepLine);
	std::cout <<"Sweep Line " << " ==> " << sweepLine->a->id<<","<<sweepLine->b->id << std::endl;
	tPolygon poly=getObsCoveringPoint(w_i,obstacleList)->poly;
	if(doesLineAndPolygonIntersects(line,poly,w_i,ori,obstacleList)){
		 std::cout <<"At Line 1" << std::endl;
		return false;
	}
	if(i==1 || !checkCoLinear(sweepLine->a,w_i_1,sweepLine->b)){
		 std::cout <<"At Line 2" << std::endl;
		 //Nusrat
		 Line* e;

		 if(!edges.empty()){
			 key_index_edge& kindex = edges.get<key_tag>();
			 e=kindex.begin()->second;
			 std::cout <<"First Line in Edge List " << " ==> " << e->id << std::endl;
			 tLinestring eLine=createLineString(e);
			 bool b = boost::geometry::intersects(line,eLine);

			 if(b){
				 //Two line just touched not intersects
				 if(!doesTwoLineTouches(line,eLine,w_i,ori)){
					 std::cout <<"At Line 4" << std::endl;
					 return false;
				 }
			 }
			 else{
				 std::cout <<"At Line 4.5 and edge list not empty" << std::endl;
				 return true;
			 }
		 }
		 else{
			 return true;
			 std::cout <<"At Line 5" << std::endl;
		 }
	}
	else{
		 std::cout <<"At Line 6" << std::endl;
		if(!ori->isVisible(w_i_1)){
			return false;
		}
		else
		{
			tLinestring w_1_to_w=createLineString(new Line(w_i_1->x,w_i_1->y,w_i->x,w_i->y));
			key_index_edge& kindex1 = edges.get<key_tag>();
			bool b=false;
			//Nusrat
			for( key_index_edge::iterator k = kindex1.begin(); k != kindex1.end(); ++k ){
				tLinestring edgeLine=createLineString(k->second);
				b = boost::geometry::intersects(w_1_to_w,edgeLine);
				if(b)
				{break;}
			}
			if(b)
				return false;
			else
				return true;
		}
	}
	return true;
}
Obstacle* getObsCoveringPoint(Point* w_i,vector<Obstacle*> obsList){
	for(int i=0;i<obsList.size();i++){
		if(obsList[i]->searchPoint(w_i->x,w_i->y)){
			return obsList[i];
		}
	}
}

bool doesTwoLineTouches(tLinestring ls1,tLinestring ls2,Point* w_i,Point* ori){
	std::deque<tPoint> output;
	int i=0;
	bool touches=false;
	boost::geometry::intersection(ls1, ls2, output);
	BOOST_FOREACH(tPoint const& p, output)
	{
			double x1=get<0>(p);
			double y1=get<1>(p);
			//2 Line Touches at w_i not internally Intersects
			if(x1==w_i->x && y1==w_i->y){
				touches=true;
			}
			if(x1==ori->x && y1==ori->y){
				touches=true;
			}
	        std::cout <<  "Intersects at : " << x1<<","<<y1<<" and Point at: "<<w_i->x<<","<<w_i->y<<" and Origin at: "<<ori->x<<","<<ori->y  << std::endl;
    }
	return touches;
}

bool doesLineAndPolygonIntersects(tLinestring ls,tPolygon p,Point* w_i,Point* ori,vector<Obstacle*> obsList){
	std::vector<turn_info> turns;
	bg::detail::get_turns::no_interrupt_policy policy;
	bg::get_turns<false, false, bg::detail::overlay::assign_null_policy>(ls, p, turns, policy);

	std::cout <<"Intersects True " << turns.size() << std::endl;
	bool intersect=false;
    if(turns.size()>1){

    	intersect=true;
	    //return true;
    }
    tPoint a=boost::make_tuple(w_i->x, w_i->y);
    tPoint b=boost::make_tuple(ori->x, ori->y);
 /*	 if(turns.size()==1){
   	 BOOST_FOREACH(turn_info const& turn, turns){
   		double x=get<0>(doesLineAndPolygonIntersectsturn.point);
   		double y=get<1>(turn.point);
   		if(x==w_i->x && y==w_i->y){
   			intersect=true;
   			std::cout <<"Intersects at " <<x<<" , "<<y <<std::endl;
   		}
   	 }
   	}*/
    if(turns.size()==1){
    int obsOri=getObsCoveringPoint(ori,obsList)->id;
    int obsW_i=getObsCoveringPoint(w_i,obsList)->id;
    if(obsOri==obsW_i)
    	intersect=true;
    }
    return intersect;

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




