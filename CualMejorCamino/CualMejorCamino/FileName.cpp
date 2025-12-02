
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include<algorithm>
#include<queue>
#include<limits>

using namespace std;
#include"DigrafoValorado.h"
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

class MejorCamino {
public:

	MejorCamino(DigrafoValorado<int> const& g, int origen) : origen(origen), distDj(g.V(),INF), distBfs(g.V(),INF),
	antBfs(g.V()), ultiDj(g.V()), pq(g.V()), pqBfs(g.V()){
		dijkstra(g);
		bfs(g);
		
	}

	bool hayCamino(int v) const {
		return distDj[v] != INF;
	}
	int distancia(int v) const {
		return distDj[v];
	}
	
	bool esMejorCamino(int v) const {
		int contBfs = 0;
		for (auto a = antBfs[v]; a.desde() != origen; a = antBfs[a.desde()]) {
			contBfs++;
		}
		int contDjk = 0;
		for (auto a = ultiDj[v]; a.desde() != origen; a = ultiDj[a.desde()]) {
			contDjk++;
		}
		return contBfs == contDjk;
	}


	void dijkstra(DigrafoValorado<int> const& g) {
		distDj[origen] = 0;
		pq.push(origen, 0);
		while (!pq.empty()) {
			int v = pq.top().elem; pq.pop();
			for (auto a : g.ady(v))
				relajar(a);
		}
	}

	void bfs(DigrafoValorado<int> const& g) {
		distBfs[origen] = 0;
		pqBfs.push(origen, 0);
		while (!pqBfs.empty()) {
			int v = pqBfs.top().elem; pqBfs.pop();
			for (auto a : g.ady(v))
				relajarBfs(a);
		}
	}
private:

	const int INF = std::numeric_limits<int>::max();
	int origen;
	vector<int> distDj;
	vector<AristaDirigida<int>> ultiDj;
	IndexPQ<int> pq;

	IndexPQ<int> pqBfs;
	vector<int> distBfs;
	vector<AristaDirigida<int>> antBfs;

	void relajar(AristaDirigida<int> a) {
		int v = a.desde(), w = a.hasta();
		if (distDj[w] > distDj[v] + a.valor()) {
			distDj[w] = distDj[v] + a.valor(); ultiDj[w] = a;
			pq.update(w, distDj[w]);
		}
	}

	void relajarBfs(AristaDirigida<int>a) {
		int v = a.desde(), w = a.hasta();
		if (distBfs[w] > distBfs[v] + 1) {
			distBfs[w] = distBfs[v] + 1; antBfs[w] = a;
			pqBfs.update(w, distBfs[w]);
		}
	}
};
bool resuelveCaso() {
	// leer los datos de la entrada
	int V, A; cin >> V;

	if (!std::cin)  // fin de la entrada
		return false;
	cin >> A;

	DigrafoValorado<int>g(V);

	for (int i = 0; i < A; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		g.ponArista({ a - 1,b - 1,c });
		g.ponArista({ b - 1,a - 1,c });
	}
	int k, origen, destino;
	cin >> k;
	for (int i = 0; i < k; i++) {
		cin >> origen >> destino;
		MejorCamino mj(g, origen - 1);

		if (mj.hayCamino(destino - 1)) {
			cout << mj.distancia(destino - 1);
			if (mj.esMejorCamino(destino - 1))
				cout << " SI\n";
			else cout << " NO\n";
		}
		else cout << "SIN CAMINO\n";
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
