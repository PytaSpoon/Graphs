#include "graph.h"
// 
//  Complete graph with vn vertices to adjacencies lists (graph)
//
 graph
    graph_complete( index n )
{    
    vertex vn = n;
    graph Kn( vn );
    for( vertex v=0; v<vn; v++) 
        for( vertex u=v+1; u<vn; u++ ) {
             Kn[v].push_back( u );
             Kn[u].push_back( v );
        } 
    return Kn;
}

//Graphs complets per cicles, retorna les llistes d'adjacencia
 graph
	 graph_cycle(index n)
 {
	 vertex vn = n;
	 graph Kn(vn);
	 for (vertex v = 0; v < vn; v++) {
		 if (v == vn - 1) {
			 Kn[v].push_back(0);
		 }
		 else {
			 Kn[v].push_back(v + 1);
		 }
	 }
	 return Kn;
 }


// 
//  Read from file fname of edges to adjacencies lists (graph)
//
 graph 
	graph_read( string fname )
{    
	ifstream fin;
    fin.open( fname.c_str() );    
    if( fin.fail() ) {
        cerr << "unable to open file " << fname.c_str() << " for reading" << endl;
        exit( 1 );
    }
 	vertex vn;
    edge en;
	fin >> vn >> en;
	graph G( vn );
    for( edge e=0; e<en; e++ ) {
         vertex v, u;
         fin >> v >> u; 
         G[v].push_back(u);
         if( u != v ) 
             G[u].push_back(v);
	}    
    return G;
}
// 
//  Write from adjacencies lists (graph) to stream
//  - vertices and edges numbers
//  - edges
  void 
	graph_write(  graph& G, ofstream& fout )
{    
//  Vertices number 
	vertex vn = G.size();
//  Count edges number from adjacencies lists
//  PLEASE CORRECT WHEN THERE ARE LOOPS
    edge en = 0; 
    for( vertex v = 0; v < vn; v++ ) 
         en += G[v].size();
    en /= 2;
//  Write edges         
    fout << "Graph with " << vn << " vertices and " << en << " edges " << endl;
    fout << "Adjacencies lists" << endl;
    for( vertex v=0; v<vn; v++ )  {
		fout << v << "\t:";
        for( index i=0; i<G[v].size(); i++) 
            fout << "\t" << G[v][i];
        fout << endl;
    }
    fout << "Edges" << endl;
    for( vertex v = 0; v < vn; v++ ) 
        for( index i = 0; i < G[v].size(); i++ ) 
            if( v <= G[v][i] )
                fout << v << "-" << G[v][i] << endl;
}

  graph
	  graph_king(index n1, index n2)
  {
	  vertex vn = n1 * n2;
	  graph Kg(vn);
	  for (index i1 = 0; i1 < n1; i1++)
		  for (index i2 = 0; i2 < n2; i2++) {
			  vertex v = i1 * n2 + i2;
			  if (i2 < n2 - 1) {
				  Kg[v].push_back(v + 1);
			  }
			  Kg[v + 1].push_back(v); //nose si aixo esta ben colocat
			  if (i1 < n1 - 1) {
				  Kg[v].push_back(v + n2); //aixo tampoc se si esta be
				  // v - v+n2
			  }
		  }
	  return Kg;
  }


  // proposta de benseny, per fer el taulell li pasem els dos index

  void
	  graph_board(graph& G, index n1, index n2, ofstream& fout)
  {
	  //  Vertices number 
	  vertex vn = G.size();
	  //  Count edges number from adjacencies lists
	  //  PLEASE CORRECT WHEN THERE ARE LOOPS
	  edge en = 0;

	  // la sortida:
	  // <<"c"<<v/n2<<",","<<v%n2<<")"<<

	  for (vertex v = 0; v < vn; v++)
		  en += G[v].size();
	  en /= 2;
	  //  Write edges         
	  fout << "Graph with " << vn << " vertices and " << en << " edges " << endl;
	  fout << "Adjacencies lists" << endl;
	  for (vertex v = 0; v < vn; v++) {
		  fout << v << "\t:";
		  for (index i = 0; i < G[v].size(); i++)
			  fout << "\t" << G[v][i];
		  fout << endl;
	  }
	  fout << "Edges" << endl;
	  for (vertex v = 0; v < vn; v++)
		  for (index i = 0; i < G[v].size(); i++)
			  if (v <= G[v][i])
				  fout << v << "-" << G[v][i] << endl;
	  // fem que escrigui una matriu en que en cada casella hi hagi el grau de la casella (G[v].size())
  }
