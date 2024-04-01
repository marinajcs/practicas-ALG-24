#include <vector>
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <fstream>

using namespace std;


void merge(vector<int> &unorderedVector, const int left, const int medio, const int right) {
    // Iteradores, no coge el final, es un rango [left, medio), [medio, right)
    vector<int>::const_iterator begin_array1 = unorderedVector.begin() + left;
    vector<int>::const_iterator end_array1_begin_array2 = unorderedVector.begin() + medio;
    vector<int>::const_iterator end_array2 = unorderedVector.begin() + right;
    // Creamos los arrays
    vector<int> array1(begin_array1, end_array1_begin_array2);
    vector<int> array2(end_array1_begin_array2, end_array2);

    // Averiguamos los tamanios de los subarrays
    int sizeofarray1 = array1.size();
    int sizeofarray2 = array2.size();

    // Empezamos a mezclar
    int i = 0;
    int j = 0;
    // K es el principio del array desordenado con DyQ
    int k = left;

    // Recogemos los elementos mas pequenios entre los dos array hasta que uno de los iteradores i j termine.
    while (i < sizeofarray1 && j < sizeofarray2)
    {
        if (array1[i] <= array2[j])
        {
            unorderedVector[k] = array1[i];
            i++;
        }
        else
        {
            unorderedVector[k] = array2[j];
            j++;
        }
        k++;
    }

    // Recogemos los elementos restantes, que son mas grandes
    while (i < sizeofarray1)
    {
        unorderedVector[k] = array1[i];
        i++;
        k++;
    }

    while (j < sizeofarray2)
    {
        unorderedVector[k] = array2[j];
        j++;
        k++;
    }
}

/*
    Algoritmo de Ordenacion MergeSort. D&C
*/
void mergeSort(vector<int> &unorderedVector, const int left, const int right) {
    // punto medio
    // int medio = (left + (right - left)) / 2;
    int medio = (left+right) / 2;
    // 1 + (2 - 1) / 2 = 2 / 2 = 1  l == m

    /*
        Control de que no se puede dividir mas el array, se convierte en un caso base. Donde medio y left ya son el mismo elemento
    */
    if (medio == left){
        return;
    }

    if (left < right) {
    mergeSort(unorderedVector, left, medio);
    mergeSort(unorderedVector, medio , right);
    merge(unorderedVector, left, medio, right);
    }
}

vector<int> uniqueElements(vector<int> &orderedVector){
    vector<int> unique;
    int actual = -1;
    for (auto it = orderedVector.begin(); it != orderedVector.end(); it++){
        if (actual != *it){
            actual=*it;
            unique.push_back(actual);
        }
    }
        
    return unique;
        
}

int main(int argc, char *argv[]){
        int n, argumento,actual_elem;
        argumento = argc - 3;

        chrono::time_point<std::chrono::high_resolution_clock> t0, tf; // Para medir el tiempo de ejecución
        unsigned long int semilla;
        unsigned long tejecucion;
        ofstream fsalida;
        vector<int> aleatorios_casos;
        
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
  
            cerr << "Ejecutando algoritmo P4 DyV para tam " << n << endl ;

            t0= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecuciÛn del algoritmo

            mergeSort(aleatorios_casos, 0, aleatorios_casos.size());
            vector<int> unique=uniqueElements(aleatorios_casos);

            tf= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que finaliza la ejecuciÛn del algoritmo
            tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();

            cerr << "\tTiempo de ejec. (us): " << tejecucion << " para tam. caso "<< n << endl;
            fsalida << n <<" "<< tejecucion <<"\n";

        }
  
        
        // for (auto it=aleatorios_casos.begin(); it != aleatorios_casos.end(); ++it)
        //     cout << *it << " ";
        // cout << endl;

        // for (auto it=unique.begin(); it != unique.end(); ++it)
        //     cout << *it << " ";
        // cout << endl;


}