
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include<queue>

using namespace std;


/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */

const int MAX = 10000;
const int INF = 100000000;
const int CASOS = 3;

 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

int adyacente(int v, int i) {
	switch (i) {
	case 0: return (v + 1) % MAX;
	case 1: return (v * 2) % MAX;
	case 2: return (v / 3);
	}
}

int bfs(int origen, int destino) {
	if (origen == destino) return 0;
	vector<int> distancia(MAX, INF);
	distancia[origen] = 0;
	queue<int> cola;
	cola.push(origen);
	while (!cola.empty()) {
		int v = cola.front();
		cola.pop();
		for (int i = 0; i < CASOS; i++) {
			int w = adyacente(v, i);
			if (distancia[w] == INF) {
				distancia[w] = distancia[v] + 1;
				if (w == destino) return distancia[w];
				else cola.push(w);
			}
		}
	}
}
bool resuelveCaso() {
	int origen, destino;
	cin >> origen >> destino;
	if (!std::cin)  // fin de la entrada
		return false;

	cout << bfs(origen, destino) << endl;

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
