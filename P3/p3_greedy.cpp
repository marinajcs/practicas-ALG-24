
#include <iostream>
#include <vector>
#include <chrono>

using namespace std;


vector<int> gasolinerasGreedy(vector<int> gasolineras, const int depositoCombustible){
	vector<int> plan_viaje;
	
	
	for (int i = 0; !gasolineras.empty(); i++) {
		int gasolineraMasLejana = 0;
		int depositoCombustibleaux = depositoCombustible;
	bool terminar = false;
	
		for(auto it = gasolineras.begin(); it != gasolineras.end() && !terminar; it++){
			depositoCombustibleaux -= (*it);
			gasolineraMasLejana += (*it);
		
			if(depositoCombustibleaux < 0){
				depositoCombustibleaux += (*it);
				gasolineraMasLejana -= (*it);
				terminar = true;
			}

			if(!gasolineras.empty()){
				it = gasolineras.erase(it);
			}
		}
		plan_viaje.push_back(gasolineraMasLejana);
	}
	
	return plan_viaje;
}


int main(){
	int tamanio_vector = 50;     

	vector<int> vectorSolucion;
	int depositoCombustible = 100;      

	for (int i = 0; i < tamanio_vector; i++)  
		vectorSolucion.push_back((rand() % 60) + 20);


	vectorSolucion = gasolinerasGreedy(vectorSolucion, depositoCombustible);

	

	for (int i = 0; i < vectorSolucion.size(); i++)
	{
		cout << "Kilometros recorridos hasta la siguiente gasolinera:  " << vectorSolucion[i] << endl;
	}
	cout << "Numero de gasolineras recorridas: " << vectorSolucion.size() << endl;
}