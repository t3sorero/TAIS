
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include<queue>
#include<deque>
#include<climits>
using namespace std;

using Camino = deque<int>;

#include "Grafo.h";  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class PeajeSombra {
public:
	PeajeSombra(const Grafo& g, int s) : visitado(g.V(), false), anterior(g.V()), distancia(g.V()), s(s) {
		bfs(g);
	}

	bool hayCamino(int v) const {
		return visitado[v];
	}
	int dist(int v) const {
		return distancia[v];
	}

	Camino camino(int v) const {
		if (!hayCamino(v)) throw std::domain_error("No existe camino");
		Camino cam;
		for (int x = v; x != s; x = anterior[x])
			cam.push_front(x);
		cam.push_front(s);
		return cam;
	}
private:
	vector<bool> visitado;
	vector<int> anterior;
	vector<int>distancia;
	int s;

	void bfs(Grafo const& g) {
		queue<int> q;
		distancia[s] = 0; visitado[s] = true;
		q.push(s);
		while (!q.empty()) {
			int v = q.front(); q.pop();
			for (int w : g.ady(v)) {
				if (!visitado[w]) {
					anterior[w] = v; distancia[w] = distancia[v] + 1; visitado[w] = true;
					q.push(w);
				}
			}
		}
	}
};

bool resuelveCaso() {
	int N, C, A, L, T;
	cin >> N >> C >> A >> L >> T;
	if (!std::cin)  // fin de la entrada
		return false;
	Grafo g(N);
	for (int i = 0; i < C; i++) {
		int a, b;
		cin >> a >> b;
		g.ponArista(a - 1, b - 1);
	}
	PeajeSombra alex(g, A-1);
	PeajeSombra lucas(g, L-1);
	PeajeSombra trabajo(g, T-1);

	int minim = INT_MAX;
	for (int i = 0; i < g.V(); i++) {
		int dist = alex.dist(i) + lucas.dist(i) + trabajo.dist(i);
		minim = min(dist, minim);
	}
	cout <<minim << endl;
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
