// C++ program for Kruskal's algorithm to find Minimum 
// Spanning Tree of a given connected, undirected and 
// weighted graph 
#include<bits/stdc++.h> 
using namespace std; 

// Creando un acceso directo para un par de enteros
typedef pair<int, int> iPair; 

// Estructura para representar el grafo
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

	// Funcion para añadir una arista
	void addEdge(int u, int v, int w) 
	{ 
		edges.push_back({w, {u, v}}); 
	} 

	// Funcion para hallar MST usando algoritmo de Kruskal
	int kruskalMST(); 
}; 


// Para representar conjuntos disjuntos
struct DisjointSets 
{ 
	int *parent, *rnk; 
	int n; 

	// Constructor. 
	DisjointSets(int n) 
	{ 
		// Asignar memoria 
		this->n = n; 
		parent = new int[n+1]; 
		rnk = new int[n+1]; 

		// Inicialmente, todos los vertices estan
		// en conjuntos diferentes y tienen rango 0
		for (int i = 0; i <= n; i++) 
		{ 
			rnk[i] = 0; 

			// Cada elemento es padre de si mismo
			parent[i] = i; 
		} 
	} 

	// Encuentra el padre de un nodo 'u'
	// Path Compression 
	int find(int u) 
	{ 
		/* Hacer que el padre de los nodos en el 
		camino u--> parent[u] apunte a parent[u] */
		if (u != parent[u]) 
			parent[u] = find(parent[u]); 
		return parent[u]; 
	} 

	// Union by rank 
	void merge(int x, int y) 
	{ 
		x = find(x), y = find(y); 

		/* Hacer que el arbol con menor altura sea un
		subarbol del otro arbol */
		if (rnk[x] > rnk[y]) 
			parent[y] = x; 
		else // If rnk[x] <= rnk[y] 
			parent[x] = y; 

		if (rnk[x] == rnk[y]) 
			rnk[y]++; 
	} 
}; 

/* La funcion devuelve el peso del MST */

int Graph::kruskalMST() 
{ 
	int mst_wt = 0; // Inicializa resultado

	// Ordenar las aristas en orden creciente según coste
	sort(edges.begin(), edges.end()); 

	// Crear conjuntos disjuntos
	DisjointSets ds(V); 

	// Iterar por todos las aristas ordenadas
	vector< pair<int, iPair> >::iterator it; 
	for (it=edges.begin(); it!=edges.end(); it++) 
	{ 
		int u = it->second.first; 
		int v = it->second.second; 

		int set_u = ds.find(u); 
		int set_v = ds.find(v); 

		// Comprobar si la arista seleccionada esta
		// creando un ciclo o no (ciclo es creado si
		// u y v pertenecen al mismo conjunto)
		if (set_u != set_v) 
		{ 
			// La arista actual estara en el MST
			// asi que la imprimimos
			cout << u << " - " << v << endl; 

			// Actualizar peso del MST
			mst_wt += it->first; 

			// Merge de los dos conjuntos
			ds.merge(set_u, set_v); 
		} 
	} 

	return mst_wt; 
} 


int main() 
{ 
	int V = 5, E = 9; 
	Graph g(V, E);


	// Leyenda
	cout << "Las plazas son: " << endl;
	cout << "0: Plaza Azcarate" << endl;
    cout << "1: Plaza de la Libertad" << endl;
    cout << "2: Plaza Mayor" << endl;
    cout << "3: Plaza de las Maravillas" << endl;
    cout << "4: Plaza de la Constitucion" << endl << endl;

	cout << "Las calles son: " << endl;
	cout << "0-1: C./ Serrano" << endl;
	cout << "0-2: C./ Lopez" << endl;
	cout << "0-3: C./ Soriano" << endl;
	cout << "0-4: C./ Portugalesa" << endl;
	cout << "1-2: C./ No" << endl;
	cout << "1-3: C./ Jobenas" << endl;
	cout << "1-4: C./ Anguila" << endl;
	cout << "2-4: C./ Bernabe" << endl;
	cout << "3-4: C./ Portugalesa de arriba" << endl;


    // Creación del grafo
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

	cout << endl;
	cout << "Las aristas del MST son \n"; 
	int mst_wt = g.kruskalMST(); 

	cout << "\nEl coste total es " << mst_wt << " euros."<< endl; 

	return 0; 
} 
