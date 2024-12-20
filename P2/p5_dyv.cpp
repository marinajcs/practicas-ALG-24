#include <bits/stdc++.h> 

// #define DEBUG

using namespace std; 

// Function for swapping two numbers 
void swap(int& x, int& y) 
{ 
    int temp = x; 
    x = y; 
    y = temp; 
} 
  
void permutations(vector<vector<int> >& res, vector<int> nums, int l, int h) { 
    // Base case 
    // Add the vector to result and return 
    if (l == h) {

        if ( res.size() > 0 && res[res.size()-1][0] == nums[0]  && res[res.size()-1][1] != nums[1] ){
            res.push_back(nums); 
        }
        else if (res.size() == 0){
            res.push_back(nums); 
        }
        
        return; 
    }
  
    // Permutations made 
    for (int i = l; i <= h; i++) { 
  
        // Swapping permutations
        swap(nums[l], nums[i]); 
  
        // Calling permutations for 
        // next greater value of l 
        permutations(res, nums, l + 1, h); 
    } 
} 
  
// Function to get the permutations 
vector<vector<int> > permute(vector<int>& nums) 
{ 
    // Declaring result variable 
    vector<vector<int> > res; 
    int x = nums.size() - 1; 
  
    permutations(res, nums, 0, x);

    return res; 
}
  
int main(int argc, char *argv[]){
        int n, argumento,actual_elem;
        argumento = argc - 3;

        chrono::time_point<std::chrono::high_resolution_clock> t0, tf; // Para medir el tiempo de ejecución
        int semilla;

        ofstream fsalida;
        vector<int> aleatorios_casos;
        vector<vector<int>> res;
        
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
            res = permute(aleatorios_casos);  // Ejecutamos el algoritmo para tamaÒo de caso n
            tf= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que finaliza la ejecuciÛn del algoritmo
            
            unsigned long tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();
            
            cerr << "n: "<< n << "\t\tTiempo (us): " << tejecucion <<endl;
            // Guardamos tam. de caso y t_ejecucion a fichero de salida
            fsalida<<n<<" "<<tejecucion<<"\n";
            #ifdef DEBUG
            for (auto it=aleatorios_casos.begin(); it != aleatorios_casos.end(); ++it)
                cout << *it << " ";
            cout << endl;

            for (auto it=res.begin(); it != res.end(); ++it)
                for (auto it2=*it.begin(); it2 != *it.end(); ++it2)
                    cout << *it2 << " ";
                cout << endl;
            #endif

        }
        
    
        
}
