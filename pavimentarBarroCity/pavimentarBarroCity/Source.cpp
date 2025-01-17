
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>


using namespace std;

#include "ConjuntosDisjuntos.h"// propios o los de las estructuras de datos de clase
#include"GrafoValorado.h"
#include"PriorityQueue.h" 
/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class Pavimentar {
public:
	Pavimentar(GrafoValorado<int> const& gv) : cj(gv.V()),pq(gv.aristas()), aristas(0), coste(0){
		while (!pq.empty()) {
			auto a = pq.top();
			pq.pop();
			int v = a.uno();
			int w = a.otro(v);
			if (!cj.unidos(v,w)) {
				cj.unir(v, w);
				coste += a.valor();
				aristas++;
				if (aristas == gv.V() - 1)  break;
			}
		}
	}

	bool hayCaminos() const {
		return cj.num_cjtos() == 1;
	}
	int costeTotal() const {
		return coste;
	}
private:
	ConjuntosDisjuntos cj;
	PriorityQueue<Arista<int>> pq;
	int aristas;
	int coste;
};

bool resuelveCaso() {
	int V;
	cin >> V;

	if (!std::cin)  // fin de la entrada
		return false;
	int A; cin >> A;

	GrafoValorado<int> gv(V);

	for (int i = 0; i < A; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		gv.ponArista({ --a,--b,c });
	}
	Pavimentar p(gv);
	if (p.hayCaminos()) {
		cout << p.costeTotal() << "\n";
	}
	else {
		cout << "Imposible\n";
	}
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
