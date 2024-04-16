// C++ program for Kruskal's algorithm to find Minimum 
// Spanning Tree of a given connected, undirected and 
// weighted graph 
#include<bits/stdc++.h> 
using namespace std; 

// Creating shortcut for an integer pair 
typedef pair<int, int> iPair; 

// Structure to represent a graph 
struct Graph 
{ 
	int V, E; 
	vector< pair<int, iPair> > edges; 

	// Constructor 
	Graph(int V, int E) 
	{ 
		this->V = V; 
		this->E = E; 
	} 

	// Utility function to add an edge 
	void addEdge(int u, int v, int w) 
	{ 
		edges.push_back({w, {u, v}}); 
	} 

	// Function to find MST using Kruskal's 
	// MST algorithm 
	int kruskalMST(); 
}; 

// To represent Disjoint Sets 
struct DisjointSets 
{ 
	int *parent, *rnk; 
	int n; 

	// Constructor. 
	DisjointSets(int n) 
	{ 
		// Allocate memory 
		this->n = n; 
		parent = new int[n+1]; 
		rnk = new int[n+1]; 

		// Initially, all vertices are in 
		// different sets and have rank 0. 
		for (int i = 0; i <= n; i++) 
		{ 
			rnk[i] = 0; 

			//every element is parent of itself 
			parent[i] = i; 
		} 
	} 

	// Find the parent of a node 'u' 
	// Path Compression 
	int find(int u) 
	{ 
		/* Make the parent of the nodes in the path 
		from u--> parent[u] point to parent[u] */
		if (u != parent[u]) 
			parent[u] = find(parent[u]); 
		return parent[u]; 
	} 

	// Union by rank 
	void merge(int x, int y) 
	{ 
		x = find(x), y = find(y); 

		/* Make tree with smaller height 
		a subtree of the other tree */
		if (rnk[x] > rnk[y]) 
			parent[y] = x; 
		else // If rnk[x] <= rnk[y] 
			parent[x] = y; 

		if (rnk[x] == rnk[y]) 
			rnk[y]++; 
	} 
}; 

/* Functions returns weight of the MST*/

int Graph::kruskalMST() 
{ 
	int mst_wt = 0; // Initialize result 

	// Sort edges in increasing order on basis of cost 
	sort(edges.begin(), edges.end()); 

	// Create disjoint sets 
	DisjointSets ds(V); 

	// Iterate through all sorted edges 
	vector< pair<int, iPair> >::iterator it; 
	for (it=edges.begin(); it!=edges.end(); it++) 
	{ 
		int u = it->second.first; 
		int v = it->second.second; 

		int set_u = ds.find(u); 
		int set_v = ds.find(v); 

		// Check if the selected edge is creating 
		// a cycle or not (Cycle is created if u 
		// and v belong to same set) 
		if (set_u != set_v) 
		{ 
			// Current edge will be in the MST 
			// so print it 
			cout << u << " - " << v << endl; 

			// Update MST weight 
			mst_wt += it->first; 

			// Merge two sets 
			ds.merge(set_u, set_v); 
		} 
	} 

	return mst_wt; 
} 

// Driver program to test above functions 
int main() 
{ 
	/* Let us create above shown weighted 
	and undirected graph */
	int V = 9, E = 14; 
	Graph g(V, E);

    // Creación del grafo
    // 0: Plaza Azcarate
    // 1: Plaza de la Libertad
    // 2: Plaza Mayor
    // 3: Plaza de las Maravillas
    // 4: Plaza de la Constitucion

    // 9 aristas (calles)
	g.addEdge(0, 1, 1100000); // Azcarate a Libertad (Serrano)
	g.addEdge(0, 2, 130000);  // Azcarate a Mayor (Lopez)
	g.addEdge(0, 3, 450004);  // Azcarate a Maravillas (Soriano)
	g.addEdge(0, 4, 748456);  // Azcarate a Constitucion (Portugalesa)
	g.addEdge(1, 2, 1300000); // Libertad a Mayor (No)
	g.addEdge(1, 3, 555123);  // Libertad a Maravillas (Jobenas)
	g.addEdge(1, 4, 1700000); // Libertad a Constitucion (Anguila)
	g.addEdge(2, 4, 554521);  // Mayor a Constitucion (Bernabe)
	g.addEdge(3, 4, 143552);  // Maravillas a Constitucion (Portugalesa de arriba)


	cout << "Edges of MST are \n"; 
	int mst_wt = g.kruskalMST(); 

	cout << "\nWeight of MST is " << mst_wt << endl; 

	return 0; 
} 
