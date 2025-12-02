
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

void resolver(IndexPQ<int, less<int>>& queue,const int &p1, const int &p2) {
	if (p1 < p2) {
		queue.push(queue.size(), p1);
		queue.push(queue.size(), p2);
	}
	else {
		queue.push(queue.size(), p2);
		queue.push(queue.size(), p1);
	}
	cout << queue.priority((queue.size() / 2)+1) << " ";
}

bool resuelveCaso() {
	int edad, p;
	cin >> edad >> p;
	IndexPQ<int,less<int>> queue ((p*2) +1);
	queue.push(0, edad);
	if (edad == 0)
		return false;
	for (int i = 0; i < p; i++) {
		int p1, p2;
		cin >> p1 >> p2;
		resolver(queue, p1, p2);
	}
	cout << endl;

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
