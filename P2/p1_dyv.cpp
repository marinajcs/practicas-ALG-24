#include <cstdlib> // Para usar srand y rand
#include <chrono>
#include <cstring> // Para usar memcpy
#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream> // Para usar ficheros
using namespace std;

int cuentafreucencia(vector<int>& nums,int abajo, int arriba,int valor){
	int count = 0;
	for(int i = abajo; i <= arriba; i++){
		if(nums[i] == valor)
		count = count + 1;
	}
	return count;
}

int encuentraMayoriaDyV(vector<int>& nums, int abajo, int arriba) {
    if (abajo == arriba) {
        return nums[abajo];
    }

    int medio = abajo + (arriba - abajo) / 2;

    int mayoriaIzquierda = encuentraMayoriaDyV(nums, abajo, medio);
    int mayoriaDerecha = encuentraMayoriaDyV(nums, medio + 1, arriba);

    if (mayoriaIzquierda == mayoriaDerecha) {
        return mayoriaIzquierda;
    }

	int cuentaIzquierda = cuentafreucencia(nums,abajo,arriba,mayoriaIzquierda);
	int cuentaDerecha = cuentafreucencia(nums,abajo,arriba,mayoriaDerecha);

	if(cuentaIzquierda > (arriba - abajo + 1 ) / 2)

	return cuentaIzquierda;

	else if (cuentaDerecha > (arriba - abajo + 1 ) / 2)

	return mayoriaDerecha;

	else
	
	return -1;
}


int main(int argc, char *argv[]) {
	
	int n, i, argumento;
    chrono::time_point<std::chrono::high_resolution_clock> t0, tf; // Para medir el tiempo de ejecución
	double tejecucion; // tiempo de ejecucion del algoritmo en ms
	unsigned long int semilla;
	ofstream fsalida;
	
	if (argc <= 3) {
		cerr<<"\nError: El programa se debe ejecutar de la siguiente forma.\n\n";
		cerr<<argv[0]<<" NombreFicheroSalida Semilla tamCaso1 tamCaso2 ... tamCasoN\n\n";
		return 0;
	}
	
	// Abrimos fichero de salida
	fsalida.open(argv[1]);
	if (!fsalida.is_open()) {
		cerr<<"Error: No se pudo abrir fichero para escritura "<<argv[1]<<"\n\n";
		return 0;
	}

    vector<int> V;
	
	// Inicializamos generador de no. aleatorios
	semilla= atoi(argv[2]);
	srand(semilla);
	
	// Pasamos por cada tamaÒo de caso
	for (argumento= 2; argumento<argc; argumento++) {
		
		// Cogemos el tamanio del caso
		n= atoi(argv[argumento]);
		
		// Reservamos memoria para el vector
		V.resize(n);

		// Generamos vector aleatorio de prueba, con componentes entre 0 y n-1
		for (i= 0; i<n; i++)
			V[i]= rand()%n;
			
		t0= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecuciÛn del algoritmo
		encuentraMayoriaDyV(V,0,V.size()); // Ejecutamos el algoritmo para tamaÒo de caso n
		tf= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que finaliza la ejecuciÛn del algoritmo
		
		unsigned long tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();
		cerr << "n: "<< n << "\t\tTiempo (us): " << tejecucion <<endl;
		
		// Guardamos tam. de caso y t_ejecucion a fichero de salida
		fsalida<<n<<" "<<tejecucion<<"\n";
		
	}
	
	// Cerramos fichero de salida
	fsalida.close();
	
	return 0;
}