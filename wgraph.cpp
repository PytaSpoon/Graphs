#include "wgraph.h"
// 
//  Weighted complete graph with vn vertices and random weights up to Mw 
//  to weighted adjacencies lists (wgraph) 
//
 wgraph
    wgraph_complete( index n,  weight Mw )
 {    
    vertex vn = n;
    wgraph WKn( vn );
    for( vertex v = 0; v < vn; v++ ) 
        for( vertex u = v+1; u<vn; u++ ) {
			weight w = rand()%Mw+1;
			WKn[v].push_back(pair<vertex,weight>(u,w));
			WKn[u].push_back(pair<vertex,weight>(v,w));
        }
    return WKn;
}
// 
//  Read from file fname of weighted edges to weighted adjacencies lists
//
 wgraph
	wgraph_read( string fname )
 {    
	ifstream fin;
    fin.open(fname.c_str());    
    if (fin.fail()) {
        cerr << "unable to open file " << fname.c_str() << " for reading" << endl;
        exit(1);
    }
 	vertex vn;
    edge en;
	fin >> vn >> en;
	wgraph G( vn );
    for( edge e=0; e<en; e++ ) {
        vertex u, v;
        weight w;
        fin >> u >> v >> w; 
        G[u].push_back(pair<vertex,weight>(v,w));
        if( u != v ) 
            G[v].push_back(pair<vertex,weight>(u,w));
    }    
    return G;
}
// 
//  Write from weighted adjacencies lists (wgraph) to stream
//  - vertices and edges numbers
//  - weighted edges
//  - degrees and sorted degrees
  void 
	wgraph_write( wgraph& G, ofstream& fout )
 {    
//  Vertices number 
	vertex vn = G.size();
//  Count edges number from adajacency matrix
    edge en = 0; 
    for( vertex v = 0; v < vn; v++) 
         en += G[v].size();
    en /= 2;
//  Write edges         
    fout << "WGraph with " << vn << " vertices and " << en << " edges " << endl;
    fout << "Weighted adjacency lists" << endl;
//  Allocate/read weighted adjacent pairs
    for( vertex v = 0; v < vn; v++ ) {
        fout << v << ":";
        for( index i = 0; i < G[v].size(); i++)  
            fout << " " << G[v][i].first << "[" << G[v][i].second << "] ";
        fout << endl;
    }
    fout << endl;
    fout << "Weighted edges" << endl;
    for( vertex v = 0; v < vn; v++ ) 
        for( index i = 0; i < G[v].size(); i++) 
            if( v <= G[v][i].first )
                fout << v << "-" << G[v][i].first <<  "[" << G[v][i].second << "] " << endl;
             
 }
