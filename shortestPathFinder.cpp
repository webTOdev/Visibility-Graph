/*

 * shortestPathFinder.cpp
 *
 *  Created on: Oct 11, 2013
 *      Author: nut
 */
/*#include <iostream>

#include <vector>
#include "VisibilityGraph.h"
#include "graphutility.h"
#include "dijkstra.h"
#include "pointHandler.h"
#include "drawing.h"

void findShortestPath(VisibilityGraph* vg,double sourceX,double sourceY,double destX,double destY){
	int numOfPoints=vg->nodes.size();
	int numOfEdges=vg->edges.size();
	int sourcePointId=searchPointByCoord(vg->nodes,sourceX,sourceY)->id;
	int destPointId=searchPointByCoord(vg->nodes,destX,destY)->id;
	Point* start;
	Point* goal;
	initiateDijkstra(numOfPoints,numOfEdges,false,sourcePointId,destPointId);
			int *shortestPath = getShortestPath();
			int i=0;
			//Print the Shortest Path
			 printf("The Shortest Path is ");
			while(shortestPath[i]!=-1){
				printf("%d ", shortestPath[i]);

				if(shortestPath[i+1]!=-1){
					start = getPointById(vg->nodes,shortestPath[i]);
					goal = getPointById(vg->nodes,shortestPath[i+1]);
					// Visualize:
					drawCircle(start->x, start->y,5,GREEN);
					drawCircle(goal->x, goal->y,5,GREEN);
					drawLine(start->x, start->y, goal->x, goal->y, GREEN);
				}
				else
					{
						goal= getPointById(vg->nodes,destPointId);
						writeText((goal->x-5), (goal->y+15),"Dest",GREEN);
					}

				if(i==0){
						writeText((start->x-5), (start->y+15),"Source",GREEN);
				}

				i++;
			}
}
*/

