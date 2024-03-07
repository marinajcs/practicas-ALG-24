#include <cstdlib> // Para usar srand y rand
#include <chrono>
#include <cstring> // Para usar memcpy
#include <iostream>
#include <fstream> // Para usar ficheros

using namespace std;

// Función para calcular el siguiente gap de la secuencia de Knuth
int nextGap(int gap) {
    if (gap <= 1) return 0;
    return (gap + 1) / 2;
}

void shellSort(int *v, int n) {
    int gap = n / 2;

    while (gap > 0) {
        // Se realiza un ordenamiento por inserción para cada elemento con el gap
        for (int i = gap; i < n; i++) {
            int temp = v[i];
            int j;
            for (j = i; j >= gap && v[j - gap] > temp; j -= gap) {
                v[j] = v[j - gap];
            }
            v[j] = temp;
        }
        // Se reduce el gap para la sig. iteración
        gap = nextGap(gap);
    }
}

// Programa main de prueba con vector aleatorio de tam n
int main(int argc, char *argv[]) {
	int *v;
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

	// Inicializamos generador de no. aleatorios
	semilla= atoi(argv[2]);
	srand(semilla);

	// Pasamos por cada tamaño de caso
	for (argumento= 3; argumento<argc; argumento++) {

		// Cogemos el tamaño del caso
		n= atoi(argv[argumento]);

		// Reservamos memoria para el vector
		v= new int[n];

		// Generamos vector aleatorio de prueba, con componentes entre 0 y n-1
		for (i= 0; i<n; i++)
			v[i]= rand()%n;

		cerr << "Ejecutando HeapSort para tam. caso: " << n << endl;

		t0= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecuciÛn del algoritmo
		shellSort(v, n); // Ejecutamos el algoritmo para tamaño de caso n
		tf= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que finaliza la ejecuciÛn del algoritmo

		unsigned long tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();

		cerr << "\tTiempo de ejec. (us): " << tejecucion << " para tam. caso "<< n<<endl;

		// Guardamos tam. de caso y t_ejecucion a fichero de salida
		fsalida<<n<<" "<<tejecucion<<"\n";

		// Liberamos memoria del vector
		delete [] v;
	}

	// Cerramos fichero de salida
	fsalida.close();

	return 0;
}
