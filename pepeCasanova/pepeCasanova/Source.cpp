
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include<queue>
#include<utility>
using namespace std;

struct Cancion{
	int duracion;
	int puntucion;
};

struct Nodo {
	vector <bool> sol;
	int k; // nivel en el que estamos
	int duracion_acum1; //duracion acumulada cara 1
	int duracion_acum2; // duracion acumulada cara 2
	int puntuacion_acum; // putacion acumulada
	double prioridad; //prioridad en la cola
	bool operator < (Nodo const& otro) const {
		return otro.prioridad > prioridad;
	}
};



int estimacion_voraz(vector<Cancion> const& canciones, int D, Nodo const& X) {
	int hueco = D - (X.duracion_acum1 + X.duracion_acum2);
	int estimacion = X.puntuacion_acum;
	int i = X.k + 1;

	while (i < canciones.size() && canciones[i].duracion <= hueco) {
		Cancion c = canciones[i];
		hueco -= c.duracion;
		estimacion += c.puntucion;
		i++;
	}
	if (i < canciones.size())
		estimacion += (hueco / canciones[i].duracion) * canciones[i].puntucion;

	return estimacion;
}

void eligirMejorCinta(vector<Cancion> const& canciones, int D, vector<bool> &sol_mejor, int &puntuacion_mejor) {
	int N = canciones.size();
	Nodo Y;
	Y.sol = vector<bool>(N);
	Y.k = -1;
	Y.duracion_acum1 = 0;
	Y.duracion_acum2 = 0;
	Y.puntuacion_acum = 0;
	Y.prioridad = estimacion_voraz(canciones, D, Y);
	priority_queue<Nodo> cola;
	cola.push(Y);
	puntuacion_mejor = -1;

	while (!cola.empty() && cola.top().prioridad > puntuacion_mejor) {
		Y = cola.top(); cola.pop();
		Nodo X(Y);
		++X.k;
		// probamos meter la cancion en primera cara
		if (Y.duracion_acum1 + canciones[X.k].duracion <= D) {
			X.sol[X.k] = true;
			X.duracion_acum1 += canciones[X.k].duracion;
			X.duracion_acum2 = Y.duracion_acum2;
			X.puntuacion_acum = Y.puntuacion_acum + canciones[X.k].puntucion;
			X.prioridad = Y.prioridad;
			if (X.k == N - 1) {
				sol_mejor = X.sol;
				puntuacion_mejor = X.puntuacion_acum;
			}
			else
				cola.push(X);
		}
		// probamos a meter la cancion en la segunda cara
		else if (Y.duracion_acum2 + canciones[X.k].duracion <= D) {
			X.sol[X.k] = true;
			X.duracion_acum2 += canciones[X.k].duracion;
			X.duracion_acum1 = Y.duracion_acum1;
			X.puntuacion_acum = Y.puntuacion_acum + canciones[X.k].puntucion;
			X.prioridad = Y.prioridad;
			if (X.k == N - 1) {
				sol_mejor = X.sol;
				puntuacion_mejor = X.puntuacion_acum;
			}
			else 
				cola.push(X);
		}
		//probamos a no meter la cancion en ninguna cara
		X.sol[X.k] = false;
		X.duracion_acum1 = Y.duracion_acum1;
		X.duracion_acum2 = Y.duracion_acum2;
		X.puntuacion_acum = Y.puntuacion_acum;
		X.prioridad = estimacion_voraz(canciones, D, X);
		if (X.k == N - 1) {
			sol_mejor = X.sol;
			puntuacion_mejor = X.puntuacion_acum;
		}
		else
			cola.push(X);
	}
}

bool resuelveCaso() {
	int n; cin >> n;

	if (n ==0)  // fin de la entrada
		return false;

	int D;
	cin >> D;
	vector<Cancion> canciones;
	for (int i = 0; i < n; i++) {
		int d, p; cin >> d >> p;
		canciones.push_back({ d,p });
	}
	vector<bool>solMejor;
	int puntuacion_mejor;
	eligirMejorCinta(canciones, D, solMejor, puntuacion_mejor);
	cout << puntuacion_mejor << "\n";

	return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	if (!in.is_open())
		std::cout << "Error: no se ha podido abrir el archivo de entrada." << std::endl;
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso());

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	std::cout << "Pulsa Intro para salir..." << std::flush;
	std::cin.get();
#endif
	return 0;
}
