
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include<deque>
#include <limits>	

using namespace std;


#include "DigrafoValorado.h"  // propios o los de las estructuras de datos de clase
#include"IndexPQ.h"

using Camino = deque<AristaDirigida<int>>;
/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.
 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class Dijkstra {
public:
	Dijkstra(DigrafoValorado<int> const& g, int origen) :origen(origen), dist(g.V(), INF), ulti(g.V()), pq(g.V()), visit(g.V(),false) {

		dist[origen] = 0;
		pq.push(origen, 0);
		while (!pq.empty()) {
			int v = pq.top().elem; pq.pop();
			visit[v] = true;
			for (auto a : g.ady(v))
				relajar(a);
		}
	}

	int distancia(int v) const {
		return dist[v];
	}

	int hayCamino(int v) const {
		return dist[v] != INF;
	}

	Camino camino(int v) const {
		Camino cam;
		AristaDirigida<int> a;
		for (a = ulti[v]; a.desde() != origen; a = ulti[a.desde()])
			cam.push_front(a);
		cam.push_front(a);
		return cam;
	}

private:
	const int INF = std::numeric_limits<int>::max();
	int origen;
	vector<int> dist;
	vector<AristaDirigida<int>> ulti;
	IndexPQ<int> pq;
	vector<bool> visit;

	void relajar(AristaDirigida<int> a) {
		int v = a.desde(); int w = a.hasta();
		if (dist[w] > dist[v] + a.valor()) {
			dist[w] = dist[v] + a.valor(); ulti[w] = a;
			pq.update(w, dist[w]);
		}
	}

};

bool resuelveCaso() {
	// leer los datos de la entrada
	int V, A;
	cin >> V >> A;
	if (!std::cin)  // fin de la entrada
		return false;
	DigrafoValorado<int> g(V);

	for (int i = 0; i < A; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		g.ponArista({ a - 1,b - 1,c });
		g.ponArista({ b - 1,a - 1,c });
	}
	// resolver el caso posiblemente llamando a otras funciones
	int pedidos; cin >> pedidos;
	for (int i = 0; i < pedidos; i++) {
		int origen, destino;
		cin >> origen >> destino;
		Dijkstra d(g, origen-1);
		if (d.hayCamino(destino - 1)) {
			cout << d.distancia(destino - 1) << ": " << origen;
			for (auto v : d.camino(destino - 1)) {
				cout << " -> " << v.hasta() + 1;
			} 
			cout<< "\n";

		}
		else
			cout << "NO LLEGA\n";
	}
	cout << "---\n";
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
