
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include<queue>
using namespace std;

#include "ConjuntosDisjuntos.h"  // propios o los de las estructuras de datos de clase
#include "Grafo.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class Paintball {

public:
	Paintball(Grafo const& g) : visit(g.V(), false),exito(true),equipos(g.V(), -1)  {


		for (int i = 0; i < g.V(); i++) { //Por si el grafo no es conexo
			if(!visit[i])
				bfs(g,i);
		}
		
	}

	bool hayEquipo() {
		return exito;
	}

private:

	vector<bool> visit;
	vector<int> equipos;
	bool eligeEquipo;

	bool exito;

	void bfs(Grafo const& g, int v) {
		queue<int> cola;
		cola.push(v);
		visit[v] = true;
		equipos[v] = 0;
		while (!cola.empty()) {
			int p = cola.front();
			cola.pop();
			for (int w : g.ady(p)) {
				if (!visit[w]) {
					cola.push(w);
					visit[w] = true;
					equipos[w] = 1 - equipos[p];
				}
				else if(equipos[w] == equipos[p]){
					exito = false;
					break;
				}
			}
		}
	}
};

bool resuelveCaso() {
	
	int V, A;
	cin >> V >> A;

	if (!std::cin)  // fin de la entrada
		return false;

	Grafo g(V);

	for (int i = 0; i < A; i++) {
		int a, b;
		cin >> a >> b;
		g.ponArista(--a, --b);
	}
	Paintball p (g);

	if (p.hayEquipo())
		cout << "SI\n";
	else
		cout << "NO\n";
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
