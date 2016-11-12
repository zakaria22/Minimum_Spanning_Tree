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

#include "edge.h"
#include "initialgraph.h"
#include "usefullstructs.h"


std::ofstream output_tikz_code("graph.dot"); // name of the file that will be produced
std::ostringstream dot_code;    // the dot code that will be printed in dot file

// to Skip some lines while reading file
void skip_lines(std::ifstream& pStream, size_t pLines)
{
    std::string s;
    for (; pLines; --pLines)
        std::getline(pStream, s);
}

//get the graph from file
void reader(InitialGraph<Edge>* graph){
  std::string line;
  std::ifstream myfile ("LAHYANI_Zakaria.txt");
  int V = 0; // Number of vertices in graph
  int E = 0; // Number of edges in graph
 
 if (myfile.is_open())
  {
   std::getline (myfile,line) ;
    
     // cout << line << '\n';
   
    std::stringstream stream(line);
    stream  >> V;
    stream >> E;
    
    skip_lines(myfile,50);

    while (std::getline (myfile,line)) {
      std::stringstream stream(line);
      int d,s =0;
      double ed=0.0;
      
      stream >> s;
      stream >> d;
      stream >> ed;
      graph->insert( PtrEdges( new Edge( s-1,d-1,ed) ) );
      
    }
    myfile.close();

  }
  else std::cout << "Unable to open file"; 
}

//save result as a dot file & compile it to svg
void exportToDot( std::vector<PtrEdges>& mst,std::vector<PtrEdges>& others){
	  
  dot_code << 
                "graph { \n"<<
                "rankdir=LR;\n";

		
		for(std::vector<PtrEdges>::const_iterator it = mst.begin(); it != mst.end(); ++it){
			dot_code <<(it->get()->vx)+1 << " -- " << (it->get()->ed )+1 <<"[label=\"" << it->get()->wt << "\",color=red,penwidth=2.0];\n";
		}
		for(std::vector<PtrEdges>::const_iterator it = others.begin(); it != others.end(); ++it){
			dot_code <<(it->get()->vx)+1 << " -- " << (it->get()->ed )+1 <<"[label=\"" << it->get()->wt << "\",color=black,penwidth=2.0];\n";
		}
dot_code << 
               " }\n";
output_tikz_code << dot_code.str();
 system("dot -T svg graph.dot -o graph.svg");
}


int main()
{
	InitialGraph<Edge>* graph = new InitialGraph<Edge>( 50, true ); 
	reader(graph);

	std::vector<PtrEdges> mst; //Edges representing the mst 
	std::vector<PtrEdges> others;
	
	
	//prim(graph,mst,others);
	
	kruskal( graph, mst,others );
	exportToDot(mst,others);
 
	return 0;
}
