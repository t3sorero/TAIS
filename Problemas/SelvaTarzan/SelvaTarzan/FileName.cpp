
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>

using namespace std;

#include "GrafoValorado.h"  // propios o los de las estructuras de datos de clase
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

class Tarzan {
public:
	Tarzan(GrafoValorado<int> const& g) : esARM(true), cuerdaMasLarga(0) {
		PriorityQueue<Arista<int>> pq(g.aristas());
		ConjuntosDisjuntos cjtos(g.V());
		while (!pq.empty()) {
			auto a = pq.top(); pq.pop();
			int v = a.uno(), w = a.otro(v);
			if (!cjtos.unidos(v, w)) {
				cjtos.unir(v, w);
				_ARM.push_back(a); cuerdaMasLarga = max(a.valor(), cuerdaMasLarga);
				if (_ARM.size() == g.V() - 1) { 
					break; 
				}
			}
		}
		if (cjtos.num_cjtos() > 1) esARM = false;
	}

	bool hayARM() const {
		return esARM;
	}

	int longitudCuerda() const {
		return cuerdaMasLarga;
	}

private:
	bool esARM;
	int cuerdaMasLarga;
	vector<Arista<int>> _ARM;
};

bool resuelveCaso() {
	// leer los datos de la entrada
	int V, A; cin >> V >> A;

	if (!std::cin)  // fin de la entrada
		return false;

	GrafoValorado<int> g(V);

	for (int i = 0; i < A; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		g.ponArista({ a - 1,b - 1,c });
	}

	// resolver el caso posiblemente llamando a otras funciones
	Tarzan t(g);
	if (t.hayARM()) cout << t.longitudCuerda() << "\n";
	else cout << "Imposible\n";
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
