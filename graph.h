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
 typedef unsigned int length;
 typedef vector<vector<vertex> > graph;
 graph graph_complete( index n );
 graph graph_read( string fname );
 graph graph_cycle(index n);
 void graph_write(  graph& G, ofstream& fout );
 component BFS( graph &G );
 component DFS( graph &G );
 component BFS_Trees(graph& G, ofstream& fout);
 component DFS_Trees(graph& G, ofstream& fout);
 void Dijkstra( graph &G, vertex sv, ofstream& fout );
 
 