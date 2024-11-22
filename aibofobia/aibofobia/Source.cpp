
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#include "Matriz.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
int aibofobia(string const& patitos, Matriz<int>&M,int i, int j) {
	if (i >= j)
		return 0;
	int& res = M[i][j];
	if (res != -1) 
		return res;
		
	if (patitos[i] == patitos[j])
		res = aibofobia(patitos, M, i + 1, j - 1);
	else
		res = min(aibofobia(patitos, M, i + 1, j), aibofobia(patitos, M, i, j - 1)) + 1;
		
	return res;
		
}

void reconstruir(string const& patitos, Matriz<int>const& M, int i, int j, string& rec) {
	if (i > j)return;
	if (i == j) 
		rec.push_back(patitos[i]);
	else if (patitos[i] == patitos[j]) {
		rec.push_back(patitos[i]); // Insertar ambos extremos
		reconstruir(patitos, M, i + 1, j - 1, rec);
		rec.push_back(patitos[j]);
	}
	else if (M[i][j] == M[i][j - 1]) {
		rec.push_back(patitos[j]); // Insertar desde la derecha
		reconstruir(patitos, M, i, j - 1, rec);
		rec.push_back(patitos[j]);
	}
	else {
		rec.push_back(patitos[i]); // Insertar desde la izquierda
		reconstruir(patitos, M, i + 1, j, rec);
		rec.push_back(patitos[i]);
	}
}

bool resuelveCaso() {
	string patitos;
	cin >> patitos;

	if (!std::cin)  // fin de la entrada
		return false;
	int n = patitos.size();
	Matriz<int> M(n, n, -1);
	for (int i = 0; i < n; i++) {
		M[i][i] = 0;
	}
	int sol = aibofobia(patitos, M,0,n-1);
	string rec;
	reconstruir(patitos, M, 0, n-1, rec);
	cout << sol << " " << rec << "\n";
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
