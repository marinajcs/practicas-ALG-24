#include <iostream>
#include <vector>
using namespace std;

const int INF = 10000;
const int FIL = 5;
const int COL = 5;

// Función para encontrar el nodo más cercano no visitado
int encontrarNodoMasCercano(int grafo[FIL][COL], vector<bool>& visitados, int n, int nodo_actual, int nodo_servidor) {
    int nodo_mas_cercano = -1;
    int distancia_minima = INF;

    for (int i = 0; i < n; ++i) {
        if (i == nodo_servidor && !visitados[i] && grafo[nodo_actual][i] < distancia_minima){
            nodo_mas_cercano = i;
            return nodo_mas_cercano;
        }
        if (!visitados[i] && grafo[nodo_actual][i] < distancia_minima) {
            distancia_minima = grafo[nodo_actual][i];
            nodo_mas_cercano = i;
        }
    }
    return nodo_mas_cercano;
}

// Función para encontrar el camino óptimo usando el algoritmo del vecino más cercano
vector<int> greedy(int grafo[FIL][COL], int n, int nodo_inicio, int nodo_servidor) {
	vector<bool> visitados(n, false);
    vector<int> solucion;
    solucion.push_back(nodo_inicio);
    visitados[nodo_inicio] = true;
    int nodo_actual = nodo_inicio;

    while (nodo_actual != nodo_servidor) {
        int nodo_mas_cercano = encontrarNodoMasCercano(grafo, visitados, n, nodo_actual, nodo_servidor);
        if (nodo_mas_cercano == -1) {
            break; // No quedan nodos por visitar
        }
        solucion.push_back(nodo_mas_cercano);
        visitados[nodo_mas_cercano] = true;
        nodo_actual = nodo_mas_cercano;
    }
    return solucion;
}

int main() {

    int grafo[FIL][COL] = {
        {0, 2, INF, INF, 1},
        {2, 0, 1, 3, INF},
        {INF, 1, 0, INF, 4},
        {INF, 3, INF, 0, 5},
        {1, INF, 4, 5, 0}
    };

	int n = 5;
	int nodo_inicio = 3;
    int nodo_servidor = 0;

	// Mostrar la matriz
    cout << "La matriz ingresada es:" << endl;
    for (int i = 0; i < FIL; ++i) {
        for (int j = 0; j < COL; ++j) {
            if (grafo[i][j]== INF)
                cout << "·" << " ";
            else
                cout << grafo[i][j] << " ";
        }
        cout << endl;
    }

	vector<int> solucion = greedy(grafo, n, nodo_inicio, nodo_servidor);

	// Imprimir el camino más corto
    cout << "Camino más corto desde el nodo " << nodo_inicio << " hasta el nodo " << nodo_servidor << ": ";

    // Imprimir la solución
    cout << "Solución: ";
    for (int i = 0; i < solucion.size(); ++i)
        cout << solucion[i] << " ";
    cout << endl;

    return 0;
}