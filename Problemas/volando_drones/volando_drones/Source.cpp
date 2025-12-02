
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include "IndexPQ.h"

using namespace std;


/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

void volar(IndexPQ<int, greater<int>>& grandes, IndexPQ<int, greater<int>>& peques, const int& N) {
	int i = 0;
	int tiempo = 0;
	while (!grandes.empty() && !peques.empty()) {
		if (i >= N) {
			cout << tiempo << " ";
			tiempo = 0;
			i = 0;
		}
		else {
			auto big = grandes.top();
			auto small = peques.top();
			if (big.prioridad > small.prioridad) {
				grandes.update(big.elem, big.prioridad - small.prioridad);
				peques.pop();
				tiempo += small.prioridad;
			}
			else if (big.prioridad < small.prioridad) {
				peques.update(small.elem, small.prioridad - big.prioridad);
				grandes.pop();
				tiempo += big.prioridad;
			}
			else { // son iguales
				grandes.pop();
				peques.pop();
				tiempo += big.prioridad;
			}
			i++;
		}
	}
	cout << tiempo << endl;
}

bool resuelveCaso() {
	int N, A, B; // a = 9V, b =1.5V
	cin >> N >> A >> B;
	if (!std::cin)  // fin de la entrada
		return false;
	IndexPQ<int, greater<int>> grandes(A);
	IndexPQ<int, greater<int>> peques(B);
	for (int i = 0; i < A; i++) {
		int aux; cin >> aux;
		grandes.push(i, aux);
	}
	for (int i = 0; i < B; i++) {
		int aux; cin >> aux;
		peques.push(i, aux);
	}
	volar(grandes, peques, N);

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
