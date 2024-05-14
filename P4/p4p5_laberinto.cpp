#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 10000;
const int FIL = 5;
const int COL = 5;
const int ADYANCENTES = 4; //Numero de casillas adyacentes

// Direcciones posibles: arriba, abajo, izquierda, derecha
int posicionesx[] = {-1, 1, 0, 0};
int posicionesy[] = {0, 0, -1, 1};

//int posicionesx[] = {0, 1, -1, 0};  // Posibles valores de x
//int posicionesy[] = {1, 0, 0, -1};  // Posibles valores de y

void mostrarLaberinto(bool laberinto[FIL][COL]){
    for (int i = 0; i < FIL; ++i) {
        for (int j = 0; j < COL; ++j) {
            if (laberinto[i][j] == false)
                cout << "X" << " ";
            else
                cout << "·" << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void mostrarCamino(bool laberinto[FIL][COL], vector<vector<bool>>& camino){
    for (int i = 0; i < FIL; ++i) {
        for (int j = 0; j < COL; ++j) {
            if (laberinto[i][j] == false)
                cout << "X" << " ";
            else{
                if (camino[i][j] == true)
                    cout << "*" << " ";
                else
                    cout << "·" << " ";
            }     
        }
        cout << endl;
    }
    cout << endl;
}

void mostrarCaminoBB(bool laberinto[FIL][COL], vector<vector<bool>>& camino, vector<pair<int,int>>& solucion){

    for(int i=0; i<solucion.size(); i++)
        camino[solucion[i].first][solucion[i].second] = true;
    
    for (int i = 0; i < FIL; ++i) {
        for (int j = 0; j < COL; ++j) {
            if (laberinto[i][j] == false)
                cout << "X" << " ";
            else{
                if (camino[i][j] == true)
                    cout << "*" << " ";
                else
                    cout << "·" << " ";
            }     
        }
        cout << endl;
    }
    cout << endl;
}
void mostrarCaminoAlgoritmo(bool laberinto[FIL][COL], vector<pair<int,int>>& camino) {
    for (int i = 0; i < FIL; ++i) {
        for (int j = 0; j < COL; ++j) {
            if (laberinto[i][j] == false)
                cout << "X" << " ";
            else {
                bool esCamino = false;
                for (auto& coord : camino) {
                    if (coord.first == i && coord.second == j) {
                        esCamino = true;
                        break;
                    }
                }
                if (esCamino)
                    cout << "*" << " "; // Casilla perteneciente al camino
                else
                    cout << "·" << " "; // Casilla no visitada
            }
        }
        cout << endl;
    }
    cout << endl;
}

void mostrarSolucion(vector<pair<int,int>>& solucion, int tipo){
    cout << "El camino para salir del laberinto es:" << endl;

    if (tipo==0) // Solucion Backtracking
        for (int i = solucion.size() - 1; i >= 0; --i) 
            cout << "(" << solucion[i].first << "," << solucion[i].second << ") ";
    
    if (tipo==1) // Solucion B&B
        for (int i = 0; i < solucion.size(); ++i) 
            cout << "(" << solucion[i].first << "," << solucion[i].second << ") ";
    
    cout << endl << endl;
}

// Función que comprueba si es posible moverse a una casilla
bool puedeAvanzar(int x, int y, bool laberinto[FIL][COL]){
    return (x >= 0 && x < FIL && y >= 0 && y < COL && laberinto[x][y]);
}

bool salirLaberinto(int x, int y, int xfin, int yfin,  bool laberinto[FIL][COL], vector<pair<int,int>>& solucion, vector<vector<bool>>& visitados, vector<vector<bool>>& camino){
    visitados[x][y] = true; // Marcamos la casilla actual como visitada

    // Llegamos a la salida
    if (x == xfin && y == yfin){
        solucion.push_back({x, y});
        camino[x][y] = true;
        return true;
    }

    // Exploramos las casillas adyacentes
    for (int i = 0; i < ADYANCENTES; ++i){
        int sigX = x + posicionesx[i];
        int sigY = y + posicionesy[i];

        // Si la casilla adyacente es válida y no ha sido visitada, llamamos recursivamente
        if (puedeAvanzar(sigX, sigY, laberinto) && !visitados[sigX][sigY])
            if (salirLaberinto(sigX, sigY, xfin, yfin, laberinto, solucion, visitados, camino)){
                solucion.push_back({x, y}); // Si encontramos un camino desde esta casilla, la añadimos a la solución
                camino[x][y] = true;
                return true;
            }
    }

    return false; // No se encontró un camino desde esta casilla
}


struct Nodo {
    int x, y, costo;
    vector<pair<int,int>> camino;

    Nodo(int _x, int _y, int _costo, const vector<pair<int,int>>& _camino) 
        : x(_x), y(_y), costo(_costo), camino(_camino){}

    bool operator<(const Nodo& otro) const {
        return costo > otro.costo;
    }
};

int calcularHeuristica(int x, int y, int xfin, int yfin) {
    return abs(x - xfin) + abs(y - yfin);
}

bool salirLaberintoBranchBound(int x, int y, int xfin, int yfin, bool laberinto[FIL][COL], vector<pair<int,int>>& solucion, vector<vector<int>>& visitados) {
    priority_queue<Nodo> pq; // Cola para el Branch and Bound

    // Inicializar el primer nodo
    vector<pair<int,int>> caminoInicio = {{x, y}};
    int costoInicial = calcularHeuristica(x, y, xfin, yfin);
    pq.push(Nodo(x, y, costoInicial, caminoInicio));

    visitados[x][y] = pq.size();
      
    while (!pq.empty()) {
        // mostrarCamino(laberinto, visitados);
        Nodo nodoActual = pq.top();
        pq.pop();

        int xActual = nodoActual.x;
        int yActual = nodoActual.y;
        int nivelActual = nodoActual.costo;
        vector<pair<int,int>> caminoActual = nodoActual.camino;

        // Verificar si se llegó a la salida
        if (xActual == xfin && yActual == yfin) {
            solucion = caminoActual;
            return true;
        }

        // Explorar las casillas adyacentes
        for (int i = 0; i < ADYANCENTES; ++i) {
            int sigX = xActual + posicionesx[i];
            int sigY = yActual + posicionesy[i];

            // Verificar si la casilla adyacente es válida y no ha sido visitada
            if (puedeAvanzar(sigX, sigY, laberinto)) {
                // Calcular la estimación (heurística) para el nodo adyacente (Branch and Bound)
                
                int nuevoCosto = caminoActual.size() + 1;
                int heuristica = calcularHeuristica(sigX, sigY, xfin, yfin);
                int costoTotal = nuevoCosto + heuristica;

                if(nuevoCosto < visitados[sigX][sigY]){
                    visitados[sigX][sigY] = nuevoCosto;

                    vector<pair<int, int>> nuevoCamino = caminoActual;
                    nuevoCamino.push_back({sigX,sigY});

                    pq.push(Nodo(sigX,sigY, costoTotal, nuevoCamino));
                }
            }
        }
    }
    
    return false; // No se encontró un camino desde esta casilla
}

int main(){

    bool laberinto[FIL][COL] = {
        {true, false, true, true, true},
        {true, true, true, false, true},
        {true, false, true, false, true},
        {true, true, true, false, true},
        {false, true, false, true, true},
    };

    pair<int,int> entrada = {0,0}; 
    pair<int,int> salida = {FIL-1,COL-1};

    vector<vector<bool>> visitados(FIL, vector<bool>(COL, false)); // Matriz visitados en Backtracking
    vector<vector<int>> visitadosBB(FIL, vector<int>(COL, INF)); // Para marcar casillas visitadas en B&B

    vector<vector<bool>> caminobt(FIL, vector<bool>(COL, false));  // Matriz camino para ver el camino
    vector<vector<bool>> caminobb(FIL, vector<bool>(COL, false));  // Matriz camino para ver el camino

    vector<pair<int,int>> solucionbt, solucionbb;

    // Mostrar la matriz
    cout << "La matriz ingresada es:" << endl;
    mostrarLaberinto(laberinto);

    cout << "Ejercicio 4: Laberinto Backtracking" << endl << endl;    

    salirLaberinto(entrada.first, entrada.second, salida.first, salida.second, laberinto, solucionbt, visitados, caminobt);

    mostrarSolucion(solucionbt,0);
    mostrarCamino(laberinto, caminobt);

    cout << "Ejercicio 5: Laberinto Branch & Bound" << endl << endl;

    salirLaberintoBranchBound(entrada.first, entrada.second, salida.first, salida.second, laberinto, solucionbb, visitadosBB);

    mostrarSolucion(solucionbb,1);
    mostrarCaminoBB(laberinto, caminobb, solucionbb);

    return 0;
}