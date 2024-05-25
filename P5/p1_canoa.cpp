#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

const int INF = 999999;

vector<vector<int>> costos {
    {0, 3, 3, INF, INF},
    {INF, 0, 4, 7, INF},
    {INF, INF, 0, 2, 3},
    {INF, INF, INF, 0, 2},
    {INF, INF, INF, INF, 0}};

void calculaCosteMin(vector<vector<int>> &dp, vector<vector<int>> &next, int n) {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (dp[i][k] < INF && dp[k][j] < INF && dp[i][j] > dp[i][k] + dp[k][j]) {
                    dp[i][j] = dp[i][k] + dp[k][j];
                    next[i][j] = k;
                }
            }
        }
    }
}

vector<int> construirRutas(int i, int j, const vector<vector<int>> &next) {
    if (next[i][j] == -1)
        return {i, j};

    int intermedia = next[i][j];
    vector<int> ruta = construirRutas(i, intermedia, next);
    ruta.pop_back();
    vector<int> subruta = construirRutas(intermedia, j, next);
    ruta.insert(ruta.end(), subruta.begin(), subruta.end());
    
    return ruta;
}

void imprimirSolucion(const vector<vector<int>> &dp, const vector<vector<int>> &next, int n) {
    cout << "Rutas y costo mínimo de los viajes en canoa:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i < j) { 
                cout << "Desde " << i+1 << " hasta " << j+1 << ": ";
                if (dp[i][j] == INF) {
                    cout << "No hay rutas disponibles";
                } else {
                    cout << "Costo: " << dp[i][j] << " | Camino: ";
                    vector<int> ruta = construirRutas(i, j, next);
                    for (int k = 0; k < ruta.size(); k++) {
                        if (k > 0)
                            cout << " -> ";
                        cout << ruta[k]+1;
                    }
                }
                cout << endl;
            }
        }
    }
}

int main() {
    int n = costos.size();
    vector<vector<int>> dp = costos, next(n, vector<int>(n, -1));

    calculaCosteMin(dp, next, n);
    imprimirSolucion(dp, next, n);


    cout << "Matriz de costos mínimos (DP)" << endl;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if (dp[i][j] == INF){
                cout << "- ";
            } else {
                cout << dp[i][j] << " ";
            }
        }
        cout << endl;
    }

    cout << "Matriz de viajes intermedios (next)" << endl;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if (next[i][j] == -1){
                cout << "* ";
            } else {
                cout << next[i][j]+1 << " ";
            }
        }
        cout << endl; 
    }

    return 0;
}
