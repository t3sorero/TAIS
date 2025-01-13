
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include<algorithm>

using namespace std;

#include "IndexPQ.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct Actividad {
	int inicio;
	int final;
};
bool operator < (Actividad a1, Actividad a2) {
	return a1.inicio < a2.inicio;
}


bool resuelveCaso() {
	int N;
	cin >> N;

	if (N ==0)  // fin de la entrada
		return false;
	vector<Actividad> v(N);
	for (int i = 0; i < N; i++) {
		cin >> v[i].inicio >> v[i].final;
	}

	sort(v.begin(), v.end());

	IndexPQ<int> pq(N);
	pq.update(0, v[0].final);
	int k = 0;
	for (int i = 1; i < N; i++) {
		
		if (pq.top().prioridad > v[i].inicio) {
			k++;
			pq.push(k, v[i].final);
		}
		else
			pq.update(pq.top().elem, v[i].final);
	}
	cout << k << "\n";

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
