#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
 using namespace std;
 typedef unsigned int vertex;
 typedef unsigned int edge;
 typedef unsigned int index; 
 typedef unsigned int degree; 
 typedef unsigned int component;
 typedef unsigned int weight;
 typedef vector<vector<pair<vertex,weight>> > wgraph;
 wgraph wgraph_complete( index n,  weight Mw );
 wgraph wgraph_read( string fname );
 void wgraph_write(  wgraph& G, ofstream& fout );
 