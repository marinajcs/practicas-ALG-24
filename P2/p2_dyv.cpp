#include <iostream> 
#include <vector> 
#include <utility>
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <fstream>

// #define DEBUG 


using namespace std; 
 
int particionarTuercas(vector<int>& tuercas, int low, int high, int tornillo) { 
    for (int i = low; i < high; i++) { 
        if (tuercas[i] == tornillo) { 
            swap(tuercas[i], tuercas[high]); 
            break; 
        }
    } 
    int pivot = tuercas[high]; 
    int i = low; 
 
    for (int j = low; j < high; j++) { 
        if (tuercas[j] < pivot) { 
            swap(tuercas[i], tuercas[j]); 
            i++; 
        }
    } 
 
    swap(tuercas[i], tuercas[high]); 
    return i; 
} 
 
int particionarTornillos(vector<int>& tornillos, int low, int high, int tuerca) { 
    for (int i = low; i < high; i++) { 
        if (tornillos[i] == tuerca) { 
            swap(tornillos[i], tornillos[high]); 
            break; 
        } 
    } 
    int pivot = tornillos[high]; 
    int i = low;
 
    for (int j = low; j < high; j++) { 
        if (tornillos[j] < pivot) { 
            swap(tornillos[i], tornillos[j]); 
            i++; 
        } 
    } 
    swap(tornillos[i], tornillos[high]); 
    return i; 
} 
 
void ordenarTuercasTornillos(vector<int>& tuercas, vector<int>& tornillos, int low, int high) { 
    if (low < high) { 
        int pivot = particionarTuercas(tuercas, low, high, tornillos[high]); 
 
        particionarTornillos(tornillos, low, high, tuercas[pivot]); 
 
        ordenarTuercasTornillos(tuercas, tornillos, low, pivot - 1); 
        ordenarTuercasTornillos(tuercas, tornillos, pivot + 1, high); 
    } 
} 
 
int main(int argc, char *argv[]){
        int n, argumento,actual_elem;
        argumento = argc - 3;

        chrono::time_point<std::chrono::high_resolution_clock> t0, tf; // Para medir el tiempo de ejecución
        unsigned long int semilla, semilla2;
        unsigned long tejecucion;
        ofstream fsalida;
        vector<int> cajonA;
        vector<int> cajonB;
        
        if (argc <= 3) {
            cerr<<"\nError: El programa se debe ejecutar de la siguiente forma.\n\n";
            cerr<<argv[0]<<" NombreFicheroSalida Semilla tamCaso1 tamCaso2 ... tamCasoN\n\n";
            return 0;
        }

        // Abrimos fichero de salida
        string merge = string(argv[1]) + ".csv";
        fsalida.open(merge);

        if (!fsalida.is_open()) {
            cerr<<"Error: No se pudo abrir fichero para escritura "<<argv[1]<<"\n\n";
            return 0;
        }
        
        //Escribimos los nombres de las columnas del output
        fsalida << "n " << "T(n) " << "K " << "TE(n)\n" ;


        // Inicializamos generador de no. aleatorios
        semilla= atoi(argv[2]);

        
        // Pasamos por cada tamanio de caso para el ejercicio 1
        for (int i = 0; i < argumento; i++){
            n = atoi(argv[i+3]);
            srand(semilla);

            //Generamos vector aleatorio de prueba, con componentes entre 0 y n-1
            for (int j = 0; j<n; j++){
                actual_elem = rand() % n;
                cajonA.push_back(actual_elem);
            }

            srand(semilla2);
            //Generamos vector aleatorio de prueba, con componentes entre 0 y n-1
            for (int j = 0; j<n; j++){
                actual_elem = rand() % n;
                cajonB.push_back(actual_elem);
            }


            cerr << "Ejecutando algoritmo tornillo y tuercas iterativo para tam " << n << endl ;

            t0= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecuciÛn del algoritmo

            ordenarTuercasTornillos(cajonA, cajonB, 0, cajonA.size() - 1); 

            tf= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que finaliza la ejecuciÛn del algoritmo
            tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();

            cerr << "\tTiempo de ejec. (us): " << tejecucion << " para tam. caso "<< n << endl;
            // Guardamos tam. de caso y t_ejecucion a fichero de salida
            fsalida<<n<<" "<<tejecucion<<"\n";
            #ifdef DEBUG
            for (auto it=cajonA.begin(); it != cajonA.end(); ++it)
                cout << *it << " ";
            cout << endl;

            for (auto it=cajonB.begin(); it != cajonB.end(); ++it)
                cout << *it << " ";
            cout << endl;
            #endif
        }
        
     


}