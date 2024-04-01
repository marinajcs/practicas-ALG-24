#include <vector>
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <fstream>

using namespace std;

// #define DEBUG

vector<int> eliminarDuplicados(vector<int> &vec) {
    vector<int> unique;
    bool encontrado = false;

    if (vec.size() > 0){
        for (int i = 0; i < vec.size(); ++i) {
            for (int j = 0; j < unique.size() && !encontrado;j++) {
                // break if we find duplicate
                if (vec[i] == unique[j]) {
                    encontrado = true;
                } 
            }

            // insert the unique item
            if (!encontrado){
                unique.push_back(vec[i]);
            }

            encontrado = false;
        }
    } 

    return unique;
}

int main(int argc, char *argv[]){
        int n, argumento,actual_elem;
        argumento = argc - 3;

        chrono::time_point<std::chrono::high_resolution_clock> t0, tf; // Para medir el tiempo de ejecución
        int semilla;

        ofstream fsalida;
        vector<int> aleatorios_casos;
        vector<int> unique;
        
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
        srand(semilla);

        // Pasamos por cada tamanio de caso para el ejercicio 1
        for (int i = 0; i < argumento; i++){
            n = atoi(argv[i+3]);
            
            //Generamos vector aleatorio de prueba, con componentes entre 0 y n-1
            for (int j = 0; j<n; j++){
                actual_elem = rand() % n;
                aleatorios_casos.push_back(actual_elem);
            }
            
            
            t0= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecuciÛn del algoritmo
            unique = eliminarDuplicados(aleatorios_casos); // Ejecutamos el algoritmo para tamaÒo de caso n
            tf= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que finaliza la ejecuciÛn del algoritmo
            
            unsigned long tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();
            
            cerr << "n: "<< n << "\t\tTiempo (us): " << tejecucion <<endl;
            fsalida << n <<" "<< tejecucion <<"\n";

        }


        /*
        #ifdef DEBUG
        for (auto it=aleatorios_casos.begin(); it != aleatorios_casos.end(); ++it)
            cout << *it << " ";
        cout << endl;

         for (auto it=unique.begin(); it != unique.end(); ++it)
            cout << *it << " ";
        cout << endl;
        #endif
        */
        
        


}