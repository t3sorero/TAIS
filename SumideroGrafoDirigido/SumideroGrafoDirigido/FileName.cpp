
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>

using namespace std;

#include "Digrafo.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class Sumidero {
public: 
	Sumidero(Digrafo const& g) : sumidero(0), haySumidero(false) {
		auto gInverso = g.inverso();

		for (int i = 0; i < g.V(); i++) {
			if (gInverso.ady(i).size() == g.V() - 1 && g.ady(i).size() == 0) {
				haySumidero = true;
				sumidero = i;
				break;
			}
		}
	}

	bool tieneSumidero() const {
		return haySumidero;
	}

	int elSumidero() const {
		return sumidero;
	}
private:
	bool haySumidero;

	int sumidero;
};

bool resuelveCaso() {
	// leer los datos de la entrada
	int V, A;
	cin >> V >> A;

	if (!std::cin)  // fin de la entrada
		return false;
	Digrafo g(V);

	for (int i = 0; i < A; i++) {
		int a, b; cin >> a >> b;
		g.ponArista(a, b);
	}
	// resolver el caso posiblemente llamando a otras funciones
	Sumidero s(g); 
	// escribir la solución
	if (s.tieneSumidero()) {
		cout << "SI " << s.elSumidero() << "\n";
	}
	else
		cout << "NO\n";
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
