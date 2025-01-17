
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include<climits>
#include<queue>

using namespace std;

#include "Grafo.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 El problema se resuelve utilizando una estrategia basada en grafos, modelando los personajes y sus 
 relaciones como un grafo no dirigido. Cada nodo representa un personaje, y cada arista representa una
 relación de amistad entre dos personajes. El objetivo es encontrar el costo mínimo necesario para 
 difundir el rumor a todos los personajes del grafo.

La idea principal es que cada componente conexa del grafo puede ser alcanzada sobornando al personaje
más barato de esa componente. Por lo tanto, el problema se reduce a calcular el costo mínimo para 
cubrir todas las componentes conexas del grafo

Realizamos una busqueda en anchura (BFS) para encontrar todas las componentes conexas del grafo, y calculamos 
el coste minimo de difundir el rumor.

Busqueda de la componente conexa: Cada nodo y aristase recorre una unica vez O(V+A) siendo V los personajes y A las aristas

El coste del problema esta en O(V+A) y se utiliza un espacio adicional
El coste en espacio esta en O(V+A) en crear el grafo y O(V) en el vector de personajes y visitados

 
 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

int difundiendoRumor(Grafo const& g, vector<int> const& personajes,vector<bool> visitados) {
	int coste = 0;
	for (int i = 0; i < g.V(); i++) {
		if (!visitados[i]) {
			int minCoste = personajes[i];
			queue<int>cola;
			cola.push(i);
			while (!cola.empty()) {
				int v = cola.front();
				cola.pop();
				visitados[v] = true;
				minCoste = min(minCoste, personajes[v]);
				auto listAdy = g.ady(v);
				for (int& j : listAdy) {
					if(!visitados[j])
						cola.push(j);
				}
			}
			coste += minCoste;
		}
	}
	return coste;
}

bool resuelveCaso() {
	int N, M;
	cin >> N >> M;
	if (!std::cin)  // fin de la entrada
		return false;
	vector<int> personajes(N);
	for (int i = 0; i < N; i++) {
		cin >> personajes[i];
	}
	vector<bool> visitados(N, false);

	Grafo amigos(N);
	for (int i = 0; i < M; i++) {
		int a, b;
		cin >> a >> b;
		amigos.ponArista(--a, --b);
	}

	int sol = difundiendoRumor(amigos, personajes, visitados);
	cout << sol << "\n";
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
