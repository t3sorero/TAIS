
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include<queue>

using namespace std;

#include "PriorityQueue.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct Caja
{
	int numCaja;
	int tiempo;

	bool operator<(Caja const& otra) const {
		if (tiempo == otra.tiempo)
			return numCaja < otra.numCaja;
		else
			return tiempo < otra.tiempo;
	}
};

bool resuelveCaso() {
	// leer los datos de la entrada
	int N, C;
	cin >> N >> C;
	
	if (N==0 && C == 0)
		return false;

	PriorityQueue <Caja, less<Caja>> pq;

	if (N > C) {
		cout << C + 1 << endl;
		for (int i = 0; i < C; ++i) {
			int x;
			cin >> x;
		}
		return true;
	}
	for (int i = 0; i < N; ++i) {
		int x;
		cin >> x;
		pq.push({ i,x });
	}
	for (int i = N; i < C; ++i) {
		int x;
		cin >> x;
		auto p = pq.top();
		pq.pop();
		pq.push({ p.numCaja,x + p.tiempo });
	}

	// escribir la solución
	cout << pq.top().numCaja + 1 << endl;

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
