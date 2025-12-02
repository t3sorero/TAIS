
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#include <algorithm>
#include"PriorityQueue.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>


bool resuelveCaso() {
	int N;
	cin >> N;

	if (N == 0)  // fin de la entrada
		return false;

	vector<long long int> v;
	for (int i = 0; i < N; i++) {
		int d; cin >> d;
		v.push_back(d);
	}
	// resolver el caso posiblemente llamando a otras funciones
	PriorityQueue<long long int> pq(v);

	long long int total = 0;
	while (pq.size()>1) {
		long long int a = pq.top(); pq.pop();
		long long int b = pq.top(); pq.pop();
		total += a + b;
		pq.push(a + b);
	}
	cout << total << "\n";
	
	// escribir la solución

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
