#include <iostream>
#include <vector>

int finMaxComensales(std::vector<std::vector<int>>& C) {
    int j = 0;
    int i = 0;
    int c = 0;

    int max = 1;
    // S
    std::vector<int> sentados(C.size(), 0);
    // CV
    std::vector<int> comensalesVisitados(C.size(), 0);

    // Empezamos con el comensal 0
    comensalesVisitados[0] = 1;

    // Evaluamos las aristas de adyyacencia o de conveniencia.
    while (i < C.size() && j < C[i].size()) {
        if (c >= C.size() - 1) {
            break;
        }

        // Vamos evaluando los comensales
        // Si el peso es mayor se indica cual es en el vector sentados y se almacena el max el peso
        if (j != i && (comensalesVisitados[j] == 0) && C[i][j] > max) {
            max = C[i][j];
            // Marcamos quien esta sentado a un lado del comensal
            sentados[c] = j;
        }

        j++;

        // Hemos llegado al final de las evaluacioens, todas las columnas se han evaulado
        if (j == C[i].size()) {
            // Debug of elegidos
            std::cout << i << " -> " << sentados[i] << " VALUE: " << C[i][sentados[i]] << std::endl;

            // Marcamos el elegido de mayor peso como visitado
            comensalesVisitados[sentados[c]] = 1;

            // reseteo del selector
            max = 1;
            j = 0;
            i = sentados[c] - 1;
            c++;

            // std::cout << comensalesVisitados << std::endl;
        }
    }

    // Salida
    int sum = 0;
    for (int i = 0; i < sentados.size(); i++) {
        if (sentados[i] == 0) {
            std::cout << i << " -> " << sentados[i] << " VALUE: " << C[i][sentados[i]] << std::endl;
        }
        sum += C[i][sentados[i]];
    }

    std::cout << "Maximal Convenience is: " << sum << std::endl;
    return sum;
}

int main() {
    // Input Matrix
    std::vector<std::vector<int>> C = {
        {0, 50, 80, 30},
        {50, 0, 30, 60},
        {80, 30, 0, 20},
        {30, 60, 20, 0}
    };

    finMaxComensales(C);
    return 0;
}

