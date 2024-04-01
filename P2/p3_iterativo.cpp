#include <chrono>
#include <iostream>
#include <fstream>

// #define DEBUG

using namespace std;

//Lineal: O(n)
pair<bool,unsigned int> MultiplConsec(unsigned int n) {
	unsigned long i, y;
	bool found = false;
	pair<bool,int> res;	

	for (i = 1; i < n && !found; i++) {
		if (n == (i*(i+1)*(i+2)) ) {
			y = i;
			found = true;
		}
	}
	if (found) {
		res.first = found;
		res.second = y;
	}
	return res;
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
	
	fsalida.open(argv[1]);
	if (!fsalida.is_open()) {
		cerr<<"Error: No se pudo abrir fichero para escritura "<<argv[1]<<"\n\n";
		return 0;
	}
	
	pair<bool,int> caso;

	for (argumento = 2; argumento<argc; argumento++) {
		n = atoi(argv[argumento]);
		cerr << "Ejecutando para caso: " << n << endl;
		
		t0 = std::chrono::high_resolution_clock::now();
		caso = MultiplConsec(n);
		tf = std::chrono::high_resolution_clock::now();
		unsigned long tejecucion = std::chrono::duration_cast<std::chrono::nanoseconds>(tf - t0).count();

		#ifdef DEBUG
		if (caso.first)
			cout << "\t-> Para n=" << n << ", y=" << caso.second << endl;
		else
			cout << "\t-> Para n=" << n << " no existe 'y'" << endl;
			
		cout << "\t-> Tiempo de ejec. (ns): " << tejecucion << endl;
		#endif

		fsalida << n <<" "<< tejecucion <<"\n";
	}
	
	fsalida.close();

	return 0;
}

