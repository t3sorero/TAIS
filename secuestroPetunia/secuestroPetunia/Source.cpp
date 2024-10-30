
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include<limits>

using namespace std;

#include "GrafoValorado.h"// propios o los de las estructuras de datos de clase
#include "IndexPQ.h"
/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class SecuestroPetunia {
public:
	SecuestroPetunia(GrafoValorado<int>gv, int D, vector<int> veces) : dist(gv.V(), INF), ulti(gv.V()), pq(gv.V()), D(D), pueblos(0) {

		for (int i = 0; i < veces.size(); i++) {
			dist[veces[i]] = 0;
			pq.push(veces[i], 0);
		}
		while (!pq.empty()) {
			int v = pq.top().elem;
			pq.pop();
			if (dist[v] <= D) {
				for (auto& i : gv.ady(v)) {
					relajar(i);
				}
				pueblos++;
			}
		}
	}

	int sizePueblos() const { return pueblos; }

	bool hayCamino(int v) const { return dist[v] != INF; }

	int distancia(int v) const { return dist[v]; }
private:
	const int INF = numeric_limits<int>::max();
	int pueblos;
	vector<int> dist;
	vector<Arista<int>> ulti;
	IndexPQ<int, less<int>> pq;
	int D;

	void relajar(Arista<int> a) {
		int v = a.uno(), w = a.otro(v);
		if (dist[w] > dist[v] + a.valor()) {
			dist[w] = dist[v] + a.valor();
			ulti[w] = a;
			pq.update(w, dist[w]);
		}
	}
};

bool resuelveCaso() {
	int D, V, A;
	cin >> D >> V >> A;

	if (!std::cin)  // fin de la entrada
		return false;

	GrafoValorado<int> gv(V);

	for (int i = 0; i < A; i++) {
		int a, b, v;
		cin >> a >> b >> v;
		gv.ponArista({ a - 1,b - 1,v });
	}
	int p; cin >> p;
	vector<int> veces;
	for (int i = 0; i < p; i++) {
		int a; cin >> a;
		veces.push_back(a-1);
	}
	SecuestroPetunia sp(gv,D, veces);
	cout << sp.sizePueblos();

	// resolver el caso posiblemente llamando a otras funciones

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
