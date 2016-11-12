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

#ifndef EDGE_H
#define EDGE_H

#include <vector>
#include <algorithm>
#include <memory>

class Edge 
{
public:
    int vx, ed;
    double wt;
    Edge(int vx = -1, int ed = -1, double wt = 0.0) : 
        vx(vx), ed(ed), wt(wt) { }
};

typedef std::shared_ptr<Edge> PtrEdges;

struct SortEdges
{
	bool operator() ( const PtrEdges& ep1, const PtrEdges& ep2  )
	{
		return ep1->wt < ep2->wt;
	}
};




#endif // EDGE_H
