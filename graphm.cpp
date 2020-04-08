#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
 using namespace std;

// PRÀCTICA 1
// AUTOR: PERE LÓPEZ GUTIÉRREZ
// NIUB: 16800965
// 
//  Complete graph to adjacency matrix
//
 vector<vector<int>>
    graphM_complete( int n )
 {    
//  Initialize adjacency matrix	to 0
    vector<vector<int>> KnM( n, vector<int>( n, 0 ) );
//  Fill adjacency matrix taking into account all the possible edges i-k
//  Leave the diagonal with 0
    for( int i=0; i<n; i++ ) 
		for (int k = i+1; k<n; k++)
			KnM[i][k] = KnM[k][i]=1;
    return KnM;
}

// Complete cycle graph to adjacency matrix

 vector<vector<int>>
	 graphM_cycle(int n)
 {
// Initialize again adjacency matrix to 0
	 vector<vector<int>> CnM(n, vector<int>(n, 0));
// Fill with ones
	 for (int i=0; i<n-1; i++)
		 CnM[i][i+1] = CnM[i+1][i] = 1;
	 CnM[n-1][0] = CnM[0][n-1] = 1;
	 return CnM;
 }

// Complete bipartite graph to adjacency matrix

 vector<vector<int>>
	 graphM_bipartite(int n, int m) {
	 vector<vector<int>> B(n + m, vector<int>(n + m, 0));

	 for (int i = 0; i < n; i++) {
		 for (int k = n; k < (n + m); k++) {
			 B[i][k] = B[k][i] = 1;
		 }
	 }
	 return B;
 }
// Complete stars graph to adjacency matrix

 vector<vector<int>>
	 graphM_stars(int n) 
 {
	 vector<vector<int>> S(n, vector<int>(n, 0));
	 for (int i = 0; i < n - 1; i++) {
		 S[n - 1][i] = S[i][n - 1] = 1;
	 }
	 return S;
 }

// Complete wheel graph to adjacency matrix

 vector<vector<int>>
	 graphM_wheel(int n)
 {
//  Initialize adjacency matrix	to 0
	 vector<vector<int>> WnM(n, vector<int>(n, 0));
//  Fill with ones
	 for (int i=0; i<n-1; i++)
	 {
		 WnM[i][n-1] = WnM[n-1][i] = 1;
		 WnM[i][i+1] = WnM[i+1][i] = 1;
	 }
	 WnM[n-2][0] = WnM[0][n-2] = 1;
	 return WnM;
 }

 // Complete grid graph to adjacency matrix

 vector<vector<int>>
	 graphM_grid(int n, int m)
 {
//  Initialize adjacency matrix	to 0
	 vector<vector<int>> GnM(n * m, vector<int>(n * m, 0));
//  Fill with 1
	 int i = 0;
	 int j = 0;
	 for (int i = 0; i<n; i++) 
	 {
		 for (int j=1; j<m; j++)
		 {
			 GnM[i*m + j][i*m + j-1] = GnM[i*m - 1+j][i*m + j] = 1;
		 }
	 }
	 for (int i = 1; i<n; i++)
	 {
		 for (int j = 0; j<m; j++) 
		 {
			 GnM[i*m + j][i*m - m+j] = GnM[i*m - m+j][i*m + j] = 1;
		 }
	 }
	 return GnM;
 }

//  Read SIMPLE graph from file fname of edges to adjacency matrix



 vector<vector<int>>
    graphM_read( string fname )
 {    
	ifstream fin;
    fin.open( fname.c_str() );    
    if( fin.fail() ) {
        cerr << "unable to open file " << fname.c_str() << " for reading" << endl;
        exit( 1 );
    }
 // Read vertices and edges numbers
	int n, m;
	fin >> n >> m;
 // Initialize adjacency matrix	to 0
    vector<vector<int>> M( n, vector<int> (n, 0) );
 // Fill adjacency matrix taking into account all the edges u-v
    for( int j=0; j<m; j++ ) {
         int u, v;
         fin >> u >> v;
		 if (u == v){
			 M[u][v] = M[u][v] + 2;  //these are the elements of the diagonal
		 }
		 else {
			 M[u][v] = M[u][v] + 1;
			 M[v][u] = M[u][v]; //due to the simmetry
		 }
    }    
    return M;
  }
// 
//  Write SIMPLE graph from adjacency matrix to file stream
//  - vertices and edges numbers
//  - adjacency matrix
//  - edges
//  - sorted degrees
//
//  IMPORTANT: This function has a bug that must be corrected
//  IMPORTANT: This function should be adapted to multigraphs
  void 
	  graphM_write( vector<vector<int>> & M, ofstream & fout)
  {
	  //  Vertices number 
	  int n = M.size();
	  //  Count edges number from adjacency matrix
	  int m = 0;
	  for (int i = 0; i < n; i++) {
		  for (int k = 0; k <= i; k++) {
			  m = m + M[i][k];
		  }
		  m = m + M[i][i] / 2; //due to the elements of the diagonal
	  }
	  //  Write vertices and edges numbers
	  fout << "Graph with " << n << " vertices and " << m << " edges " << endl;
	  //  Write adjacency matrix
	  fout << "Adjacency matrix" << endl;
	  for (int i = 0; i < n; i++) {
		  for (int k = 0; k < n; k++) {
			  fout << "\t" << M[i][k];
		  }
		  fout << endl;
	  }
	  //  Write edges         
	  fout << "Edges" << endl;
	  for (int i = 0; i < n; i++) {
		  for (int k = i; k < n; k++) {
			  if (M[i][k] > 0) {
				  for (int q = 0; q < M[i][k]; q++) {
					  fout << i << " " << k << endl;
				  }
			  }
		  }
	  }

	  //  Count degrees
	  vector<int> deg(n);
	  for (int i = 0; i < n; i++) {
		  deg[i] = M[i][i];
		  for (int k = 0; k < n; k++) {
			  deg[i] += M[i][k];
		  }
	  }
	  //  Write sorted degrees sequence
	  fout << "Degrees sequence" << endl;
	  for (int i = 0; i < n; i++) {
		  fout << deg[i] << " ";
	  }
	  fout << endl;
	  //  Sort degrees sequence
	  sort(deg.begin(), deg.end());
	  //  Write sorted degrees sequence
	  fout << "Sorted degrees sequence" << endl;
	  for (int i = 0; i < n; i++) {
		  fout << deg[i] << " ";
	  }
	  fout << endl;
  }
// Random permutation to create adjacency matrix with the permutation

  vector<int>
	  Random_Permutation(int n)
  {
	  vector<int>RP(n);
	  vector<int>B(n, false); //boolean vector
	  for (int i = 0; i < n; i++) 
	  {
		  int r = rand() % (n - i);  //random r
		  for (int k = 0; k <= r; k++) 
		  {  //permutation
			  if (B[k])
				  r++;
		  }
		  B[r] = true; //change thee index to not have the same again
		  RP[i] = r; //we add the random to the matrix
	  }
	  return RP;
  }
//Test equalty, if 2 graphs are the same

  bool
	  equalty(vector<vector<int>>& M1, vector<vector<int>>& M2)
  {
	  if (M1.size() != M2.size()) return false;
	  for (int i = 0; i < (M1.size()); i++) {
		  for (int j = 0; j < (M2.size()); j++) {
			  if (M1[i][j] != M2[i][j])
				  return false;
		  }
	  }
	  return true;
  }
//Test isomorf, this will be useful to the complete test

bool
	test_isomorf(vector<vector<int>>& M1, vector<int>& P, vector<vector<int>>& M2)
{
	int n = M1.size(), n2 = M2.size(), nP = P.size();
	if (n2 != n || nP != n) return false;
	for (int i = 0; i < n; i++)
		for (int k = 0; k < n; k++)
			if (M2[P[i]][P[k]] != M1[i][k])
				return false;
	return true;
}

// Test automorphism

  bool
	  test_automorf(vector<vector<int>>& M, vector<int>& P)
  {
	  int n = (M.size()), nP = P.size();
	  for (int i = 0; i < n; i++)
		  for (int k = 0; k < n; k++)
			  if (M[P[i]][P[k]] != M[i][k])
				  return false;
	  return true;
  }

  // Permutates vertices of the graph M with the permutation P

  vector<vector<int>>
	  graphM_Permutation(vector<int>& P, vector<vector<int>>& M)
  {
	  int n = M.size();
	  if (P.size() != n) exit(1); //if they don't have the same size it goes out
	  vector<vector<int>>R(n, vector<int>(n, 0));
	  for (int i = 0; i < n; i++) {
		  for (int k = 0; k < n; k++) {
			  R[P[i]][P[k]] = M[i][k];
		  }
	  }
	  return R;
  }

  // Returns a 1 if P1 (the permutation) is isomorphic to M1 and M2
  int
	  graphM_isomorf(vector<vector<int>>& M1, vector<vector<int>>& M2, vector<int> P1) {
	  int n1 = M1.size();
	  int n2 = M2.size();
	  int a = 0;
	  if (n1 == n2) 
	  {
		  for (int i = 0; i < n1; i++)
			  for (int j = 0; j < n1; j++)
				  if (M2[P1[i]][P1[j]] != M1[i][j])
					  a++;
	  }
	  else 
	  {
		  a = 1;
	  }
	  if (a != 0) 
	  {
		  return 0;
	  }
	  else 
	  {
		  return 1;
	  }
  }

// Isomorphisms returns the number of isomorphims that have 2 matrix
  int
	  Isomorphisms(vector<vector<int>>& M1, vector<vector<int>>& M2, ofstream& fout)
  {
	  int n = M1.size(), m = M2.size();
	  if (m != n) return false;
	  vector<int> P(n);
	  for (int i = 0; i < n; i++)
		  P[i] = i;
	  int ison = 0;
	  do {
		  if (test_isomorf(M1, P, M2)) {
			  ison++;
			  fout << "Isomorphism " << ison << ":";
			  for (int j = 0; j < n; j++) {
				  fout << " " << P[j];
			  }
			  fout << endl;
		  }
	  } while (next_permutation(P.begin(), P.end()));

	  return ison;
  }

// Returns a 1 if P1 (the permutation) is autsomorphic to M1
  int
	  graphM_automor(vector<vector<int>>& M1, vector<int>& P1) {
	  int n1 = M1.size();
	  for (int i = 0; i < n1; i++)
		  for (int j = 0; j < n1; j++)
			  if (M1[P1[i]][P1[j]] != M1[i][j])
				  return 0;
	  return 1;
  }

// Return the number of the autormophism a matrix have and the orbites.
  int
	  Automorphisms(vector<vector<int>>& M, ofstream& fout)
  {
	  int n = M.size(), Auton = 0;
	  vector<int> Orb(n);
	  for (int i = 0; i < n; i++)
		  Orb[i] = i;
	  vector<int>P(n);
	  for (int i = 0; i < n; i++)
		  P[i] = i;
	  do {
		  if (test_isomorf(M, P, M)) {
			  Auton++;
			  fout << "Automorphism " << Auton << ":" << endl;
			  for (int j = 0; j < n; j++)
				  fout << P[j] << "	 ";
			  fout << endl;
			  for (int i = 0; i < n; i++) {
				  if (Orb[P[i]] > Orb[i])
					  Orb[P[i]] = Orb[i];
				  if (Orb[i] > Orb[P[i]])
					  Orb[i] = Orb[P[i]];
			  }
		  }
	  } while (next_permutation(P.begin(), P.end()));
	  fout << "Existeixen" << Auton << " orbites:" << endl;
	  for (int i = 0; i < n; i++)
		  fout << "Orbita " << i << ": " << Orb[i] << endl;
	  fout << endl;
	  return Auton;
  }

//	Main program:

 int 
	main()
{
    ofstream fout;

// EXERCISE 1

//  graph0.in
	fout.open("graph0.out");
    vector<vector<int>> M0 = graphM_read( "graph0.in" );
    graphM_write( M0, fout );
	fout.close();
//  graph1.in
	vector<vector<int>> M1 = graphM_read("graph1.in");
	fout.open("graph1.out");
	graphM_write(M1, fout);
	fout.close();
//  graph2.in
	vector<vector<int>> M2 = graphM_read("graph2.in");
	fout.open("graph2.out");
	graphM_write(M2, fout);
	fout.close();
//  graph3.in
	vector<vector<int>> M3 = graphM_read("graph3.in");
	fout.open("graph3.out");
	graphM_write(M3, fout);
	fout.close();
//  K9
	fout.open("K9.out");
    vector<vector<int>> MK9 = graphM_complete( 9 );
    graphM_write( MK9, fout );
	fout << endl << "Automorphisms of K9" << endl;
	fout << Automorphisms(MK9, fout) << " automorphisms of K9" << endl;
//  DEIXO COMENTAT COM ES FARIA PER ESCRIURE TAMBÉ ELS AUTORFISMES
	fout.close();

// EXERCISE 2 with EXERCISE 7

//  K54K45
	vector<vector<int>> MK45 = graphM_bipartite(4, 5);
	vector<vector<int>> MK54 = graphM_bipartite(5, 4);
	fout.open("K54K45.out");
	graphM_write(MK45, fout);
	graphM_write(MK54, fout);
	fout << endl << "Automorphisms of MK45" << endl;
	cout << Automorphisms(MK45, fout) << " automorphisms of K45" << endl;
	fout << endl << "Automorphisms of K54" << endl;
	cout << Automorphisms(MK54, fout) << " automorphisms of K54" << endl;
	cout << Isomorphisms(MK54, MK45, fout) << "isomorfismes de K45 o K54" << endl;
	fout.close();
//  C9
	fout.open("C9.out");
	vector<vector<int>> MC9 = graphM_cycle(9);
	graphM_write(MC9, fout);
	fout << endl << "Automorphisms of C9";
	cout << Automorphisms(MC9, fout) << " automorphisms of C9" << endl;
	fout.close();
//  S9
	vector<vector<int>> MS9 = graphM_stars(9);
	fout.open("S9.out");
	graphM_write(MS9, fout);
	fout << endl << "Automorphisms of S9" << endl;
	cout << Automorphisms(MS9, fout) << " automorphisms of S9" << endl;
	fout.close();
//	W9
	vector<vector<int>> MW9 = graphM_wheel(9);
	fout.open("W9.out");
	graphM_write(MW9, fout);
	fout << endl << "Automorphisms of W9" << endl;
	cout << Automorphisms(MW9, fout) << " automorphisms of W9" << endl;
	fout.close();
//	G33
	vector<vector<int>> MG33 = graphM_grid(3, 3);
	fout.open("G33.out");
	graphM_write(MG33, fout);
	fout << endl << "Automorphisms of G33" << endl;
	cout << Automorphisms(MG33, fout) << " automorphisms of G43" << endl;
	fout.close();

// EXERCISE 3

	// Equalty between graph1 and graph2
	cout << " Matrix of graph1.in and graph2.in: " << endl;
	equalty(M1, M2);

	// Permutation 1,2,3,0 with graph1 and graph3
	vector<int> P{ 1,2,3,0 };
	cout << "Matrix of graph1.in and graph3.in " << endl;
	for (int i = 0; i < P.size(); i++)
		cout << P[i] << " ";

	if (graphM_isomorf(M1, M3, P) == 1)
		cout << " It's isomorphism" << endl;
	else
		cout << " It's not isomoprhism" << endl;

	// Permutation 1,2,3,0 with graph1
	cout << "Matrix graph1.in with permutation " << endl;
	for (int i = 0; i < P.size(); i++)
		cout << P[i] << " ";

	if (graphM_automor(M1, P) == 1)
		cout << "It's automorphism" << endl;
	else
		cout << "It's not automorphism" << endl;

	// Another permutation in the graph bipartite
	cout << "Permutation in K54 and K45 ";
	vector<int> Is{ 8,5,3,2,4,1,0,7,6 };
	for (int i = 0; i < Is.size(); i++)
		cout << Is[i] << " ";
	vector<vector<int>> K54 = graphM_bipartite(5, 4);
	vector<vector<int>> K45 = graphM_bipartite(4, 5);
	if (graphM_isomorf(K54, K45, Is) == 1)
		cout << "It's isomorphism of K5,4 and K4,5" << endl;
	else
		cout << "It's not isomoprhism of K5,4 and K4,5" << endl;

// EXERCISE 4

	vector<int> RA = Random_Permutation(9);
	for (int i = 0; i < RA.size(); i++)
		cout << RA[i] << " ";
	cout << endl;
	vector<vector<int>> Mper = graphM_Permutation(RA,MK54);
	if (graphM_isomorf(MK54, Mper, RA) == 1)
		cout << "It's isomorphism" << endl;
	else
		cout << "It's not isomorphism" << endl;

// EXERCISE 5 IT'S ONLY CHANGE THE PROGRAM

// EXERCISE 6
	vector<vector<int>> g8a = graphM_read("graph8A.in");
	vector<vector<int>> g8b = graphM_read("graph8B.in");

	fout.open("graph8.out");
	fout << "Graph8A.in" << endl;
	Automorphisms(g8a, fout);
	fout << "Graph8B.in" << endl;
	Automorphisms(g8b, fout);
	Isomorphisms(g8a, g8b, fout);
	fout.close();

	vector<vector<int>> g10a = graphM_read("graph10A.in");
	vector<vector<int>> g10b = graphM_read("graph10B.in");

	fout.open("graph10.out");
	fout << "Graph10A.in" << endl;
	Automorphisms(g10a, fout);
	fout << "Graph10B.in" << endl;
	Automorphisms(g10b, fout);
	Isomorphisms(g10a, g10b, fout);
	fout.close();

//  Finish
	cout << endl << "Press enter to finish... ";
    cin.get();
}
