
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include<unordered_map>
#include<queue>


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

class NumeroBacon {
public:
	NumeroBacon(Grafo const& g): visit(g.V(), false), ant(g.V()), dist(g.V()), s(0) {

		bfs(g);
	}

	bool hayCamino (int v) const{
		return visit[v];
	}

	int distacia(int v) const {
		return dist[v];
	}

private:

	
	vector<bool> visit;
	vector<int> ant;
	vector<int> dist;
	int s; // kevin bacon

	void bfs(Grafo const& g) {
		queue<int> q;
		dist[s] = 0; visit[s] = true;
		q.push(s);
		while (!q.empty()) {
			int v = q.front(); q.pop();
			for (int w : g.ady(v)) {
				if (!visit[w]) {
					ant[w] = v; dist[w] = dist[v] + 1; visit[w] = true;
					q.push(w);
				}
			}
		}
	}
};


bool resuelveCaso() {
	int G; cin >> G;

	if (!std::cin)  // fin de la entrada
		return false;

	vector<vector<string>> actores; 
	unordered_map<string, int> mapeoActorIndice;
	mapeoActorIndice.insert({ "KevinBacon", 0 });
	int index = 0;
	for (int i = 0; i < G; i++) { //por cada peli
		string name; cin >> name;
		int V; cin >> V;
		vector<string> pelisActor;
		for (int j = 0; j < V; j++) {
			string actor; cin >> actor;
			if (mapeoActorIndice.find(actor) == mapeoActorIndice.end()) { // no esta el actor todavia
				mapeoActorIndice.insert({ actor,++index });
			}
			pelisActor.push_back(actor);
		}
		actores.push_back(pelisActor);	
	}

	//Ahora creamos el grafo con todos los actores
	Grafo g(mapeoActorIndice.size());

	for (auto peli : actores) {

		vector<int> indices;
		for (auto actor : peli) {
			indices.push_back(mapeoActorIndice[actor]);
		}

		// Conectar cada actor con todos los demás de la misma película
		for (int i = 0; i < indices.size(); i++) {
			for (int j = i + 1; j < indices.size(); j++) {
				g.ponArista(indices[i], indices[j]);
			}
		}

	}
	// resolver el caso posiblemente llamando a otras funciones
	NumeroBacon nm(g);
	// escribir la solución
	int A; cin >> A;

	for (int i = 0; i < A; i++) {
		string name; cin >> name;
		if (nm.hayCamino(mapeoActorIndice[name])) {
			cout << name << " " << nm.distacia(mapeoActorIndice[name]);
		}
		else {
			cout << name << " INF";
		}
		cout << endl;
	}
	cout << "---\n";

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
