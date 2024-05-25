#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int FIL = 4;
const int COL = 5;

void mostrarLaberinto(int laberinto[FIL][COL]){
    for (int i = 0; i < FIL; ++i) {
        for (int j = 0; j < COL; ++j) {
            if (laberinto[i][j] == -1)
                cout << "X" << " ";
            else if (laberinto[i][j] == 0)
                cout << "·" << " ";
            else
                cout << "€" << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void mostrarMatrizCostes(vector<vector<int>> costes){
    for (int i = 0; i < FIL; ++i){ 
        cout << endl;
        for (int j = 0; j < COL; ++j) 
            cout << costes[i][j] << "\t";
    }
    cout << endl << endl;
}

void mostrarSolucion(vector<pair<int,int>>& solucion){
    cout << "El camino para salir del laberinto con más dinero es:" << endl;
    for (int i = solucion.size() - 1; i >= 0; --i) {
        cout << "(" << solucion[i].first << "," << solucion[i].second << ") ";
    }
    cout << endl << endl;
}

vector<vector<int>> rellenarMatrizCostes(int laberinto[FIL][COL], vector<vector<int>> costes) {

    for (int i = 0; i < FIL; ++i) {
        for (int j = FIL - 1; j >= 0; --j) {
            if (laberinto[i][j] == -1) {
                costes[i][j] = -1;  // Casilla no transitable
            } else {
                int oro_actual;
                if (laberinto[i][j] == 1)
                    oro_actual = 1;
                else 
                    oro_actual = 0;

                if (i == 0 && j == COL - 1) {
                    costes[i][j] = oro_actual;
                } else {
                    int max_oro_prev = -1;
                    if (i > 0 && costes[i-1][j] != -1)  // Anterior arriba
                        max_oro_prev = max(max_oro_prev, costes[i-1][j]);
                
                    if (j < COL - 1 && costes[i][j+1] != -1)  // Derecha
                        max_oro_prev = max(max_oro_prev, costes[i][j+1]);
                    
                    if (i > 0 && j < COL - 1 && costes[i-1][j+1] != -1)  // Diagonal arriba
                        max_oro_prev = max(max_oro_prev, costes[i-1][j+1]);
                    
                    if (max_oro_prev != -1) 
                        costes[i][j] = oro_actual + max_oro_prev;
                }
            }
        }
    }

    return costes;
}

vector<pair<int, int>> recuperarCamino(int laberinto[FIL][COL], vector<vector<int>>& DP, vector<pair<int, int>> camino) {
    int i = FIL - 1, j = 0;
    camino.push_back({i, j});

    while (i > 0 || j < COL - 1) {
        int max_oro = -1;
        pair<int, int> siguiente_casilla;

        if (i > 0 && DP[i-1][j] != -1 && DP[i-1][j] > max_oro) {
            max_oro = DP[i-1][j];
            siguiente_casilla = {i-1, j};
        }
        if (j < COL - 1 && DP[i][j+1] != -1 && DP[i][j+1] > max_oro) {
            max_oro = DP[i][j+1];
            siguiente_casilla = {i, j+1};
        }
        if (i > 0 && j < COL - 1 && DP[i-1][j+1] != -1 && DP[i-1][j+1] > max_oro) {
            max_oro = DP[i-1][j+1];
            siguiente_casilla = {i-1, j+1};
        }

        camino.push_back(siguiente_casilla);
        i = siguiente_casilla.first;
        j = siguiente_casilla.second;
    }

    return camino;
}

int main(){

    int laberinto[FIL][COL] = {
        {1,0,-1,0,0},
        {0,1,1,0,0},
        {0,0,1,0,0},
        {0,0,1,0,0},
    };

    vector<vector<int>> costes(FIL, vector<int>(COL, 0));
    vector<pair<int, int>> camino;

    // Mostrar la matriz
    cout << "La matriz ingresada es:" << endl;
    mostrarLaberinto(laberinto);  

    costes = rellenarMatrizCostes(laberinto, costes);
    camino = recuperarCamino(laberinto,costes,camino);

    mostrarMatrizCostes(costes);
    mostrarSolucion(camino);

    return 0;
}