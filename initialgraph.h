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

#ifndef INITIALGRAPH_H
#define INITIALGRAPH_H

#include "edge.h"

template <class Edge>
class InitialGraph
{ 
private:
    int Vert, Edg;
    bool dirG;
    std::vector <std::vector<PtrEdges>> adjecency;

public:
    InitialGraph(int V, bool dirG = false) :
        adjecency(V), 
        Vert(V), 
        Edg(0), 
        dirG(dirG)
    { 
        for ( int i = 0; i < V; i++ ) adjecency[i].resize( V );
    }

    int V() const { return Vert; }
    int E() const { return Edg; }

    bool directed() const { return dirG; }
    
    void insert( PtrEdges e )
    { 
        int vx = e->vx;
        int ed = e->ed;
        if (adjecency[vx][ed] == 0) Edg++;
        adjecency[vx][ed] = e;
        if (!dirG) adjecency[ed][vx] = e;
    } 

    void remove(PtrEdges e)
    { 
        int vx = e->vx;
        int ed = e->ed;

        if (adjecency[vx][ed] != 0)  
            Edg--;

        adjecency[vx][ed] = 0;

        if (!dirG) adjecency[ed][vx] = 0; 
    } 

    PtrEdges edge(int vx, int ed) const 
    { return adjecency[vx][ed]; }

	// Get the weighted edges
	void edges( std::vector<PtrEdges>& edges )
	{
		for( int u = 0; u < V(); ++u )
		{
			InitialGraph<Edge>::adjIT A(*this, u); 

			for ( PtrEdges e = A.beg(); !A.end(); e = A.nxt() ) 
			{ 
				if ( NULL != e )
				{
					edges.push_back( e );
				}
			}
		}
	}

    class adjIT;
    friend class adjIT;
};

template <class Edge>
class InitialGraph<Edge>::adjIT
{ 
private:

    const InitialGraph &G;
    int i, vx;

public:
    adjIT(const InitialGraph<Edge> &G, int vx) : 
        G(G), 
        vx(vx), 
        i(0) {}

    PtrEdges beg() { i = -1; return nxt(); }

    PtrEdges nxt()
    {
        for (i++; i < G.V(); i++)
            if (G.edge(vx, i)) 
                return G.adjecency[vx][i];
        
        return 0;
    }

    bool end() const { return i >= G.V(); }
};



#endif // INITIALGRAPH_H
