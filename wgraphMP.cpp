#include "wgraph.h"

// volem que retorni un weight,- FUNCIÓ 1
weight
Dijkstra(wgraph& G, vertex sv, vertex tv)
{
	vertex vn = G.size();
	//  Inialize vertices as unlabeled
	vector<bool> Dl(vn, false);
	//  Infinity for lengths
	weight infty = UINT_MAX;
	//  Inialitize distance to sv to infty for all vertices but sv
	vector<weight> Dd(vn, infty);
	Dd[sv] = 0;
	//  Vertex mdv with minimum distance to starting vertex sv: sv
	vertex mdv = sv;
	do {
		//  Label mdv and check distance from sv to its adjacents	
		Dl[mdv] = true;
		for (index i = 0; i < G[mdv].size(); i++)
			if (Dd[G[mdv][i].first] > Dd[mdv] + G[mdv][i].second)
				Dd[G[mdv][i].first] = Dd[mdv] + G[mdv][i].second;
		//  Find new not labeled vertex mdv with minimum distance to sv
		weight md = infty;
		mdv = vn;
		for (vertex v = 0; v < vn; v++)
			if (md > Dd[v] && !Dl[v]) {
				md = Dd[v];
				mdv = v;
			}
	} while (mdv < vn && mdv!=tv);
		if (Dd[tv] < infty)
			return Dd[tv];
}


// volem que retorni un weight,- FUNCIÓ 2
weight
Dijkstra(wgraph& G, vertex sv)
{
	vertex vn = G.size();
	//  Inialize vertices as unlabeled
	vector<bool> Dl(vn, false);
	//  Infinity for lengths
	weight infty = UINT_MAX;
	//  Inialitize distance to sv to infty for all vertices but sv
	vector<weight> Dd(vn, infty);
	Dd[sv] = 0;
	//  Vertex mdv with minimum distance to starting vertex sv: sv
	vertex mdv = sv;
	do {
		//  Label mdv and check distance from sv to its adjacents	
		Dl[mdv] = true;
		for (index i = 0; i < G[mdv].size(); i++)
			if (Dd[G[mdv][i].first] > Dd[mdv] + G[mdv][i].second)
				Dd[G[mdv][i].first] = Dd[mdv] + G[mdv][i].second;
		//  Find new not labeled vertex mdv with minimum distance to sv
		weight md = infty;
		mdv = vn;
		for (vertex v = 0; v < vn; v++)
			if (md > Dd[v] && !Dl[v]) {
				md = Dd[v];
				mdv = v;
			}
		//initialize
		weight MDd = 0;
	} while (mdv < vn && mdv != tv);  //aixo cal modificarho
	if (Dd[tv] < infty)
		return MDd;
}


// dijkstra modificada per wgraphs
void
Dijkstra(wgraph& G, vertex sv, ofstream& fout)
{
	vertex vn = G.size();
	//  Inialize vertices as unlabeled
	vector<bool> Dl(vn, false);
	//  Infinity for lengths
	weight infty = UINT_MAX;
	//  Inialitize distance to sv to infty for all vertices but sv
	vector<weight> Dd(vn, infty);
	Dd[sv] = 0;
	//  Vertex mdv with minimum distance to starting vertex sv: sv
	vertex mdv = sv;
	do {
		//  Label mdv and check distance from sv to its adjacents	
		Dl[mdv] = true;
		for (index i = 0; i < G[mdv].size(); i++)
			if (Dd[G[mdv][i].first] > Dd[mdv] + G[mdv][i].second)
				Dd[G[mdv][i].first] = Dd[mdv] + G [mdv][i].second;
		//  Find new not labeled vertex mdv with minimum distance to sv
		weight md = infty;
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

// dijkstra tree

void
Dijkstra_Tree(wgraph& G, vertex sv, ofstream& fout)
{
	vertex vn = G.size();
	// initialize vertice
	vector<vertex> Dp(vn, vn);

	//  Infinity for lengths
	weight infty = UINT_MAX;
	//  Inialitize distance to sv to infty for all vertices but sv
	vector<weight> Dd(vn, infty);
	Dd[sv] = 0;
	//  Vertex mdv with minimum distance to starting vertex sv: sv
	vertex mdv = sv;
	do {
		//  Label mdv and check distance from sv to its adjacents	
		Dp[mdv] = true;
		for (index i = 0; i < G[mdv].size(); i++) {
			if (Dd[G[mdv][i].first] > Dd[mdv] + G[mdv][i].second)
				Dd[G[mdv][i].first] = Dd[mdv] + G[mdv][i].second;
				Dp[G[mdv][i].first] = mdv; G[mdv][i].first;
		}
		//  Find new not labeled vertex mdv with minimum distance to sv
		weight md = infty;
		mdv = vn;
		for (vertex v = 0; v < vn; v++)
			if (md > Dd[v] && !Dp[v]) {
				md = Dd[v];
				mdv = v;
			}
	} while (mdv < vn);
	fout << "\nCamins minimals " << endl;
	for (vertex v = 0; v < vn; v++)
		if (Dd[v] < infty) { // tbe podem posar si el pare es vn
			vertex pv = v;
			fout << v;
			while (pv != sv) {
				pv = Dp[pv];
				fout << '_' << pv;
			}
		}
		else
			fout << v << "\tNot connected" << endl;
}

