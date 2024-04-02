#include <iostream>
#include <vector>
#include <set>
#include <chrono>
#include <fstream>

// #define DEBUG

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

    for (int day = 1; day <= n - 1; ++day) {
        #ifdef DEBUG
            cout << "Día " << day << ":" << endl;
        #endif
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

            #ifdef DEBUG
            cout << "Partido " << i + 1 << ": Equipo " << equipo1 << " vs Equipo " << equipo2 << endl;
            #endif 
            res[equipo1-1][day-1] = equipo2;
            res[equipo2-1][day-1] = equipo1;

            jugados.insert(make_pair(equipo1, equipo2));
        }

        int temp = equipos[n - 1];
        for (int i = n - 1; i > 1; --i) {
            equipos[i] = equipos[i - 1];
        }
        equipos[1] = temp;
    }

    #ifdef DEBUG
    cout << "\nMatriz de enfrentamientos:" << endl;
    
    for (int i = 0; i < n; ++i){
        cout << "Equipo " << (i+1) << ": ";
        for (int j = 0; j < n-1; ++j){
            cout << res[i][j] << " ";
        }
        cout << endl;
    }
    #endif 
}

int main(int argc, char *argv[]) {
    int n, argumento;
    chrono::time_point<std::chrono::high_resolution_clock> t0, tf;
	double tejecucion;
	ofstream fsalida;
	
	if (argc <= 2) {
		cerr<<"\nError: El programa se debe ejecutar de la siguiente forma.\n\n";
		return 0;
	}
    string merge = string(argv[1]) + ".csv";
	fsalida.open(merge);
	if (!fsalida.is_open()) {
		cerr<<"Error: No se pudo abrir fichero para escritura "<<argv[1]<<"\n\n";
		return 0;
	}
	
	for (argumento = 2; argumento<argc; argumento++) {
		n = atoi(argv[argumento]);
		cerr << "Ejecutando para caso: " << n << endl;
		
		t0 = std::chrono::high_resolution_clock::now();
		crearCalendario(n);
		tf = std::chrono::high_resolution_clock::now();

		unsigned long tejecucion = std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();
		fsalida << n <<" "<< tejecucion <<"\n";
	}
	
	fsalida.close();

	return 0;
}
