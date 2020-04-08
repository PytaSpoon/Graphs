#include <ctime>
#include "graph.h"
#include "wgraph.h"

 int 
	main()
{
    ofstream fout;
//  Seed rand()
    srand( (unsigned int) time( NULL ) ) ;
//  Complete graph K9 to adjacencies lists
	fout.open( "K9.out" );    
    graph K9 = graph_complete( 9 );
	graph_write( K9, fout );
    fout  << "\nNumber of DFS components: "  << DFS( K9 )  << endl;
    fout  << "\nNumber of BFS components: "  << BFS( K9 )  << endl;
    Dijkstra( K9, 0, fout );
	fout.close();
//  Read graph from graph0.in to adjacencies lists G0
	fout.open( "graph0.out" );    
    graph G0 = graph_read( "graph0.in" );
	graph_write( G0, fout );
    fout  << "\nNumber of DFS components: "  << DFS( G0 )  << endl;
    fout  << "\nNumber of BFS components: "  << BFS( G0 )  << endl;
    Dijkstra( G0, 0, fout );
	fout.close();
//  Random weighted complete graph WK9 with weights 1-9 to weighted adjacencies lists 
	fout.open( "WK9.out" );    
    wgraph WK9 = wgraph_complete( 9, 9 );
	wgraph_write( WK9, fout );
	fout.close();
//  Read weighted graph from wgraph0.in to weighted adjacencies lists WG0
	fout.open( "wgraph0.out");    
    wgraph WG0 = wgraph_read( "wgraph0.in" );
	wgraph_write( WG0, fout );
	fout.close();
//
//  Ending
//
    cout << "Press enter to finish..." << endl;
    cin.get();
}
