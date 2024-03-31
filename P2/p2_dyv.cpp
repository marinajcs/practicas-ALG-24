#include <iostream> 
#include <vector> 
#include <utility>
 
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
 
int main() { 
    vector<int> tuercas = {4, 7, 10, 8, 2, 6, 1, 5, 3}; 
    vector<int> tornillos = {5, 2, 4, 6, 7, 3, 8, 10, 1};

    cout << "Tuercas desordenadas: "; 
    for (int tuerca : tuercas) cout << tuerca << " "; 
    cout << "\nTornillos desordenados: "; 
    for (int tornillo : tornillos) cout << tornillo << " "; 
    cout << endl; 
 
    ordenarTuercasTornillos(tuercas, tornillos, 0, tuercas.size() - 1); 
 
    cout << "Tuercas ordenadas: "; 
    for (int tuerca : tuercas) cout << tuerca << " "; 
    cout << "\nTornillos ordenados: "; 
    for (int tornillo : tornillos) cout << tornillo << " "; 
    cout << endl; 
 
    return 0; 
}
