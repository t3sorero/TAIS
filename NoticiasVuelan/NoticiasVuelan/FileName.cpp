
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>

using namespace std;

#include "Grafo.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class ComponenteConexa {
public: 
	ComponenteConexa(Grafo const& g) : visit(g.V(), false), sol(g.V(),1), ids(g.V()), tamGrupo(0) {

		for (int i = 0; i < g.V(); i++) {
			if (!visit[i]) {
				dfs(g, i, tamGrupo);
				tamGrupo++;
			}
		}

	}

	int tamanyoComponente(int i) {
		return sol[ids[i]];
	}

private:
	vector<bool> visit;

	vector<int> sol;

	vector<int> ids;

	int tamGrupo;
	
	void dfs(Grafo const& g, int v, int idGrupo) {
		visit[v] = true;
		ids[v] = idGrupo;
		sol[idGrupo]++;

		for (int w : g.ady(v)) {
			if (!visit[w])
				dfs(g, w, idGrupo);
		}
	}
};

bool resuelveCaso() {
	int V, G;
	cin >> V >> G;

	if (!std::cin)  // fin de la entrada
		return false;

	Grafo g(V);
	for (int i = 0; i < G; i++) {
		int a; cin >> a;
		if (a > 1) {
			int b; cin >> b;
			for (int j = 0; j < a - 1; j++) {
				int c; cin >> c;
				g.ponArista(b - 1, c - 1);
				b = c;
			}
		}
		else if (a == 1) cin >> a;
		
	}
	// resolver el caso posiblemente llamando a otras funciones
	ComponenteConexa c(g);

	for (int i = 0; i < g.V(); i++) {
		cout << c.tamanyoComponente(i) - 1 << " ";
	}
	cout << endl;
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
