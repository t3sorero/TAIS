
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

#include "GrafoValorado.h"  // propios o los de las estructuras de datos de clase
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

class MejorCamino {
public:
	MejorCamino(GrafoValorado<int> const& gv, int ori) : origen(ori), dist(gv.V(),INF), ulti(gv.V()), pq(gv.V()), 
		callesDijkstra(gv.V(),INF){
		dist[ori] = 0;
		pq.push(ori, 0);
		callesDijkstra[ori] = 0;
		visit[ori] = true;
		while (!pq.empty()) {
			int v = pq.top().elem;
			pq.pop();
			for (auto& a : gv.ady(v)) {
				relajar(a);
				if (!visit[a.otro(v)]) {
					callesDijkstra[a.otro(v)] = callesDijkstra[v] + 1; visit[a.otro(v)] = true;
				}
			}
		}
	}
	//bool menorNCalles(int v) const { return < callesDijkstra[v]; }


	bool hayCamino(int v) const { return dist[v] != INF; }

	int distancia(int v) const { return dist[v]; }
private:
	const int INF = numeric_limits<int>::max();
	int origen;
	vector<int> dist;
	vector<Arista<int>>ulti;
	IndexPQ<int> pq;
	vector<int> callesDijkstra;
	vector<bool> visit;
	
	void relajar(Arista<int>const& a) {
		int v = a.uno(), w = a.otro(v);
		if (dist[w] > dist[v] + a.valor()) {
			dist[w] = dist[v] + a.valor();
			ulti[w] = a;
			pq.update(w, dist[w]);
		}
	}
};

bool resuelveCaso() {
	int V; cin >> V;
	if (!std::cin)  // fin de la entrada
		return false;

	int A; cin >> A;

	GrafoValorado<int> gv(V);
	for (int i = 0; i < A; i++) {
		int a, b, v;
		cin >> a >> b >> v;
		gv.ponArista({ a - 1,b - 1,v });
	}
	int c; cin >> c;
	for (int i = 0; i < c; i++) {
		int origen, fin;
		cin >> origen >> fin;
		MejorCamino mc(gv, origen);
		if (mc.hayCamino(fin)) {
			cout << mc.distancia(fin);
			if (!mc.menorNCalles(fin)) cout << " SI\n";
			else cout << " NO\n";
		}
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
