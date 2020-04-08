//
//	TREE SEARCH IN GRAPHS
//  - BFS method
//  - DFS method
//  - Dijkstra (without weights) method
//
//  R --> ROOT (ARREL)
//  T --> TREE (ARBRE)
#include "graph.h"
//
//  Breadth First Search: returns components/trees number
//
component
BFS(graph& G)
{
	vertex vn = G.size();
	component Tn = 0;
	//  Vertices list
	vector<vertex> BFSv(vn);
	//  Label vertices as unvisited
	vector<bool> BFSl(vn, false);
	//  List index
	index BFSn = 0;
	//  Find non labeled vertex as root vertex rv of new component/tree Tn
	for (vertex rv = 0; rv < vn; rv++)
		if (!BFSl[rv]) {
			//  Actualize display index, DESPLACEM L'INDEX
			index BFSi = BFSn;
			//  New root rv found for new component
			Tn++;
			//  Label and list rv
			BFSl[rv] = true; // EL MARQUEM JA VISITAT
			BFSv[BFSn++] = rv; // POSEM RV A LA POSICIÓ BFSN I FAIG CORRER L'INDEX, AQUEST ++ L'HEM DE POSAR DESPRES, AUGEMENTEM DESPRÉS L'INDEX
			if (G[rv].size())
				do {
					//  New vertex v to display 
					vertex v = BFSv[BFSi++];
					for (index i = 0; i < G[v].size(); i++)
						if (!BFSl[G[v][i]]) {
							//  Label and list adjacent G[v][i]
							BFSl[G[v][i]] = true;
							BFSv[BFSn++] = G[v][i];
						}
				} while (BFSi < BFSn);
		}
	return Tn;
}

// BFS TREES

component
BFS_Trees(graph & G, ofstream & fout)
{
	vertex vn = G.size();
	component Tn = 0;
	//  Vertices list
	vector<vertex> BFSv(vn);
	//  Label vertices as unvisited
	vector<vertex> BFSp(vn, vn);
	//  List index
	index BFSn = 0;
	//  Index de visita
	vector<index> BFSind(vn);
	//  Find non labeled vertex as root vertex rv of new component/tree Tn
	for (vertex rv = 0; rv < vn; rv++)
		if (BFSp[rv]== vn) {
			//  Actualize display index, DESPLACEM L'INDEX
			index BFSi = BFSn;
			BFSind[rv] = BFSn;
			//  Profunditat de l'arrel
			vector<length> BFSd(vn);
			//  Label and list rv
			BFSp[rv] = rv; // EL MARQUEM JA VISITAT I MARQUEM QUE ÉS EL VERTEX RV	
			BFSd[rv] = 0;  // PROFUNDITAT
			BFSv[BFSn++] = rv; // POSEM RV A LA POSICIÓ BFSN I FAIG CORRER L'INDEX, AQUEST ++ L'HEM DE POSAR DESPRES, AUGEMENTEM DESPRÉS L'INDEX
			//  New root rv found for new component
			Tn++;
			if (G[rv].size())
				do {
					//  New vertex v to display 
					vertex v = BFSv[BFSi++];
					for (index i = 0; i < G[v].size(); i++)
						if (!BFSp[G[v][i]]==vn) {
							//  Label and list adjacent G[v][i]
							BFSp[G[v][i]] = v;
							BFSind[G[v][i]] = BFSn;
							BFSd[G[v][i]] = BFSd[v] + 1; // afegim que la profunditat del vertex es la del pare+1
							BFSv[BFSn++] = G[v][i];
						}
				} while (BFSi < BFSn);
		}
	// Escriure v BFSind[v] quin es el predecessor BFSp[v], la profunditat BFSd[v]
	// Escriure les arestes (funcio graph_write) les escrivim de v al seu adjacent v - G[v][i]
	// Indiquem si les arestes són de l'arbre o no
	// Per trobar el predecessor en comú, el camí de un vertex a l'altre, igualem profunditats i despres tirem enrera,
	// fins a trobar el que és comú i així acabem trobant el cicle.
	// Per saber si la aresta és o no de l'arbre, fer un if mirant si són adjacents en els dos sentits, si un és predecessor
	// o l'altre.
	return Tn;
}
//
//  Recursive function for Depth First Search from v
//
 void 
    DFS( graph &G, vector<bool> &DFSl,  vertex v ) 
{
	for( index i=0; i<G[v].size(); i++ ) 
        if( !DFSl[G[v][i]] ) {
		//  Label adjacent vertex as visited
            DFSl[G[v][i]] = true;
		//  DFS recursive for non visited adjacent vertices   
            DFS( G, DFSl, G[v][i] );
        }
}
//
//  Depth First Search: returns components/trees number
//
 component 
    DFS(  graph &G ) 
{
    vertex vn = G.size();
//  Initialize number of components/trees to 0
    component Tn = 0;
//  Label vertices as unvisited
    vector<bool> DFSl( vn, false );
    for( vertex rv=0; rv<vn; rv++) 
         if( !DFSl[rv] ){
		 //  New root found
		 //  Count new component
			 Tn++;
		 //  Label root vertex
			 DFSl[rv] = true;
		 //  Display component
             DFS( G, DFSl, rv );
         }
    return Tn;
}

// DFS_Trees

 void
	 DFS_Trees(graph& G, index DFSn, vector<index> DFSind, vector<vertex>& DFSp, vector<length> DFSd, vertex v)
 {
	 vertex vn = G.size();
	 for (index i = 0; i < G[v].size(); i++)
		 if (DFSp[G[v][i]]==vn) {
			 //  Label adjacent vertex as visited
			 DFSp[G[v][i]] = v;
			 // Cal fer els DFSind[G[v][i]=...
			 // Cal fer els DFSd[G[v][i]=...
			 // Cal fer els DFSn[G[v][i]=...
			 //  DFS recursive for non visited adjacent vertices   
			 DFS_Trees(G, DFSn, DFSind, DFSp, DFSd, G[v][i]);
		 }
 }

 component
	 DFS_Trees(graph& G, ofstream& fout)
 {
	 vertex vn = G.size(); index DFSn = 0;
	 //  Initialize number of components/trees to 0
	 component Tn = 0; vector<index> DFSind(vn);
	 //  Label vertices as unvisited
	 vector<vertex> DFSp(vn, vn); vector<length> DFSd(vn);
	 for (vertex rv = 0; rv < vn; rv++)
		 if (DFSp[rv]==vn) {
			 //  New root found
			 //  index augment
			 DFSind[rv] = DFSn++;
			 //  marquem la profunditat a zero
			 DFSd[rv] = 0;
			 //  Label root vertex
			 DFSp[rv] = rv;
			 //  Count new component
			 Tn++;
			 //  Display component
			 DFS_Trees(G, DFSn, DFSind, DFSp, DFSd, rv);
		 }
	 // Escriure tota la informació igual amb BFS
	 return Tn;
 }


//  Minimal path lengths by Dijkstra's method to stream
//  - Distances to all vertices: lengths of minimal paths
//
 void
    Dijkstra(  graph &G,  vertex sv, ofstream& fout ) 
{
    vertex vn = G.size();
//  Inialize vertices as unlabeled
    vector<bool> Dl( vn, false );
//  Infinity for lengths
	length infty = UINT_MAX;
//  Inialitize distance to sv to infty for all vertices but sv
	vector<length> Dd( vn, infty );
	Dd[sv]=0;
//  Vertex mdv with minimum distance to starting vertex sv: sv
	vertex mdv = sv; 
	do {
	//  Label mdv and check distance from sv to its adjacents	
		Dl[mdv] = true;
		for( index i=0; i<G[mdv].size(); i++ ) 
			if( Dd[G[mdv][i]] > Dd[mdv]+1 )	
				Dd[G[mdv][i]] = Dd[mdv]+1; 
	//  Find new not labeled vertex mdv with minimum distance to sv
		length md = infty;
		mdv = vn;
		for( vertex v=0; v<vn; v++ )
			if( md > Dd[v] && !Dl[v] ) {
				md = Dd[v];
				mdv = v;
			}
	} while( mdv<vn );
    fout << "\nDistances from starting vertex " << sv << endl;
	for( vertex v=0; v<vn; v++ )
        if( Dd[v]<infty )
		    fout << v << "\t" << Dd[v]  << endl;
        else
            fout << v << "\tNot connected" << endl;
}


 //evolucio pels escacs s1,s2 casella de sortida

 void
	 Dijkstra_chess(graph& G, index n1, index n2, index s1, index s2, vertex sv, ofstream& fout)
 {
	 vertex vn = G.size();
	 vertex sv = s1 * n2 + s2;
	 //  Inialize vertices as unlabeled
	 vector<bool> Dl(vn, false);
	 //  Infinity for lengths
	 length infty = UINT_MAX;
	 //  Inialitize distance to sv to infty for all vertices but sv
	 vector<length> Dd(vn, infty);
	 Dd[sv] = 0;
	 //  Vertex mdv with minimum distance to starting vertex sv: sv
	 vertex mdv = sv;
	 do {
		 //  Label mdv and check distance from sv to its adjacents	
		 Dl[mdv] = true;
		 for (index i = 0; i < G[mdv].size(); i++)
			 if (Dd[G[mdv][i]] > Dd[mdv] + 1)
				 Dd[G[mdv][i]] = Dd[mdv] + 1;
		 //  Find new not labeled vertex mdv with minimum distance to sv
		 length md = infty;
		 mdv = vn;
		 for (vertex v = 0; v < vn; v++)
			 if (md > Dd[v] && !Dl[v]) {
				 md = Dd[v];
				 mdv = v;
			 }
	 } while (mdv < vn);
	 fout << "\nDistances from starting vertex " << sv << endl;
	 for (vertex v = 0; v < vn; v++)
		 if (Dd[v] < infty)
			 fout << v << "\t" << Dd[v] << endl;
		 else
			 fout << v << "\tNot connected" << endl;
 }