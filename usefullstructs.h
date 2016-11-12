/*
 * <one line to give the library's name and an idea of what it does.>
 * Copyright (C) 2016  <copyright holder> <email>
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 * 
 */

#ifndef USEFULLSTRUCTS_H
#define USEFULLSTRUCTS_H

#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include <unistd.h>
#include<bits/stdc++.h>

#include "edge.h"
#include "initialgraph.h"


// A structure to represent a subGraph 
struct subGraph
{
    int ancestor;
    int cost;
};
typedef subGraph SubGraph;

// function to find set of an element i

int getSet( SubGraph subNodes[], int i )
{
    // find root and make root as ancestor of i 
    if (subNodes[i].ancestor != i)
        subNodes[i].ancestor = getSet(subNodes, subNodes[i].ancestor);
 
    return subNodes[i].ancestor;
}

// A function that make union of two sets of x and y by cost
void addToSet( SubGraph subNodes[], int x, int y )
{
    int xfather = getSet( subNodes, x );
    int yfather = getSet( subNodes, y );
 
    // Attach smaller cost tree under root of high cost tree
    if ( subNodes[xfather].cost < subNodes[yfather].cost )
	{
        subNodes[xfather].ancestor = yfather;
	}
    else if (subNodes[xfather].cost > subNodes[yfather].cost)
	{
        subNodes[yfather].ancestor = xfather;
	}
    else
    {
		// If ranks are same, then make one as root and increment
		// its cost by one
        subNodes[yfather].ancestor = xfather;
        subNodes[xfather].cost++;
    }
}


// Kruskal's algorithm to find MST
void kruskal( InitialGraph<Edge>* graph, std::vector<PtrEdges>& mst,std::vector<PtrEdges>& others )
{
    const int V = graph->V();
 
    // Sort edges in non-decreasing order of their weight
	std::vector<PtrEdges> edges;
	graph->edges( edges );
	
	std::sort(edges.begin(), edges.end(), SortEdges() );
	std::unique_ptr<subGraph[]> subNodes( new subGraph[ V ]() );
 
    // Create V subNodes with
    for ( int vx = 0; vx < V; ++vx )
    {
        subNodes[vx].ancestor = vx;
        subNodes[vx].cost = 0;
    }

	for ( std::vector<PtrEdges>::iterator it = edges.begin(); it != edges.end(); ++it )
	{
		PtrEdges edgePtr = *it;

		int x = getSet( subNodes.get(), edgePtr->vx );
		int y = getSet( subNodes.get(), edgePtr->ed );
		
		
		// check for cycle
		if ( x != y )
		{
		
			mst.push_back( edgePtr );
			addToSet( subNodes.get(), x, y );
		}
		else
			others.push_back(edgePtr);
	}
}


void getEd(InitialGraph<Edge>* graph,std::vector<PtrEdges>& mst,std::vector<int>& mar,std::vector<int>& nonMar){
	const int V = graph->V();
	
	std::vector<PtrEdges> edges;
	std::vector<PtrEdges> temp;
	std::vector<PtrEdges> temp2;

	std::vector<int> noMartemp;
	graph->edges( edges );
	//temp2 ( mst);
	//while(mar.size()!=5){
	for ( std::vector<PtrEdges>::iterator it = edges.begin(); it != edges.end(); ++it )
	{
		for(int i = 0; i<mar.size();i++){
			for(int j = 0; j<nonMar.size();j++){
					
				PtrEdges edgePtr = *it;
				if(edgePtr->vx == mar[i] && edgePtr->ed == nonMar[j]  ){
					temp.push_back(edgePtr);
				}
			}			
		}
	}
	
	std::sort(temp.begin(), temp.end(), SortEdges() );

	
	mst.push_back(temp[0]);
	std::vector<PtrEdges>::iterator ii = temp.begin();
	PtrEdges ptrNodeToAdd = *ii;
	
	mar.push_back(ptrNodeToAdd->ed);
	nonMar.erase(std::remove(nonMar.begin(), nonMar.end(), ptrNodeToAdd->ed), nonMar.end());
	
	
	
	std::cout<<mar.size()<<" " << nonMar.size()<<std::endl;
	//}
	/*
	graph->edges( edges );
	
	for ( std::vector<PtrEdges>::iterator it = edges.begin(); it != edges.end(); ++it )
	{
		PtrEdges edgePtr = *it;
		
		if(edgePtr->vx == i){
			//std::cout<< edgePtr->vx << " " << edgePtr->ed << " " << edgePtr->wt <<std::endl;
			mst.push_back(edgePtr);
		}
	}
	
	std::sort(mst.begin(), mst.end(), SortEdges() );
	
	std::vector<PtrEdges> bst;
		std::vector<PtrEdges> VS;

	bst.push_back( mst[0]);
	
	for ( std::vector<PtrEdges>::iterator it = edges.begin(); it != edges.end(); ++it )
	{
		PtrEdges edgePtr = *it;
		
		if(edgePtr != bst[0]){
			//std::cout<< edgePtr->vx << " " << edgePtr->ed << " " << edgePtr->wt <<std::endl;
			VS.push_back(edgePtr);
		}
	}
	
	std::cout<<VS.size();
	
	edges.clear();
	edges.swap(VS);
	
	mst.clear();
	*/
	
	
}

void prim( InitialGraph<Edge>* graph, std::vector<PtrEdges>& mst,std::vector<PtrEdges>& others )
{
	const int V = graph->V();
	std::vector<int> nodeM;
	std::vector<int> nodeO;
	
	std::vector<PtrEdges> edges;
	
	graph->edges( edges );
	
	nodeM.push_back(0);
	
	for(int i=1;i<50;++i){
		nodeO.push_back(i);
	}
	
	while(nodeM.size()!=10){
		getEd( graph,mst, nodeM,nodeO);
	}
	
	
}


#endif // USEFULLSTRUCTS_H
