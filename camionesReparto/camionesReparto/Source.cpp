
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

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class CamionesReparto {
public:

	CamionesReparto(const GrafoValorado<int>& g, const int& ini, const int & fin, const int& tam) : visit(g.V(), false), tam(tam) {
		dfs(g, ini,fin);
	}

	bool hayCamino(int v) {
		return visit[v];
	}
private:
	vector<bool>visit;
	int tam;

	void dfs(GrafoValorado<int> const& g, int v, const int& fin) {
		visit[v] = true;
		if (visit[fin] == true) return;
		else {
			for (auto& w : g.ady(v)) {
				if (w.valor() >= tam) {
					int v = w.uno();
					if (!visit[w.otro(v)]) { //w.otro(w.uno())
						 dfs(g, w.otro(v), fin);
					}
				}
			}
		}
	}
};
bool reparto(const GrafoValorado<int>& g, const int& ini, const int& fin, const int& tam) {
	CamionesReparto c(g, ini, fin, tam);
	if (c.hayCamino(fin)) return true;
	else return false;
}


bool resuelveCaso() {
	int V, A;
	cin >> V >> A;
	if (!std::cin)  // fin de la entrada
		return false;


	GrafoValorado<int> g(V);

	for (int i = 0; i < A; i++) {
		int a, b, tam;
		cin >> a >> b >> tam;
		Arista<int> arist(a-1,b-1,tam);
		g.ponArista(arist);
	}

	int c;
	cin >> c;
	for (int i = 0; i < c; i++) {
		int ini, fin, tam;
		cin >> ini >> fin >> tam;
		if (reparto(g, ini - 1, fin - 1, tam)) cout << "SI\n";
		else cout << "NO\n";
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
