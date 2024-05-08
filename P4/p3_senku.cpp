#include <iostream>
#include <vector>
#include <utility>

using namespace std;

// vector<vector<int>> tablero = {
//     {2, 2, 0, 0, 0, 2, 2},
//     {2, 2, 0, 0, 0, 2, 2},
//     {0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 1, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0},
//     {2, 2, 0, 0, 0, 2, 2},
//     {2, 2, 0, 0, 0, 2, 2},
// };


// VARIABLES GLOBALES: 

int tablero[7][7] = {
    {2, 2, 0, 0, 0, 2, 2},
    {2, 2, 0, 0, 0, 2, 2},
    {0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0},
    {2, 2, 0, 0, 0, 2, 2},
    {2, 2, 0, 0, 0, 2, 2},
};
// 0: ficha, 1: vacío, 2: no jugable


int n_filas = 7, n_columnas = 7;
int n_nodos = n_filas*n_columnas; // 32 fichas, 33 huecos para ponerlas, 42 casillas en total (7x7)
int num_movimientos = 0;


// Vector para ver que ficha ha sido movida (????)
vector<bool> movimiento_hecho;

// Vector de movimientos para llegar a la solución.
    // vector de: ( (posicion.x, posicion.y), movimiento )
    //  posicion: posicion en el tablero 
    //  movimiento: 0-->arriba, 1-->derecha, 2-->abajo, 3--> izquierda
vector< pair <pair<int,int>, int> > movimientosSolucion; 




/**
 * Funcion que devuelve si el estado del tablero actualmente es considerado solución
*/
bool esSolucion() {

    // Si no hay ficha en el medio, no es solución
    if (tablero[3][3] == 1) {
        return false;
    }

    // Comprobar que no haya más fichas aparte de la del medio
    for (int i = 0; i < n_filas; ++i) {
        for (int j = 0; j < n_columnas; ++j) {

            if (i == 0 or i == 1 or i == 5 or i == 6) {
                if (j >= 2 and j <= 4) {
                    if (tablero[i][j] == 0) {
                        return false;
                    }
                }
            }

            if (i == 2 or i == 4) {
                if (tablero[i][j] == 0) {
                    return false;
                }
            }

            if (i == 3) {
                if (j >= 0 and j <= 2) {
                    if (tablero[i][j] == 0) {
                        return false;
                    }
                }
                if (j >= 4 and j <= 6) {
                    if (tablero[i][j] == 0) {
                        return false;
                    }
                }
            }
        }
    }

    cout << "Solucion encontrada!" << endl;

    return true;
}

/**
 * Devuelve los movimientos posibles, vacío si no hay movimientos posibles.
*/
vector<int>  hayMovimientosPosibles (pair<int,int> posicion) {
    vector<int> movimientosPosibles;

    // Arriba?
    if (tablero[posicion.first - 2][posicion.second] == 1) { // cuando salte hay una casilla libre
        if (tablero[posicion.first - 1][posicion.second] == 0) { // ficha a comer que tiene justo delante
            movimientosPosibles.push_back(0);
        }
    }

    // Derecha?
    if (tablero[posicion.first][posicion.second + 2] == 1) { // cuando salte hay una casilla libre
        if (tablero[posicion.first][posicion.second + 1] == 0) { // ficha a comer que tiene justo delante
            movimientosPosibles.push_back(1);
        }
    }

    // Abajo?
    if (tablero[posicion.first + 2][posicion.second] == 1) { // cuando salte hay una casilla libre
        if (tablero[posicion.first + 1][posicion.second] == 0) { // ficha a comer que tiene justo delante
            movimientosPosibles.push_back(2);
        }
    }

    // Izquierda?
    if (tablero[posicion.first][posicion.second - 2] == 1) { // cuando salte hay una casilla libre
        if (tablero[posicion.first][posicion.second - 1] == 0) { // ficha a comer que tiene justo delante
            movimientosPosibles.push_back(3);
        }
    }

    return movimientosPosibles;
}

/**
 * Devuelve el movimiento resultante de mover la ficha que se pasa por parámetro
*/
pair <pair<int,int>, int> siguienteMovimiento (pair<int,int> posicion, int movimiento) {
    pair <pair<int,int>, int> movimientoSiguiente;

    // Arriba
    if (movimiento == 0) {
        movimientoSiguiente = make_pair( make_pair(posicion.first-2, posicion.second), movimiento );
    }
    // Derecha
    else if (movimiento == 1) {
        movimientoSiguiente = make_pair( make_pair(posicion.first, posicion.second+2), movimiento );
    }
    // Abajo
    else if (movimiento == 2) {
        movimientoSiguiente = make_pair( make_pair(posicion.first+2, posicion.second), movimiento );
    }
    // Izquierda
    else if (movimiento == 3) {
        movimientoSiguiente = make_pair( make_pair(posicion.first, posicion.second-2), movimiento );
    }
    else{
        movimientoSiguiente = make_pair( make_pair(posicion.first, posicion.second), -1);
    }

    return movimientoSiguiente;
}

void imprimirTablero() {
    for (int i = 0; i < n_filas; ++i) {
        for (int j = 0; j < n_columnas; ++j) {
            cout << tablero[i][j] << " ";
        }
        cout << endl;
    }
}


/**
 * k = nodo actual siendo explorado
 * mov = movimiento a hacer
 * n = numero de nodos (32) 32 fichas, 33 huecos
 * movimientos = movimientos hasta el momento explorandose
*/
void P3_Backtracking(int k, int movimientoSiguiente, int n, vector< pair <pair<int,int>, int> > & movimientos) {
    if (esSolucion()) {
        movimientosSolucion = movimientos;
        return;
    } else if (movimiento_hecho[k]) {
        P3_Backtracking(k + 1, -1, n, movimientos);
    }

    for (int i = 0; i < n; i++) {
        // Fila y columna para saber que nodo es en el tablero, yendo en orden de fila
        int fila = i / n_filas;
        int columna = i % n_columnas;

        // Valor del nodo explorandose actualmente
        int nodo_actual = tablero[fila][columna]; 

        // Si no es una casilla no evaluable
        if (nodo_actual != 2) {
            if (!movimiento_hecho[i]) { // esto tiene sentido?
                
                // Si se ha hecho un movimiento, se aplica al nodo que estamos explorando (va fuera del for?)
                if (movimientoSiguiente != -1){
                    // Se hace el siguiente movimiento con la ficha que es
                    movimientos.push_back(siguienteMovimiento(movimientos[i].first, movimientoSiguiente));
                }

                // Explorar posibles casos de la ficha actual
                vector<int> posiblesMovimientos = hayMovimientosPosibles(movimientos[i].first);

                // Si hay posibles movimientos de la ficha actual, explorarlos (generar sus correspondientes nodos)
                if (!posiblesMovimientos.empty()) {
                    for (int p = 0; p < posiblesMovimientos.size(); p++){
                        // Se hace llamada recursiva para crear ese nuevo nodo (ejectuando el movimiento posible)
                        P3_Backtracking(k + 1, posiblesMovimientos[p], n, movimientos); 

                        // La llamada recursiva devuelve el control
                        movimientos.pop_back();
                        movimiento_hecho[k] = movimiento_hecho[i] = false;
                    }
                }
                else{
                    return; // Si no hay posibles movimientos, vuelve??
                }
                

            }
        }


        
    }
}

int main() {
    vector< pair <pair<int,int>, int> > movimientos;
    P3_Backtracking(0, -1, n_nodos, movimientos);
    
    cout << "Número de movimientos: " << movimientos.size() << endl;
    
    cout << "Movimientos" << endl;
    for (int i = 0; i < movimientosSolucion.size(); i++) {
        std::string movimiento = "";
        if      (movimientosSolucion[i].second == 0) movimiento = "arriba";
        else if (movimientosSolucion[i].second == 1) movimiento = "derecha";
        else if (movimientosSolucion[i].second == 2) movimiento = "abajo";
        else if (movimientosSolucion[i].second == 3) movimiento = "izquierda";


        cout << "- Movimiento " << i << ": (" << movimientosSolucion[i].first.first << ", " << movimientosSolucion[i].first.second << ") y " << movimiento << endl;
    }

    return 0;
}
