
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include<climits>

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



bool resuelveCaso() {
	int P;
	cin >> P;

	if (!std::cin)  // fin de la entrada
		return false;
	
	vector<vector<int>> listaPilas(P);
	int minim = INT_MAX;
	for (int i = 0; i < P; i++) {
		int l; cin >> l;
		vector<int> pila(l);
		for (int j = 0; j < l; j++) {
			int d; cin >> d;
			pila.push_back(d);
			minim = min(minim, d);
		}
		listaPilas[i] = pila;
	}
	
	bool encontrado = false;
	int posicion = 1;
	while (!encontrado) {
		pair<int, int> eliminado = { 0,listaPilas[0].back() }; // pila - elemento
		for (int i = 1; i < P; i++) {
			if (eliminado.second > listaPilas[i].back()) {
				eliminado = { i,listaPilas[i].back() };
			}
		}
		if (eliminado.second == minim)
			encontrado = true;
		else {
			posicion++;
			listaPilas[eliminado.first].pop_back();
		}
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
