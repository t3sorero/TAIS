
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <deque>

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

class OrdenandoTareas {
public:

	OrdenandoTareas(Digrafo const& g) : visit(g.V(), false), ant(g.V()), apilado(g.V(), false), hayCiclo(false) {
		for (int i = 0; i < g.V(); i++) {
			if(!visit[i])
				dfs(g, i);
		}
	}

	bool tieneOrden() const {
		return !hayCiclo;
	}

	deque<int> ordenacionTareas() const {
		return orden;
	}

private:
	vector<bool> visit;
	vector<int> ant;
	vector<bool> apilado;
	bool hayCiclo;

	deque<int> orden;

	void dfs(Digrafo const& g, int v) {
		apilado[v] = true;
		visit[v] = true;
		for (int w : g.ady(v)) {
			if (hayCiclo) 
				return;
			if (!visit[w]) { 
				ant[w] = v; dfs(g, w);
			}
			else if (apilado[w]) {
				hayCiclo = true;
			}
		}
		orden.push_front(v);
		apilado[v] = false;
	}
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
		g.ponArista(a - 1, b - 1);
	}

	// resolver el caso posiblemente llamando a otras funciones
	OrdenandoTareas ot(g);

	if (ot.tieneOrden()) {
		for (int v : ot.ordenacionTareas()) {
			cout << v + 1 << " ";
		}
		cout << "\n";
	}
	else
		cout << "Imposible\n";
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
