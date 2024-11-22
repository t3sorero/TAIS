
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
	int N, L;
	cin >> N >> L;

	if (!std::cin)  // fin de la entrada
		return false;
	// 1. Longitud cuerda
	// 2. precio cuerda
	vector < pair<int, int>> v;
	for (int i = 0; i < N; i++) {
		int a, b; cin >> a >> b;
		v.push_back({ a,b });
	}
	/*
	*				{ cuerdas (i-1,j) si v[i-1] > j
	
	cuerdas(i,j) = 	{ cuerdas (i, j-v[i-1].first) +1 si j-v[i-1].first <= v[i-1].first

					{ No hace nada en el resto de casos
	*/
	Matriz<EntInf> cuerdas(N + 1, L + 1, Infinito);
	cuerdas[0][0] = 0;
	for (int i = 1; i <= N; i++) {
		cuerdas[i][0] = 0;
		cuerdas[i-1][v[i-1].first] = 1;
		for (int j = 1; j <= L; j++) {
			if (v[i - 1].first > j) {
				cuerdas[i][j] = cuerdas[i - 1][j];
			}
			else if (j-v[i-1].first <= v[i-1].first)
					cuerdas[i][j] = cuerdas[i][j - v[i - 1].first] + 1;
		}
	}
	if (cuerdas[N][L] != Infinito) {
		cout << "SI ";
		int res = 0;
		int lowcost = INT_MAX;
		// 1 longitud
		// 2 precio
		unordered_map<int, int> mapper;
		for (int i = 0; i < N; i++) {
			mapper.insert(v[i]);
			if (cuerdas[i + 1][L] != Infinito) {
				res++;
				int e = 0;
				EntInf a = cuerdas[i + 1][L];
				e += v[i].second;
				while (a > 1) {
					a = cuerdas[i + 1][L - v[i].first];
					e += mapper.at(L - v[i].first);
				}
				lowcost = min(lowcost, e);
			}
		}
		cout << res << " " << cuerdas[N][L] << " " << lowcost << "\n";

	}
	else cout << "NO\n";
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
