#include <iostream>
#include <vector>
#include <set>

using namespace std;

void crearCalendario(int n) {
    if (n % 2 != 0) {
        cout << "El número de equipos debe ser par." << endl;
        return;
    }

    vector<int> equipos(n);
    vector<vector<int>> res(n, vector<int>(n-1));

    for (int i = 0; i < n; ++i) {
        equipos[i] = i + 1;
    }
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n-1; ++j){
            res[i][j] = 0;
        }
    }

    set<pair<int, int>> jugados;
    vector<vector<int>> matriz(n - 1, vector<int>(n / 2, 0));

    // Iterar para n-1 días
    for (int day = 1; day <= n - 1; ++day) {
        cout << "Día " << day << ":" << endl;
        for (int i = 0; i < n / 2; ++i) {
            int equipo1 = equipos[i];
            int equipo2 = equipos[n - 1 - i];
            while (jugados.find(make_pair(equipo1, equipo2)) != jugados.end()) {
                ++equipo1;
                if (equipo1 > n / 2) {
                    equipo1 = 1;
                    ++equipo2;
                }
            }

            cout << "Partido " << i + 1 << ": Equipo " << equipo1 << " vs Equipo " << equipo2 << endl;

            res[equipo1-1][day-1] = equipo2;
            res[equipo2-1][day-1] = equipo1;

            jugados.insert(make_pair(equipo1, equipo2));
        }

        // Rotación
        int temp = equipos[n - 1];
        for (int i = n - 1; i > 1; --i) {
            equipos[i] = equipos[i - 1];
        }
        equipos[1] = temp;
    }

    cout << "\nMatriz de enfrentamientos:" << endl;
    
    for (int i = 0; i < n; ++i){
        cout << "Equipo " << (i+1) << ": ";
        for (int j = 0; j < n-1; ++j){
            cout << res[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int numEquipos;

    cout << "Ingrese el número de equipos (debe ser par): ";
    cin >> numEquipos;

    crearCalendario(numEquipos);

    return 0;
}