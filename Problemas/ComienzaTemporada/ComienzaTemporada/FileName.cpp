
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

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
	// leer los datos de la entrada
	int N, M; cin >> N >> M;

	if (!std::cin)  // fin de la entrada
		return false;
	PriorityQueue<int> jugadores;
	for (int i = 0; i < N; i++) {
		int a; cin >> a;
		jugadores.push(a);
	}

	PriorityQueue<int> camisetas;
	for (int i = 0; i < M; i++) {
		int a; cin >> a;
		camisetas.push(a);
	}
	int cont = 0;
	while (!jugadores.empty() && !camisetas.empty()) {
		int j = jugadores.top(); int c = camisetas.top();

		if (c < j) { // La camiseta es muy pequeña, no le sirve a nadie
			camisetas.pop();
		}
		else if (j + 1 < c) { // El jugador es muy pequeño, probamos con el siguiente
			cont++;
			jugadores.pop();
		}
		else if (j == c || (j + 1 == c)) { //Puede usar la camiseta
			camisetas.pop();
			jugadores.pop();
		}
	}
	// escribir la solución
	cout << cont + jugadores.size() << "\n";
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
