
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include<climits>
#include<numeric>
#include<deque>
using namespace std;

#include "GrafoValorado.h"  // propios o los de las estructuras de datos de clase
#include"PriorityQueue.h"
#include"ConjuntosDisjuntos.h"


/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */

class MinasEmperadorTrajano  {
public:
	MinasEmperadorTrajano(GrafoValorado<int> const& gv, int origen, int tesoro) : pq(gv.aristas()), cj(gv.V()), maxim(0) {

		while (!pq.empty()) {
			auto a = pq.top();
			pq.pop();
			int v = a.uno();
			int w = a.otro(v);
			if (!cj.unidos(v, w)) {
				cj.unir(v, w);
				_ARM.push_back(a);
				if (cj.unidos(origen, tesoro)) {
					maxim = a.valor();
					break;
				}
			}
		}
	}

	
	int maxSinAire(int origen, int tesoro) const {
		return maxim;
	}

	bool hayCamino(int origen, int tesoro) const {
		return cj.unidos(origen, tesoro);
	}

	

private:
	PriorityQueue<Arista<int>> pq;
	vector<Arista<int>> _ARM;
	ConjuntosDisjuntos cj;
	int maxim;
};

bool resuelveCaso() {
	int V, A;
	cin >> V >> A;

	if (!std::cin)  // fin de la entrada
		return false;

	GrafoValorado<int> gv(V);

	for (int i = 0; i < A; i++) {
		int ini, fin, t;
		cin >> ini >> fin >> t;
		gv.ponArista({ --ini,--fin,t });
	}

	int origen, tesoro;
	cin >> origen >> tesoro;
	--origen, --tesoro;

	MinasEmperadorTrajano mapa (gv, origen,tesoro);

	if (!mapa.hayCamino(origen,tesoro))
			cout << "IMPOSIBLE\n";
	else 
		cout << mapa.maxSinAire(origen,tesoro) << "\n";
	

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
