
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include<queue>
#include<limits>
using namespace std;

#include "DigrafoValorado.h"  // propios o los de las estructuras de datos de clase
#include"IndexPQ.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class NavegandoSinTeclado {
public:
	NavegandoSinTeclado(DigrafoValorado<int>const& dg, int orig) :origen(orig), dist(dg.V(), INF), ulti(dg.V()), pq(dg.V()) {
		dist[origen] = 0;
		pq.push(origen, 0);
		while (!pq.empty()) {
			int v = pq.top().elem;
			pq.pop();
			for (auto& i : dg.ady(v)) {
				relajar(i);
			}
		}

	}

	bool hayCamino(int v) const { return dist[v] != INF; }

	int distancia(int v) const { return dist[v]; }
private:
	const int INF = numeric_limits<int>::max();
	int origen;
	vector<int> dist;
	vector<AristaDirigida<int>> ulti;
	IndexPQ<int, less<int>> pq;

	void relajar(AristaDirigida<int> a) {
		int v = a.desde(), w = a.hasta();
		if (dist[w] > dist[v] + a.valor()) {
			dist[w] = dist[v] + a.valor();
			ulti[w] = a;
			pq.update(w, dist[w]);
		}
	}
};

bool resuelveCaso() {
	int V;
	cin >> V;
	if (V==0)
		return false;
	vector<int> v;
	for (int i = 0; i < V; i++) {
		int a; cin >> a;
		v.push_back(a);
	}

	DigrafoValorado<int> dg(V);

	int A; cin >> A;
	for (int i = 0; i < A; i++) {
		int a, b, val;
		cin >> a >> b >> val;
		dg.ponArista({ a - 1,b - 1,val + v[a - 1] });
	}

	NavegandoSinTeclado nst(dg, 0);
	if (nst.hayCamino(V - 1)) cout << nst.distancia(V - 1) + v[V - 1] << "\n";
	else cout << "IMPOSIBLE\n";

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
