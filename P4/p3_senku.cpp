#include <iostream>
#include <vector>
#include <utility>

using namespace std;


// VARIABLES GLOBALES: 
vector<vector<int>> tablero = {
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
int n_nodos = n_filas * n_columnas; // 32 fichas, 33 huecos para ponerlas, 49 casillas en total (7x7)

// DEBUG
int contador_it = 0; // Para saber cuantas iteraciones ha hecho el for
int contador_movs_explorados = 0; // Para saber cuantos movimientos fueron explorados
/////

// vector<vector<bool>> visitados(n_filas, vector<bool>(n_columnas, false));


// Vector de movimientos para llegar a la solución.
    // vector de: ( (posicion.x, posicion.y), movimiento )
    //  posicion: posicion en el tablero 
    //  movimiento: 0-->arriba, 1-->derecha, 2-->abajo, 3--> izquierda
vector< pair <pair<int,int>, int> > movimientosSolucion; 


// FUNCIONES:

/**
 * Imprime el tablero
*/
void imprimirTablero(vector<vector<int>> tab) {
    for (int i = 0; i < n_filas; ++i) {
        for (int j = 0; j < n_columnas; ++j) {
            cout << tab[i][j] << " ";
        }
        cout << endl;
    }
}

/**
 * Funcion que devuelve si el estado del tablero actualmente es considerado solución
*/
bool esSolucion(vector<vector<int>> tableroActual) {

    // Si no hay ficha en el medio, no es solución
    if (tableroActual[3][3] == 1) {
        return false;
    }
    // Comprobar que no haya más fichas aparte de la del medio
    for (int i = 0; i < n_filas; ++i) {
        for (int j = 0; j < n_columnas; ++j) {
            if (i != 3 and j!= 3){
                if (i == 0 or i == 1 or i == 5 or i == 6) {
                    if (j >= 2 and j <= 4 and j != 3) {
                        if (tableroActual[i][j] == 0) {
                            return false;
                        }
                    }
                }

                if ((i == 2 or i == 4)) {
                    if (tableroActual[i][j] == 0) {
                        return false;
                    }
                }

                if (i == 3) {
                    if (j >= 0 and j <= 2) {
                        if (tableroActual[i][j] == 0) {
                            return false;
                        }
                    }
                    if (j >= 4 and j <= 6) {
                        if (tableroActual[i][j] == 0) {
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
vector<int> hayMovimientosPosibles (pair<int,int> posicion, vector<vector<int>> tableroActual) {
    vector<int> movimientosPosibles;

    // Arriba?
    if ((posicion.first - 2) >= 0){ // No se sale del tablero
        if (tableroActual[posicion.first - 2][posicion.second] == 1) { // cuando salte hay una casilla libre
            if (tableroActual[posicion.first - 1][posicion.second] == 0) { // ficha a comer que tiene justo delante
                movimientosPosibles.push_back(0);
            }
        }
    }

    // Derecha?
    if ((posicion.second + 2) < n_columnas){ // No se sale del tablero
        if (tableroActual[posicion.first][posicion.second + 2] == 1) { // cuando salte hay una casilla libre
            if (tableroActual[posicion.first][posicion.second + 1] == 0) { // ficha a comer que tiene justo delante
                movimientosPosibles.push_back(1);
            }
        }   
    }

    // Abajo?
    if ((posicion.first + 2) < n_columnas){ // No se sale del tablero
        if (tableroActual[posicion.first + 2][posicion.second] == 1) { // cuando salte hay una casilla libre
            if (tableroActual[posicion.first + 1][posicion.second] == 0) { // ficha a comer que tiene justo delante
                movimientosPosibles.push_back(2);
            }
        }    
    }

    // Izquierda?
    if ((posicion.second - 2) >= 0){ // No se sale del tablero
        if (tableroActual[posicion.first][posicion.second - 2] == 1) { // cuando salte hay una casilla libre
            if (tableroActual[posicion.first][posicion.second - 1] == 0) { // ficha a comer que tiene justo delante
                movimientosPosibles.push_back(3);
            }
        }    
    }


    return movimientosPosibles;
}

/**
 * Función que actualiza el tablero según el movimiento de la ficha que se le pase
 * Devuelve el tablero actualizado
*/
vector<vector<int>> ejecutarMovimientoEnTablero (pair<int,int> pos, int movimiento, vector<vector<int>> tablero) {
    // Asumimos que es un movimiento posible porque tenemos una función
    // que devuelve movimientos posibles

    vector<vector<int>> n_tab = tablero;

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
void P3_Backtracking(pair<int,int> posActual, int movimientoSiguiente, int n, vector<vector<int>> tablero_actual, vector< pair <pair<int,int>, int> > & movimientos) {
    if (esSolucion(tablero_actual)) {
        movimientosSolucion.resize(movimientos.size());
        movimientosSolucion = movimientos;
        return;
    }

    if (movimientos.size() >= 32){ 
        return;
    }

    vector<vector<int>> tablero_actualizado = tablero_actual;


    // Si se ha hecho un movimiento, se aplica al nodo que estamos explorando
    if (movimientoSiguiente != -1){

        // DEBUG: Imprimir tablero ántes de hacer el movimiento
        // cout << "Tablero antes: " << endl;
        // imprimirTablero(tablero_actual);
        // cout << endl;
        //////


        // Se hace el siguiente movimiento con la ficha que es
        movimientos.push_back(make_pair(posActual, movimientoSiguiente)); // antes siguienteMovimiento(posActual, movimientoSiguiente)
        tablero_actualizado = ejecutarMovimientoEnTablero(posActual, movimientoSiguiente, tablero_actualizado); // actualiza tablero


        // DEBUG: Imprimir tablero despues del movimiento hecho
        // std::string mov = "";
        // cout << "tablero despues:"<<endl;
        // cout << "ficha: (" << posActual.first << "," << posActual.second << ") movio ";
        // if (movimientoSiguiente == 0) mov = "arriba";
        // else if (movimientoSiguiente == 1) mov = "derecha";
        // else if (movimientoSiguiente == 2) mov = "abajo";
        // else if (movimientoSiguiente == 3) mov = "izquierda";
        
        // cout << mov << endl;
        // imprimirTablero(tablero_actualizado);
        // cout << endl << endl;
        //////
    }

    if (movimientos.size() < 31) {
        for (int i = 0; i < n; i++) {
            contador_it++;
            // Fila y columna para saber que nodo es en el tablero, yendo en orden de fila
            int fila = i / n_filas;
            int columna = i % n_columnas;
        
            // Valor del nodo explorandose actualmente
            int nodo_actual = tablero_actualizado[fila][columna]; 

            // Posicion actual del tablero (ficha que estamos evaluando)
            pair<int,int> posicionActual = make_pair(fila, columna);

            // Si es una casilla evaluable
            if (nodo_actual == 0) {
                // Explorar posibles casos de la ficha actual
                vector<int> posiblesMovimientos = hayMovimientosPosibles(posicionActual, tablero_actualizado);

                // Si hay posibles movimientos de la ficha actual, explorarlos (generar sus correspondientes nodos)
                if (!posiblesMovimientos.empty()) {
                        // DEBUG: Movimientos posibles detectados
                        // cout << "---- Hay " << posiblesMovimientos.size() << " movimientos posibles " << endl;
                        ///////
                    
                    // Itera por los movimientos posibles
                    for (int p = 0; p < posiblesMovimientos.size(); p++) {
                        // DEBUG: Movimientos hechos hasta el momento en toda la ejecución
                        contador_movs_explorados++;
                        // cout << "Movimiento nº " << contador_movs_explorados << " siendo explorado de la iteracion " << contador_it << endl;
                        ///////

                        // Se hace llamada recursiva para crear ese nuevo nodo (ejecutando el movimiento posible)
                        P3_Backtracking(posicionActual, posiblesMovimientos[p], n, tablero_actualizado, movimientos); 

                        // La llamada recursiva devuelve el control
                        movimientos.pop_back();
                    }

                }
            }
        }
    }


    
}

int main() {
    vector< pair <pair<int,int>, int> > movimientos;
    P3_Backtracking(make_pair(0,0), -1, n_nodos, tablero, movimientos);
    
    cout << endl << "\t*****Número de movimientos de la solucion: " << movimientosSolucion.size() << endl;

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

    // DEBUG contadores de iteraciones y movimientos explorados en total
    // cout << endl << "Contador iteraciones for: " << contador_it << endl;
    // cout << endl << "Contador movimientos explorados: " << contador_movs_explorados << endl;
    ///////


    return 0;
}
