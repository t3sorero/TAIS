
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include<limits>
#include<algorithm>

using namespace std;

#include "GrafoValorado.h"  // propios o los de las estructuras de datos de clase
#include "IndexPQ.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */

class NecesitamosAgua {
public:
	NecesitamosAgua(GrafoValorado<long long int> const& gv, int origen) : dist(gv.V(), INF), pq(gv.V()) {
		dist[origen] = 0;
		pq.push(origen, 0);
		while (!pq.empty()) {
			int v = pq.top().elem; pq.pop();
			for (auto &a : gv.ady(v))
				relajar(a,v);
		}
	}

	bool hayCamino(int v) const { return dist[v] != INF; }
	int distancia(long long int v) const { return dist[v]; }

private:
	const long long INF = numeric_limits<long long int>::max();
	vector<long long int> dist;
	IndexPQ<long long int> pq;
	

	void relajar(Arista<long long int> a, int ve) {
		int v = a.uno();
		int w = a.otro(v);
		if (ve == w) swap(v, w);
		if (dist[w] > dist[v] + a.valor()) {
			dist[w] = dist[v] + a.valor();
			pq.update(w, dist[w]);
		}
	}
};

 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
bool ordenaSort(pair<int, long long int> const& a, pair<int, long long int> const& b) {
	return a.second > b.second;
}
bool resuelveCaso() {
	long long int V;long long int A;
	cin >> V >> A;

	if (!std::cin)  // fin de la entrada
		return false;

	GrafoValorado<long long int> gv(V);

	for (int i = 0; i < A; i++) {
		int a, b; long long int c;
		cin >> a >> b >> c;
		Arista  <long long int> arist(a - 1, b - 1,c);
		gv.ponArista(arist);
	}

	NecesitamosAgua norte (gv, 0);
	NecesitamosAgua sur(gv, V - 1);
	vector<pair<int, long long int>> diff;
	
	for (int i = 1; i < V-1; i++) {
		diff.push_back({ i, norte.distancia(i) - sur.distancia(i) });
	}

	sort(diff.begin(), diff.end(), ordenaSort);

	long long int costo_total = 0;
	int pueblos_por_planta = (V - 2) / 2;

	// Asignar primeros pueblos al sur (tienen diferencia más negativa)
	for (int i = 0; i < pueblos_por_planta; i++) {
		int pueblo = diff[i].first;
		costo_total += 2 * sur.distancia(pueblo);  // Ida y vuelta
	}

	// Asignar últimos pueblos al norte
	for (int i = pueblos_por_planta; i < diff.size(); i++) {
		int pueblo = diff[i].first;
		costo_total += 2 * norte.distancia(pueblo);  // Ida y vuelta
	}

	cout << costo_total << "\n";
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
