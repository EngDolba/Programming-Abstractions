/******************************************************************************
* File: Trailblazer.cpp
*
* Implementation of the graph algorithms that comprise the Trailblazer
* assignment.
*/

#include "Trailblazer.h"
#include "TrailblazerGraphics.h"
#include "TrailblazerTypes.h"
#include "TrailblazerPQueue.h"
#include "Vector.h"
#include "Random.h"
using namespace std;

/* Function: shortestPath
* 
* Finds the shortest path between the locations given by start and end in the
* specified world.	 The cost of moving from one edge to the next is specified
* by the given cost function.	The resulting path is then returned as a
* Vector<Loc> containing the locations to visit in the order in which they
* would be visited.	If no path is found, this function should report an
* error.
*
* In Part Two of this assignment, you will need to add an additional parameter
* to this function that represents the heuristic to use while performing the
* search.  Make sure to update both this implementation prototype and the
* function prototype in Trailblazer.h.
*/
Loc locs(int r, int c)
{
	Loc loc;
	loc.col = c;
	loc.row = r;
	return loc;
}
Set<Loc> neighbors(Loc loc,Grid<double>& world)
{
	int row = loc.row;
	int col = loc.col;
	Set<Loc> clusters;
	if(world.inBounds(loc.row+1,loc.col))
	{
		clusters.add(locs(row+1,col));
	}
	if(world.inBounds(loc.row,loc.col+1))
	{
		clusters.add(locs(row,col+1));
	}
	if(world.inBounds(loc.row+1,loc.col+1))
	{
		clusters.add(locs(row+1,col+1));
	}
	if(world.inBounds(loc.row-1,loc.col+1))
	{
		clusters.add(locs(row-1,col+1));
	}
	if(world.inBounds(loc.row+1,loc.col-1))
	{
		clusters.add(locs(row+1,col-1));
	}
	if(world.inBounds(loc.row-1,loc.col-1))
	{
		clusters.add(locs(row-1,col-1));
	}
	if(world.inBounds(loc.row,loc.col-1))
	{
		clusters.add(locs(row,col-1)); 
	}
	if(world.inBounds(loc.row-1,loc.col))
	{
		clusters.add(locs(row-1,col)); 
	}
	return clusters;
}
Set<Loc> neighbors1(Loc loc,int numRows,int numCols)
{
	int row = loc.row;
	int col = loc.col;
	Set<Loc> clusters;
	if(row+1<numRows)
	{
		clusters.add(locs(row+1,col));
	}
	if(col+1<numCols)
	{
		clusters.add(locs(row,col+1));
	}
	if(col-1>=0)
	{
		clusters.add(locs(row,col-1)); 
	}
	if(row-1>=0)
	{
		clusters.add(locs(row-1,col)); 
	}
	return clusters;
}
Vector<Loc>
shortestPath(Loc start, Loc end,
			 Grid<double>& world,
			 double costFunction(Loc one, Loc two, Grid<double>& world),
			 double heuristic(Loc start, Loc end, Grid<double>& world)) {
				 Map<Loc,Loc> parents; // key shvili value parent;
				 Map<Loc,double> distances;
				 Set<Loc> expanded;
				 Set<Loc> visited;
				 TrailblazerPQueue<Loc>  enqueued;
				 visited.add(start);
				 distances[start] = 0;
				 enqueued.enqueue(start,heuristic(start,end,world));
				 colorCell(world,start,GREEN);
				 while(!enqueued.isEmpty())
				 {
					 Loc curr = enqueued.dequeueMin();
					 expanded.add(curr);
					 colorCell(world,curr,GREEN);
					 if(curr==end) break;
					 foreach(Loc loc in neighbors(curr,world))
					 {
						 if(expanded.contains(loc)) continue;
						 double dist = distances[curr] + costFunction(curr,loc,world);
						 if(!visited.contains(loc))
						 {
							 visited.add(loc);
							 colorCell(world,loc,YELLOW);
							 distances[loc] = dist;
							 parents[loc] = curr;
							 enqueued.enqueue(loc,dist+heuristic(loc,end,world));
						 }
						 if(visited.contains(loc) && dist<distances[loc])
						 {
							 distances[loc] = dist;
							 parents[loc] = curr;
							 enqueued.decreaseKey(loc,dist+heuristic(loc,end,world));
						 }
					 }
				 }
				 Stack<Loc> clusters;

				 Loc loc = end;
				 while(loc!=start)
				 {
					 clusters.push(loc);
					 loc = parents[loc];
				 }
				 clusters.push(start);
				 Vector<Loc> answer;
				 while(!clusters.isEmpty())
				 {
					 answer.add(clusters.pop());
				 }
				 return answer;
}

Set<Edge> createMaze(int numRows, int numCols) {
	Set<Set<Loc>*> allocatedMemory;
	Map<Loc,Set<Loc>*> clusters;
	Set<Edge> result;
	TrailblazerPQueue<Edge> kruskal;
	int clusterSize = 0;
	for(int i = 0;i<numRows;i++)
		for(int j = 0;j<numCols;j++)
		{ 
			Set<Loc>* set = new Set<Loc>;
			allocatedMemory.add(set);
			Loc loc;
			loc.col = j;
			loc.row = i;
			set->add(loc);
			clusters[loc] = set;
			clusterSize++;
		}
		for(int i = 0;i<numRows;i++)
			for(int j = 0;j<numCols-1;j++)
			{
				Loc loc;
				loc.col = j;
				loc.row = i;
				Loc loc1;
				loc1.col = j+1;
				loc1.row = i;
				Edge edge;
				edge.start = loc;
				edge.end = loc1;
				kruskal.enqueue(edge,randomInteger(0,INT_MAX));
			}
			for(int i = 0;i<numRows-1;i++)
				for(int j = 0;j<numCols;j++)
				{
					Loc loc;
					loc.col = j;
					loc.row = i;
					Loc loc1;
					loc1.col = j;
					loc1.row = i+1;
					Edge edge;
					edge.start = loc;
					edge.end = loc1;
					kruskal.enqueue(edge,randomInteger(0,INT_MAX));
				}
				while(clusterSize!=1)
				{
					Edge e = kruskal.dequeueMin();
					Loc loc1 = e.start;
					Loc loc2 = e.end;
					if(clusters[loc1]!=clusters[loc2])
					{
						Set<Loc>* newSet = new Set<Loc>;
						allocatedMemory.add(newSet);
						*newSet += *clusters[loc1];
						*newSet += *clusters[loc2];
						clusters[loc1]  = newSet;
						clusters[loc2] = newSet;
						foreach(Loc loc in *newSet)
							clusters[loc] = newSet;
						clusterSize--;
						result.add(e);
					}
				}
				foreach(Set<Loc>* allocM in allocatedMemory)
					delete allocM;
				return result;
}
Loc getConnectedNeighbor(Loc loc,Set<Loc> mazeLocs)
{
	int row = loc.row;
	int col = loc.col;
	TrailblazerPQueue<Loc> set;
	if(mazeLocs.contains(locs(row+1,col)))
	{
		set.enqueue(locs(row+1,col),randomInteger(0,512));
	}
	if(mazeLocs.contains(locs(row-1,col)))
	{
		set.enqueue(locs(row-1,col),randomInteger(0,512));

	}
	if(mazeLocs.contains(locs(row,col+1)))
	{
		set.enqueue(locs(row,col+1),randomInteger(0,512));
	}
	if(mazeLocs.contains(locs(row,col-1)))
	{
		set.enqueue(locs(row,col-1),randomInteger(0,512));
	}
	return set.dequeueMin();

}
Set<Edge> runPrimsAlgorithm(int& numRows,int& numCols,TrailblazerPQueue<Loc>& neighborLocs,Set<Loc> neighborLocs1,Set<Loc>& mazeLocs)
{
	// source: https://hurna.io/academy/algorithms/maze_generator/prim_s.html
	Set<Edge> result;
	Loc loc1;
		loc1.col = randomInteger(3,numCols-5);
		loc1.row = randomInteger(3,numRows-5);
		mazeLocs.add(loc1);
		foreach(Loc loc in neighbors1(loc1,numRows,numCols))
			{
					neighborLocs.enqueue(loc,randomInteger(0,5096));
					neighborLocs1.add(loc);
			}
		while(!neighborLocs.isEmpty())
		{
			Loc min = neighborLocs.dequeueMin();
			mazeLocs.add(min);
			Loc loc2 = getConnectedNeighbor(min,mazeLocs);
			Edge edge;
			edge.start = loc2;
			edge.end = min;
			result.add(edge);
			foreach(Loc loc in neighbors1(min,numRows,numCols))
			{
				if(!mazeLocs.contains(loc) && !neighborLocs1.contains(loc))
				{
					neighborLocs.enqueue(loc,randomInteger(0,5096));
					neighborLocs1.add(loc);
				}
			}
				
		}
return result;
}
Set<Edge> createMazePrim(int numRows, int numCols)
{
	// cota ar iyos did dros andomebs magram wesit adekvaturad optimizirebulia
	TrailblazerPQueue<Loc> neighborLocs;
	Set<Loc> neighborLocs1; 
	Set<Loc> mazeLocs;
	for(int i = 0;i<numRows;i++)
		for(int j = 0;j<numCols;j++)
		{
			Loc loc;
			loc.col = j;
			loc.row = i;
		}
	return runPrimsAlgorithm(numRows,numCols,neighborLocs,neighborLocs1,mazeLocs);
}
