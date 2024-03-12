#include <chrono>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <iostream>
#include <iterator>
#include <limits>

// #define DEBUG

class CountingSort{
    private:
        int maxValue;
        std::vector<int> * input;
        std::vector<int> * outputArray;
        std::vector<int> * countArray;

    void init(){
        // Get the minimun possible value on int.
        maxValue = std::numeric_limits<int>::min();
        outputArray = new std::vector<int>(input->size(), 0);

        // Starts algorithms
        // Get max value
        // Initialize the vector with zeroes
        searchMax();
        countArray = new std::vector<int>(maxValue+1, 0);
        // Count all occurences on the N vector.
        countArrayInitialization();
        // Do the cummulative sum on the vector of occurrences.
        makeCumulativeCount();
        // Do the ordering from each element on the N vector and the vector of Ocurrences M.
        makeOutputArray();
    }

    void searchMax(){
        for (auto it=input->begin(); it != input->end(); it++){
            if (maxValue < *it)
                maxValue=*it;
        }
    }

    void countArrayInitialization(){
        // Counting all occurences.
        for (auto it=input->begin();it!=input->end(); it++){
            countArray->operator[](*it)++;
        }

        #ifdef DEBUG

        std::cout << "NON CUMULATIVE" << std::endl;
        for (auto it = countArray->begin();it!=countArray->end(); it++)
            std::cout << *it << " ";
        std::cout << std::endl;

        #endif
    }

    void makeCumulativeCount(){
        for (auto it=countArray->begin()+1; it!=countArray->end();it++){
            *it+=*(it-1);
        }

        #ifdef DEBUG

        std::cout << "CUMULATIVE" << std::endl;
        for (auto it = countArray->begin();it!=countArray->end(); it++)
            std::cout << *it << " ";
        std::cout << std::endl;

        #endif
    }

    void makeOutputArray(){
        unsigned int actualCellOutput = -1;
        // Counting from reverse from the input
        // For each element of the input, calculate the ordered position by the cummulative occurrences.
        for (auto it=input->rbegin(); it!=input->rend();it++){
            // Accessing to the array of occurrences cummulated, and we get the position -1 because 
            // the cummulative frecuency marks the final possition ordering.
            actualCellOutput = countArray->operator[](*it)-1;
            // Writes to the output with the position precalculated.
            outputArray->operator[](actualCellOutput) = *it;
            //Upgrade the occurrences for the next, minus one ocurrence.
            countArray->operator[](*it)--;

            #ifdef DEBUG
            std::cout << "ActualCell: " << actualCellOutput << " Actual Elem Ordering " << *it << " Sizeof Output Arr " << outputArray -> size()  << std::endl;
            #endif
        }
    }

    public:
        CountingSort(){}

        CountingSort(std::vector<int> * i){
            input = i;
            init();
        }



        CountingSort & operator=(CountingSort * cs){
            this -> input = cs -> input;
            this -> countArray= cs -> countArray;
            this -> outputArray = cs -> outputArray;
            
            return *this;
        }
        
        ~CountingSort(){
            delete input;
            delete countArray;
            delete outputArray;
        }

        int getMaxValue(){
            return maxValue;
        }
        void printResult(){
            std::cout << "INPUT VECTOR" << std::endl;
            for (auto it=input->begin();it!=input->end();it++){
                std::cout << *it << " ";
            }
            std::cout << std::endl;

            std::cout << "ORDERED VECTOR" << std::endl;
            for (auto it=outputArray->begin();it!=outputArray->end();it++){
                std::cout << *it << " ";
            }
            std::cout << std::endl;
        }
};


int main(int argc, char **argv){
	int n, argumento,actual_elem;
	argumento = argc - 3;

    std::chrono::time_point<std::chrono::high_resolution_clock> t0, tf; // Para medir el tiempo de ejecución
	unsigned long int semilla;
    unsigned long tejecucion;
	std::ofstream fsalida;
	
	if (argc <= 3) {
		std::cerr<<"\nError: El programa se debe ejecutar de la siguiente forma.\n\n";
		std::cerr<<argv[0]<<" NombreFicheroSalida Semilla tamCaso1 tamCaso2 ... tamCasoN\n\n";
		return 0;
	}
	
	// Abrimos fichero de salida
	std::string outputfile = std::string(argv[1]) + ".csv";

	fsalida.open(outputfile);
	if (!fsalida.is_open()) {
		std::cerr<<"Error: No se pudo abrir fichero para escritura "<<argv[1]<<"\n\n";
		return 0;
	}
	



	// // Inicializamos generador de no. aleatorios
	semilla= atoi(argv[2]);
	srand(semilla);

    std::vector<int> *input;

    // //Escribimos los nombres de las columnas del output
	fsalida << "Tam Caso,Tiempo Ejecución medido,Costante K,Tiempo Ejecucion Ajustado,Tiempo ejecución teórico\n" ;

	// Pasamos por cada tamanio de caso para el ejercicio 1
	for (int i = 0; i < argumento; i++){
		n = atoi(argv[i+3]);
        input = new std::vector<int>(n);
		
		//Generamos vector aleatorio de prueba, con componentes entre 0 y n-1
		for (int j = 0; j<n; j++){
            actual_elem = rand() % n;
            input->operator[](j)=actual_elem;
        }

        CountingSort * sort;

        t0= std::chrono::high_resolution_clock::now();
        sort = new CountingSort(input);
        tf=std::chrono::high_resolution_clock::now();
        unsigned long tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();
        // N IS THE PROBLEM SIZE AND K THE MAX ELEM SIZE FOR THE SUBVECTOR
        unsigned long int fn=n+sort-> getMaxValue();
        double k= (double) tejecucion / (double) n;
        double tte=k*fn;
		fsalida<<n<<","<<tejecucion<<","<<k<<","<<tte<<","<<fn<<"\n";
        #ifdef DEBUG
        sort->printResult();
        #endif
        delete sort;

      
    }

}
