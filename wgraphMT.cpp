#include "wgraph.h"

weight 
KruskalTrees(wgraph& G, ofstream& fout)
{
	vertex vn = G.size();
	vector<component> KT(vn);  // a quin arbre es troba cada component
	for (vertex v = 0; v < vn; v++) KT[v] = vn; //iniciem KT a vn
	weight Tw = 0;

	weight infty = UINT_MAX; //per buscar el minim

	vector<weight> Kw(vn, 0);

	//cerca de aresta minimal entre components diferents:
	do {
		weight mw = infty;
		vertex mv; index mvi;
		for(vertex v=0; v<vn; v++)
			for (index i = 0; i < G[v].size(); i++)
				if (mw < G[v][i].second && KT[v] != KT[G[v][i].first]) {
					mw = G[v][i].second; mv = v; mvi = i;
				}
		if (mw == infty) break;
	//escriviu l'aresta minimal trobada va de mv(mvi)-mva[mw] || vertex mva=G[mv][mvi].first;
	//uniu les components de mv i mva
	//trobar el maxim i el minim dels KT
		component mKT = min(KT[mv], KT[mva]), MKT = max(KT[mv], KT[mva]);
		Tw += mw;
	// MKT -> mKT falta fer aixo
		Kw[mKT] += Kw[MwT] + mw;
		Kw[MKT] = 0;
	// Escriviu components: vertexs [es arbre minimal]
	} while (true);

}

weight
PrimTrees(wgraph & G, ofstream & fout)
{
	vertex vn = G.size();
	vector<vertex> Pp(vn, vn);
	weight Tw = 0;
	weight infty = UINT_MAX;
	do { //cerca d'aresta minimal 'fora' dels arbres anteriors
		// per montar la branca, buscarem que el predecessor sigui vn
		weight mw = infty;
		vertex mv; index mvi;
		for (vertex v=0; v<vn; v++)
			for (index i=0; i<G[v].size();i++)
				if (mw > G[v][i].second && Pp[v]==vn) { //falta una condicio
					mw = G[v][i].second; mv = v; mvi = i;
				}
		if (mw == infty) break;
		// escriure aresta minimal
		Tw += mw;
		Pp[mv] = mv;
		Pp[mva] = mv; //falta definir mva perque no tingui error
		do { //cerca d'aresta minimal que surti
			weight mw = infty;
			for (vertex v = 0; v < vn; v++)
				for (index i = 0; i < G[v].size(); i++)
					if (mw > G[v][i].second && ) {  //falta una condicio
						mw = G[v][i].second; mv = v; mvi = i;
					}
			if (mw == infty) break;
			// escriure aresta minimal
			Tw += mw;
		} while (true);
	} while (true);
	return Tw;
}
