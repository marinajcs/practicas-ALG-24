#include <vector>
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <fstream>

//#define DEBUG
using namespace std;

void tornillosTuercasIterativo(vector<int> & cajonA, vector<int> & cajonB){
    int aux = -1;

    for (int i = 0; i < cajonA.size(); ++i){
        for (int j = i; j < cajonB.size(); ++j){
            if (cajonA[i] == cajonB[j]){
                aux = cajonB[j];
                cajonB[j] = cajonB[i];
                cajonB[i] = aux;
            }
        }
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

            tornillosTuercasIterativo(cajonA, cajonB);

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