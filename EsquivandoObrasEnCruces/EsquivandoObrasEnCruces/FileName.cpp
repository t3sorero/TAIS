
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#include "Matriz.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

int rellenaMatriz(Matriz<int>& m, Matriz<char>const& tablero, int i, int j) {

	//Casos Base

	if (i < 0 || j < 0)
		return 0;

	if (i == 0 && j == 0)
		return 1;

	if (tablero[i][j] == 'X')
		return 0;


	if (m[i][j] != -1) {
		return m[i][j];
	}
	//Casos Recursivos

	m[i][j] = rellenaMatriz(m, tablero, i - 1, j) + rellenaMatriz(m, tablero, i, j - 1);

	return m[i][j];
}

bool resuelveCaso() {
	// leer los datos de la entrada
	int N, M; cin >> N >> M;

	if (!std::cin)  // fin de la entrada
		return false;
	
	Matriz<char> tablero (N, M);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			char a; cin >> a;
			tablero[i][j] = a;
		}
	}

	Matriz<int> tablaDinamica(N, M, -1);

	/*
	* 
	* Casos base
	* 
	* cruce(0,0) = 1 hay un camino hasta el origen
	* tablero[i][j] == 'X' entonces return 0, hay una obra
	* 
	* casos recursivo
	* 
	* 
	* cruce(i,j) = cruce(i-1,j) + cruce (i, j-1) si tavblero[i][j] == .
	
	*/



	cout << rellenaMatriz(tablaDinamica,tablero,N-1,M-1) << "\n";
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
