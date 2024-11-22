
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include<climits>
#include<limits>
#include<unordered_map>

using namespace std;

#include "EnterosInf.h"  // propios o los de las estructuras de datos de clase
#include"Matriz.h"

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
	int P, S;
	cin >> P >> S;

	if (!std::cin)  // fin de la entrada
		return false;
	vector <int> v;
	for (int i = 0; i < S; i++) {
		int a; cin >> a;
		v.push_back(a);
	}
	/*
	*				{ dianas (i-1,j) si v[i-1] > j

	dianas(i,j) = 	{ dianas (i, j-v[i-1].first) +1 si j-v[i-1].first <= v[i-1].first

	*/
	Matriz<EntInf> dianas(S + 1, P + 1, Infinito);
	dianas[0][0] = 0;
	for (int i = 1; i <= S; i++) {
		dianas[i][0] = 0;
		for (int j = 1; j <= P; j++) {
			if (v[i - 1] > j) {
				dianas[i][j] = dianas[i - 1][j];
			}
			else
				dianas[i][j] = min(dianas[i][j - v[i - 1]] + 1,dianas[i - 1][j]);
		}
	}
	if (dianas[S][P] != Infinito) {
		cout << dianas[S][P]<< ": ";
		vector<int> sol;
		int i = S, j = P;
		while (j > 0) {
			if (v[i - 1] <= j && dianas[i][j] != dianas[i - 1][j]) {
				sol.push_back(v[i - 1]);
				j -= v[i - 1];
			}
			else i--;
		}
		for (auto& a : sol) {
			cout << a << " ";
		}
		cout << "\n";
	}
	else cout << "Imposible\n";
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
