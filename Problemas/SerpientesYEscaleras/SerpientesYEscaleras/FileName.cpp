
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
using namespace std;

#include "Digrafo.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
class Juego {
public: 
	Juego(Digrafo const& g, int numVertices) : visit(g.V(), false), ant(g.V()), dist(g.V()), s(0), fin(numVertices-1) {
		bfs(g);
	}

	int distancia(int v) const {
		return dist[v];
	}

private:
	vector<bool> visit;
	vector<int> ant;
	vector<int> dist;
	int s, fin;

	void bfs(Digrafo const& g) {
		queue<int> q;
		dist[s] = 0; visit[s] = true;
		q.push(s);
		while (!q.empty()) {
			int v = q.front(); q.pop();
			if (v == fin) break;
			for (int w : g.ady(v)) {
				if (!visit[w]) {
					ant[w] = v; dist[w] = dist[v] + 1; visit[w] = true;
					q.push(w);
				}
			}
		}
	}
};

bool resuelveCaso() {
	// leer los datos de la entrada
	int N, K, S, E;
	cin >> N >> K >> S >> E;
	if (N == 0 && K == 0 && S == 0 && E ==0)
		return false;

	Digrafo tablero(N * N);
	unordered_map<int, int> sye;
	for (int i = 0; i < S + E; i++) {
		int a, b; cin >> a >> b;
		sye.insert({ a - 1,b - 1 });
	}

	for (int i = 0; i < N * N; i++) {
		for (int j = 1; j <= K; j++) {
			if (sye.count(i + j) > 0) {
				tablero.ponArista(i, sye.at(i + j));
			}
			else
				if (i + j < N * N)
					tablero.ponArista(i, i + j);
		}
	}
	// resolver el caso posiblemente llamando a otras funciones
	Juego j(tablero, N*N);
	// escribir la solución
	cout << j.distancia(N*N - 1) << "\n";
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
