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
int n_nodos = n_filas*n_columnas; // 32 fichas, 33 huecos para ponerlas, 49 casillas en total (7x7)
int num_movimientos = 0;


int contador_it = 0; // Para saber cuantas iteraciones ha hecho el for
int contador_movs_explorados = 0; // Para saber cuantos movimientos fueron explorados


// Vector para ver que ficha ha sido movida (????)
// vector<bool> movimiento_hecho(n_nodos, false);

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
            if (i != 3 and j!= 3){
                if (i == 0 or i == 1 or i == 5 or i == 6) {
                    if (j >= 2 and j <= 4 and j != 3) {
                        if (tablero[i][j] == 0) {
                            return false;
                        }
                    }
                }

                if ((i == 2 or i == 4)) {
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
    if (tablero[posicion.first - 2][posicion.second] == 1 and (posicion.first - 2) >= 0) { // cuando salte hay una casilla libre
        if (tablero[posicion.first - 1][posicion.second] == 0) { // ficha a comer que tiene justo delante
            movimientosPosibles.push_back(0);
        }
    }

    // Derecha?
    if (tablero[posicion.first][posicion.second + 2] == 1 and (posicion.second + 2) < n_columnas) { // cuando salte hay una casilla libre
        if (tablero[posicion.first][posicion.second + 1] == 0) { // ficha a comer que tiene justo delante
            movimientosPosibles.push_back(1);
        }
    }

    // Abajo?
    if (tablero[posicion.first + 2][posicion.second] == 1 and (posicion.first + 2) < n_columnas) { // cuando salte hay una casilla libre
        if (tablero[posicion.first + 1][posicion.second] == 0) { // ficha a comer que tiene justo delante
            movimientosPosibles.push_back(2);
        }
    }

    // Izquierda?
    if (tablero[posicion.first][posicion.second - 2] == 1 and (posicion.second - 2) >= 0) { // cuando salte hay una casilla libre
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

/**
 * Función para imprimir el tablero
*/
void imprimirTablero(int ** tab) {
    for (int i = 0; i < n_filas; ++i) {
        for (int j = 0; j < n_columnas; ++j) {
            cout << tab[i][j] << " ";
        }
        cout << endl;
    }
}

/**
 * Devuelve la siguiente posicion del tablero recorriendo por filas
*/
pair<int,int> siguientePosicion(pair<int,int> posActual) {
    pair<int, int> nuevaPos;

    if (posActual.first == 6 and posActual.first == 6) {
        // ultimo nodo de todos
        nuevaPos.first = -1;
        nuevaPos.second = -1;
    }
    else if (posActual.first <= 5) {
        nuevaPos.first = posActual.first;       // misma fila
        nuevaPos.second = posActual.second + 1; // siguiente columna
    }
    else if (posActual.first == 6 and posActual.first <= 5) {
        nuevaPos.first = posActual.first + 1;   // nueva fila
        nuevaPos.second = 0;                    // primera columna de la nueva fila
    }

    return nuevaPos;
}

/**
 * Función que actualiza el tablero según el movimiento de la ficha que se le pase
 * Devuelve el tablero actualizado
*/
int ** ejecutarMovimientoEnTablero (pair<int,int> pos, int movimiento, int ** tablero) {
    // Asumimos que es un movimiento posible porque tenemos una función
    // que devuelve movimientos posibles

    int ** n_tab = tablero;

    switch (movimiento) {
        case 0: // Hacia arriba
            n_tab[pos.first][pos.second] = 1;     // pasa a estar vacía porque se mueve de ahí
            n_tab[pos.first-1][pos.second] = 1;   // pasa a estar vacía porque se come la ficha 
            n_tab[pos.first-2][pos.second] = 0;   // pasa a estar la ficha porque ha saltado ahí   
            break;
        case 1: // Hacia la derecha
            n_tab[pos.first][pos.second] = 1;     // pasa a estar vacía porque se mueve de ahí
            n_tab[pos.first][pos.second+1] = 1;   // pasa a estar vacía porque se come la ficha 
            n_tab[pos.first][pos.second+2] = 0;   // pasa a estar la ficha porque ha saltado ahí   
            break;
        case 2: // Hacia abajo
            n_tab[pos.first][pos.second] = 1;     // pasa a estar vacía porque se mueve de ahí
            n_tab[pos.first+1][pos.second] = 1;   // pasa a estar vacía porque se come la ficha 
            n_tab[pos.first+2][pos.second] = 0;   // pasa a estar la ficha porque ha saltado ahí   
            break;
        case 3: // Hacia la izquierda
            n_tab[pos.first][pos.second] = 1;     // pasa a estar vacía porque se mueve de ahí
            n_tab[pos.first][pos.second-1] = 1;   // pasa a estar vacía porque se come la ficha 
            n_tab[pos.first][pos.second-2] = 0;   // pasa a estar la ficha porque ha saltado ahí   
            break;
    }

    return n_tab;
}

/**
 * posActual = posicion actual de la ficha a mover
 * movimientoSiguiente = movimiento que hará la ficha en posActual
 * n = numero de nodos (32) 32 fichas, 33 huecos
 * tablero_actual = tablero con las actualizaciones de los movimientos que llevamos hasta el momento
 * movimientos = movimientos hasta el momento explorandose
*/
void P3_Backtracking(pair<int,int> posActual, int movimientoSiguiente, int n, int ** tablero_actual, vector< pair <pair<int,int>, int> > & movimientos) {
    if (esSolucion()) {
        cout << "Llegó a solución con " << movimientos.size() << "movimientos" << endl;
        movimientosSolucion.resize(movimientos.size());
        movimientosSolucion = movimientos;
        // cout << "solucion almacenada" << endl;
        return;
    }

    int ** tablero_actualizado = tablero_actual;

    // Si se ha hecho un movimiento, se aplica al nodo que estamos explorando (va fuera del for?)
    if (movimientoSiguiente != -1){

        cout << "Tablero antes: " << endl;
        imprimirTablero(tablero_actual);

        // Se hace el siguiente movimiento con la ficha que es
        movimientos.push_back(siguienteMovimiento(posActual, movimientoSiguiente)); // antes movimientos[i].first
        tablero_actualizado = ejecutarMovimientoEnTablero(posActual, movimientoSiguiente, tablero_actual); // actualiza tablero
        // posicionActual = movimientos.back().first;  // se actualiza la posicion actual
        std::string mov = "";
        cout << "tablero despues:"<<endl;
        cout << "ficha: ("<<posActual.first<<","<<posActual.second<<") movio ";
        if (movimientoSiguiente == 0) mov = "arriba";
        else if (movimientoSiguiente == 1) mov = "derecha";
        else if (movimientoSiguiente == 2) mov = "abajo";
        else if (movimientoSiguiente == 3) mov = "izquierda";
        
        cout << mov << endl;
        imprimirTablero(tablero_actualizado);
        cout << endl;
    }

    for (int i = 0; i < n; i++) {
        contador_it++;
        // Fila y columna para saber que nodo es en el tablero, yendo en orden de fila
        int fila = i / n_filas;
        int columna = i % n_columnas;

        // Valor del nodo explorandose actualmente
        int nodo_actual = tablero_actualizado[fila][columna]; 

        pair<int,int> posicionActual = make_pair(fila, columna);

        // Si es una casilla evaluable
        if (nodo_actual == 0) {

                // Explorar posibles casos de la ficha actual
                vector<int> posiblesMovimientos = hayMovimientosPosibles(posicionActual);

                // Si hay posibles movimientos de la ficha actual, explorarlos (generar sus correspondientes nodos)
                if (!posiblesMovimientos.empty()) {
                        // cout << "---- Hay " << posiblesMovimientos.size() << " movimientos posibles " << endl;
                    
                    for (int p = 0; p < posiblesMovimientos.size(); p++){
                        contador_movs_explorados++;
                        // Se hace llamada recursiva para crear ese nuevo nodo (ejecutando el movimiento posible)
                        P3_Backtracking(posicionActual, posiblesMovimientos[p], n, tablero_actualizado, movimientos); 

                        // La llamada recursiva devuelve el control
                        movimientos.pop_back();
                    }

                }

        }


        
    }
}

int main() {
    int* tableroPtr[7];
    for (int i = 0; i < 7; ++i) {
        tableroPtr[i] = tablero[i];
    }

    vector< pair <pair<int,int>, int> > movimientos;
    P3_Backtracking(make_pair(0,0), -1, n_nodos, tableroPtr, movimientos);
    
    cout << endl << "\t*****Número de movimientos: " << movimientosSolucion.size() << endl;


    // Si hay solucion, se imprime
    if (movimientosSolucion.size() > 0){
        cout << "Movimientos: " << endl;
        for (int i = 0; i < movimientosSolucion.size(); i++) {
            std::string movimiento = "";
            if      (movimientosSolucion[i].second == 0) movimiento = "arriba";
            else if (movimientosSolucion[i].second == 1) movimiento = "derecha";
            else if (movimientosSolucion[i].second == 2) movimiento = "abajo";
            else if (movimientosSolucion[i].second == 3) movimiento = "izquierda";


            cout << "- Movimiento " << i << ": (" << movimientosSolucion[i].first.first << ", " << movimientosSolucion[i].first.second << ") y " << movimiento << endl;
        }
    }
    else {
        cout << "\tNo se ha encontrado solucion" << endl;
    }

    // Debug
    cout << endl << "contador iteraciones for: " << contador_it << endl;
    cout << endl << "contador movimientos explorados: " << contador_movs_explorados << endl;


    return 0;
}
