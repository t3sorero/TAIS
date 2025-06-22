
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>

using namespace std;

#include "GrafoValorado.h" // propios o los de las estructuras de datos de clase
#include "ConjuntosDisjuntos.h"
#include "PriorityQueue.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
class Aeropuerto {
public:

	Aeropuerto(GrafoValorado<int> const& gv, int C) : coste(0), numAeropuertos(0){
		PriorityQueue<Arista<int>> pq(gv.aristas());
		ConjuntosDisjuntos cjtos(gv.V());
		while (!pq.empty()) {
			auto a = pq.top(); pq.pop();
			int v = a.uno(), w = a.otro(v);
			if (!cjtos.unidos(v, w) && a.valor()<C) {
				cjtos.unir(v, w);
				_ARM.push_back(a); coste += a.valor();
				if (_ARM.size() == gv.V() - 1) break;
				
				
			}
		}
		numAeropuertos = cjtos.num_cjtos();
	}

	int costeCarreteras() const {
		return coste;
	}

	int numeroAeropuertos() const {
		return numAeropuertos;
	}

private:
	vector<Arista<int>> _ARM;
	int coste;
	int numAeropuertos;
};

bool resuelveCaso() {
	int V, A, C;
	cin >> V >> A >> C;
	if (!std::cin)  // fin de la entrada
		return false;

	GrafoValorado<int> gv(V);

	for (int i = 0; i < A; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		gv.ponArista({ a - 1,b - 1,c });
	}
	// resolver el caso posiblemente llamando a otras funciones
	Aeropuerto a (gv,C);

	// escribir la solución
	cout << a.costeCarreteras() + C * a.numeroAeropuertos() << " " << a.numeroAeropuertos() << "\n";
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
