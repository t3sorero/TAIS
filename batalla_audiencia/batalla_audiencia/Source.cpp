
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

void resolver(IndexPQ<int, greater<int>>& queue, IndexPQ<int, greater<int>>&res, const int & oldD, const int&d) {
	int h = queue.top().elem;
	int k = d - oldD;
	k += res.priority(h);
	res.update(h, k);
	int a, c = 0;
	cin >> c;
	while (c != -1) {
		cin >> a;
		queue.update(c-1, a);
		cin >> c;
	}
}
bool resuelveCaso() {
	int D, C, N, d; 
	cin >> D >> C >> N;
	if (!std::cin)  // fin de la entrada
		return false;
	IndexPQ<int, greater<int>> queue (C);
	IndexPQ<int, greater<int>> res(C);
	for (int i = 0; i < C; i++) {
		int aux;
		cin >> aux;
		queue.push(i, aux);
		res.push(i, 0);
	}
	int oldD = 0;
	for (int i = 0; i < N; i++) {
		cin >> d;
		resolver(queue, res, oldD, d);
		oldD = d;
	}
	int h = queue.top().elem;
	int k = D - oldD;
	k += res.priority(h);
	res.update(h, k);
	for (int i = 0; i< C;i++) {
		if (res.top().prioridad != 0) cout << res.top().elem + 1 << " " << res.top().prioridad << endl;
		res.pop();
	}
	cout << "---\n";
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
