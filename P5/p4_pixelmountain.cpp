#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int FIL = 4;
const int COL = 5;

void mostrarMontania(int laberinto[FIL][COL]){
    for (int i = 0; i < FIL; ++i) {
        for (int j = 0; j < COL; ++j) {
            cout << laberinto[i][j] << " ";
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
    cout << "El camino para escalar la montaña con la mínima dificultad es:" << endl;
    for (int i = solucion.size() - 1; i >= 0; --i) {
        cout << "(" << solucion[i].first << "," << solucion[i].second << ") ";
    }
    cout << endl << endl;
}

vector<vector<int>> rellenaPixelMountain(const int montania[FIL][COL], vector<vector<int>> dificultad) {
    for (int j = 0; j < COL; j++)   // Rellenamos la ultima fila (coinciden)
        dificultad[FIL-1][j] = montania[FIL-1][j];

    // Rellenar la matriz de costos desde la penúltima fila hasta la primera
    for (int i = FIL - 2; i >= 0; --i) {
        for (int j = 0; j < COL; ++j) {
            int minDif = dificultad[i + 1][j];
            if (j > 0) 
                minDif = min(minDif, dificultad[i + 1][j - 1]);
            
            if (j < COL - 1) 
                minDif = min(minDif, dificultad[i + 1][j + 1]);
            
            dificultad[i][j] = montania[i][j] + minDif;
        }
    }
    return dificultad;
}

vector<pair<int, int>> recuperaCamino(int montania[FIL][COL], vector<vector<int>>& dificultad, vector<pair<int, int>> camino) {
    
    int minCoste = dificultad[0][0];
    int posMin =0;

    for (int j = 0; j < COL; j++)  
        if(dificultad[0][j]<minCoste){
            minCoste = dificultad[0][j];
            posMin = j;
        }
        
    camino.push_back({0, posMin});

    for (int i = 1; i < FIL; ++i) {
        int sigMin = posMin;
        minCoste = dificultad[i][posMin];

        if (posMin > 0 && dificultad[i][posMin - 1] < minCoste) {
            minCoste = dificultad[i][posMin - 1];
            sigMin = posMin - 1;
        }

        if (posMin < COL - 1 && dificultad[i][posMin + 1] < minCoste) {
            minCoste = dificultad[i][posMin + 1];
            sigMin = posMin + 1;
        }

        posMin = sigMin;
        camino.push_back({i, posMin});
    }

    return camino;
}

int main(){

    int montania[FIL][COL] = {
        {2,8,9,5,8},
        {4,4,6,2,3},
        {5,7,5,6,1},
        {3,2,5,4,8},
    };

    vector<vector<int>> dificultad(FIL, vector<int>(COL, 0));
    vector<pair<int, int>> camino;

    // Mostrar la matriz
    cout << "La matriz ingresada es:" << endl;
    mostrarMontania(montania);  

    dificultad = rellenaPixelMountain(montania, dificultad);
    camino = recuperaCamino(montania,dificultad,camino);

    mostrarMatrizCostes(dificultad);
    mostrarSolucion(camino);

    return 0;
}