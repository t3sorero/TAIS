
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include<deque>

using namespace std;

using Camino = deque<int>;

#include "Digrafo.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 El coste es O(n) siendo n el numero de instrucciones

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class CicloDirigido {
public:
	CicloDirigido(Digrafo const& g) : visit(g.V(), false), ant(g.V()),
		apilado(g.V(), false), hayciclo(false) {
		int v = 0;
		dfs(g, v);
	}
	bool hayCiclo() const { return hayciclo; }
	bool ultimoVisitado() const { return visit[visit.size()-1]; }

private:
	vector<bool> visit; // visit[v] = ¿se ha alcanzado a v en el dfs?
	vector<int> ant; // ant[v] = vértice anterior en el camino a v
	vector<bool> apilado; // apilado[v] = ¿está el vértice v en la pila?
	Camino _ciclo; // ciclo dirigido (vacío si no existe)
	bool hayciclo;

	void dfs(Digrafo const& g, int v) {
		apilado[v] = true;
		visit[v] = true;
		for (int w : g.ady(v)) {

			if (!visit[w]) { // encontrado un nuevo vértice, seguimos
				ant[w] = v; dfs(g, w);
			}
			else if (apilado[w]) { // hemos detectado un ciclo
				// se recupera retrocediendo
				hayciclo = true;
				for (int x = v; x != w; x = ant[x])
					_ciclo.push_front(x);
				_ciclo.push_front(w); _ciclo.push_front(v);
			}
		}
		apilado[v] = false;
	}
};

bool resuelveCaso() {
	int V;
	cin >> V;

	if (!std::cin)  // fin de la entrada
		return false;

	Digrafo g(V+1);
	vector<bool> visitados;

	for (int i = 1; i < V; i++) {
		char c; cin >> c;
		int n;
		switch (c) {
		case 'A': g.ponArista(i - 1, i);
			break;
		case 'J': cin >> n; g.ponArista(i - 1, n-1);
			break;
		case 'C': cin >> n; g.ponArista(i - 1, i); g.ponArista(i - 1, n-1);
			break;
		}
	}
	char c; cin >> c;
	int n;
	switch (c) {
	case 'J': cin >> n; g.ponArista(V-1, n-1);
		break;
	case 'C': cin >> n; g.ponArista(V-1, n-1); g.ponArista(V-1, V);
		break;
	default: g.ponArista(V-1, V);
		break;
	}
	CicloDirigido d(g);
	if (!d.hayCiclo()) cout << "SIEMPRE\n";
	else {
		if (d.ultimoVisitado()) cout << "A VECES\n";
		else cout << "NUNCA\n";
	}

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
