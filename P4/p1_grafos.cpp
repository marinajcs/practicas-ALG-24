#include <iostream>
#include <vector>
#include <utility>

using namespace std;

vector<vector<int>> P = {
    {-1, 3, 5, 7},
    {2, -1, 4, 6},
    {9, 5, -1, 10},
    {1, 6, 3, -1},
};
int n = P.size();
vector<bool> emparejado(n, false);
double maxSum = 0;
vector<pair<int, int>> parejasOptimas;


void P1_Backtracking(int k, int n, double suma, vector<pair<int, int>>& parejas) {
    if (k == (n-1)) {
        if (suma > maxSum) {
            maxSum = suma;
            parejasOptimas = parejas;
        }
        return;
    } else if (emparejado[k]) {
        P1_Backtracking(k + 1, n, suma, parejas);
    }

    for (int i = k + 1; i < n; i++) {
        if (!emparejado[i]) {
            emparejado[k] = emparejado[i] = true;
            parejas.push_back(make_pair(k, i));
            double pairValue = P[k][i] * P[i][k];
            
            P1_Backtracking(k + 1, n, suma + pairValue, parejas);
            
            parejas.pop_back();
            emparejado[k] = emparejado[i] = false;
        }
    }
}

int main() {
    vector<pair<int, int>> parejas;
    P1_Backtracking(0, n, 0, parejas);
    
    cout << "Máxima suma de valores de emparejamiento: " << maxSum << endl;
    cout << "Emparejamientos óptimos:" << endl;
    for (int i = 0; i < n/2; i++) {
        cout << "- Pareja " << i+1 << ": " << parejasOptimas[i].first << " y " << parejasOptimas[i].second << endl;
    }

    return 0;
}
