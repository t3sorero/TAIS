
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#include "GrafoValorado.h"  // propios o los de las estructuras de datos de clase
#include"PriorityQueue.h"
#include"ConjuntosDisjuntos.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class ArchipielagoEnBici {
public:

	ArchipielagoEnBici(GrafoValorado<int>const& g) :coste(0), tam(g.V()) {
		PriorityQueue<Arista<int>> queue(g.aristas());
		ConjuntosDisjuntos cj(g.V());
		while (!queue.empty()) {
			auto a = queue.top();
			queue.pop();
			int v = a.uno();
			int w = a.otro(v);
			if (!cj.unidos(v, w)) {
				cj.unir(v, w);
				arm.push_back(a);
				coste += a.valor();
				if (arm.size() == g.V() - 1) break;
			}
		}
	}

	int costeTotal()const {
		return coste;
	}

	bool esARM()const {
		return (arm.size() == tam - 1);
	}
	

private:
	int coste;
	vector<Arista<int>> arm;
	int tam;
};

bool resuelveCaso() {
	int V, A;
	cin >> V >> A;

	if (!std::cin)  // fin de la entrada
		return false;
	GrafoValorado<int> g(V);
	for (int i = 0; i < A; i++) {
		int a, b, tam;
		cin >> a >> b >> tam;
		Arista<int> arist(a-1, b-1, tam);
		g.ponArista(arist);
	}

	ArchipielagoEnBici bici(g);
	if (bici.esARM()) cout << bici.costeTotal() << "\n";
	else cout << "No hay puentes suficientes\n";

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
