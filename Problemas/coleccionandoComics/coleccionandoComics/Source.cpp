
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include<climits>

#include"PriorityQueue.h"

using namespace std;


/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct mejorComic {
	int pos;
	int pila;
};

struct Comic {
	int pila;
	int valor;
};

bool operator < (Comic c1, Comic c2) {
	return c1.valor < c2.valor;
}

bool resuelveCaso() {
	int P;
	cin >> P;

	if (!std::cin)  // fin de la entrada
		return false;
	
	vector<vector<int>> listaPilas(P);
	int minim = INT_MAX;
	mejorComic mc;
	for (int i = 0; i < P; i++) {
		int l; cin >> l;
		vector<int> pila;
		for (int j = 0; j < l; j++) {
			int d; cin >> d;
			pila.push_back(d);
			if (minim > d) {
				minim = d;
				mc.pila = i;
				mc.pos = j;
			}
		}
		listaPilas[i] = pila;
	}

	PriorityQueue<Comic> cola;
	int j = 0;
	while (j < P) {
		if (j != mc.pila) {
			int ulti = listaPilas[j].size() - 1;
			cola.push({ j, listaPilas[j][ulti]});
			listaPilas[j].pop_back();
		}
		++j;
	}

	int posicion = 1;

	for (int i = listaPilas[mc.pila].size() - 1; i > mc.pos; i--) {

		int c = listaPilas[mc.pila][i];
		while (!cola.empty() && cola.top().valor < c) {
			auto a = cola.top();
			cola.pop();
			posicion++;
			int ulti = listaPilas[a.pila].size() - 1;
			if (ulti > 0) {
				cola.push({a.pila, listaPilas[a.pila][ulti] });
				listaPilas[a.pila].pop_back();

			}
		}
		posicion++;
		
	}

	cout << posicion << "\n";
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
