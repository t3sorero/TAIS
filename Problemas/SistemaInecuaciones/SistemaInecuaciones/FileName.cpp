
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include<deque>

using namespace std;
using Camino = std::deque<int>; // 

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

class CicloDirigido {
	// Clase que detecta ciclos en un grafo dirigido.
	// Si hay ciclo, almacena el ciclo en _ciclo.
	// El coste es O(V + E) donde V es el número de vértices y E el número de aristas.
public:
	CicloDirigido(Digrafo const& g) : visit(g.V(), false), ant(g.V()),
	apilado(g.V(), false), hayciclo(false) {
	for (int v = 0; v < g.V(); ++v)
		if (!visit[v])
			dfs(g, v);
}
	  bool hayCiclo() const { return hayciclo; }
	  Camino const& ciclo() const { return _ciclo; }
private:
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
			if (hayciclo) // si hemos encontrado un ciclo terminamos
				return;
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

class OrdenTopologico {
	// g es DAG
public:
	OrdenTopologico(Digrafo const& g) : visit(g.V(), false) {
		for (int v = 0; v < g.V(); ++v)
			if (!visit[v])
				dfs(g, v);
	}
	// devuelve la ordenación topológica
	deque<int> const& orden() const {
		return _orden;
	}
private:
	std::vector<bool> visit;
	std::deque<int> _orden; // ordenación topológica
	void dfs(Digrafo const& g, int v) {
		visit[v] = true;
		for (int w : g.ady(v))
			if (!visit[w])
				dfs(g, w);
		_orden.push_front(v);
	}
};

bool resuelveCaso() {
	// leer los datos de la entrada
	int V, E;
	cin >> V >> E;

	if (!std::cin)  // fin de la entrada
		return false;

	Digrafo g(V);
	for (size_t i = 0; i < E; i++)
	{
		int a, b; cin >> a >> b;
		g.ponArista(--a, --b);
	}

	// resolver el caso posiblemente llamando a otras funciones
	CicloDirigido c(g);

	// escribir la solución
	if (c.hayCiclo()) {
		cout << "NO\n";
	}
	else
	{
		vector<int> valores (V);
		int contador = 10;
		auto orden = OrdenTopologico(g).orden();
		for (auto k: orden) {

			valores[k] = contador++;
		}

		cout << "SI";
		for (int valor :valores)
			cout << ' ' << valor;
		cout << '\n';
	}


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
