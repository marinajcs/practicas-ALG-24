#include <cstdlib> // Para usar srand y rand
#include <chrono>
#include <iostream>
#include <fstream> // Para usar ficheros
#include <limits.h>
using namespace std;

//Constante: O(1)
pair<bool,unsigned int> isSolution(unsigned int y, unsigned int n){
	pair<bool,unsigned long> res;
	unsigned long mult;
	mult = y*(y+1)*(y+2);
	if (n ==  mult){
		res.first = true;
		res.second = n;
	} else {
		if (y != 0 && (y*(y+1)) / y != (y+1))  //se produce overflow?
			res.second = ULONG_MAX;
		else if( (y*(y+1) != 0 && mult / (y*(y+1)) != (y+2)))
			res.second = ULONG_MAX;
		else
			res.second = (y*(y+1)*(y+2));
	}
	return res;
}

//Logarítmica: O(log2(n))
pair<bool,unsigned long> MultiplConsecDyV(unsigned int n) {
	int mid;
	int max = n-1;
	int min = 1;
	bool found = false;
	pair<bool,unsigned int> res;

	while (min <= max && !found) {
		mid = (min+max)/2;
		if (isSolution(mid,n).first){
			res.first = found = true;
			res.second = mid;
		} else {
			if (n < isSolution(mid,n).second)  
				max = mid-1;
			else
				min = mid+1;
		}
	}
	return res;
}


int main(int argc, char *argv[]) {
	int n, argumento;
    chrono::time_point<std::chrono::high_resolution_clock> t0, tf;
	double tejecucion;
	ofstream fsalida;
	
	if (argc <= 3) {
		cerr<<"\nError: El programa se debe ejecutar de la siguiente forma.\n\n";
		return 0;
	}
	
	fsalida.open(argv[1]);
	if (!fsalida.is_open()) {
		cerr<<"Error: No se pudo abrir fichero para escritura "<<argv[1]<<"\n\n";
		return 0;
	}
	
	pair<bool,int> caso;

	for (argumento = 3; argumento<argc; argumento++) {
		n= atoi(argv[argumento]);
		cerr << "Ejecutando para caso: " << n << endl;
		
		t0= std::chrono::high_resolution_clock::now();
		caso = MultiplConsecDyV(n);
		tf= std::chrono::high_resolution_clock::now();
		unsigned long tejecucion= std::chrono::duration_cast<std::chrono::nanoseconds>(tf - t0).count();

		if (caso.first)
			cout << "\t-> Para n=" << n << ", y=" << caso.second << endl;
		else
			cout << "\t-> Para n=" << n << " no existe 'y'" << endl;
			
		cout << "\t-> Tiempo de ejec. (ns): " << tejecucion << endl;

		fsalida << n <<" "<< tejecucion <<"\n";
	}
	
	fsalida.close();

	return 0;
}