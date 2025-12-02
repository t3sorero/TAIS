
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include<algorithm>

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

int festival(vector<pair<int,int>> const& M, Matriz<int>& dp, int i, int j) {
	
	//casos base
	if (i == 0) return 0;

	if (j == 0) return 0;

	if (dp[i][j] != -1) {
		return dp[i][j];
	}
	//No eligo el nuevo festival i
	int noElegir = festival(M, dp, i - 1, j);

	int precio = M[i - 1].second;
	int personas = M[i - 1].first;
	int elegir = 0;
	//puedo elegir el nuevo festival i, veo si me conviene y no me paso de presupuesto pero tengo que evitar que repita festivales
	if (precio <= j) {
		elegir = festival(M, dp, i - 1, j - precio) + personas;
	}

	dp[i][j] = max(noElegir, elegir);

	return dp[i][j];
}

bool resuelveCaso() {
	int P, N;
	cin >> P >> N;
	if (!std::cin)  // fin de la entrada
		return false;
	// 1 personas
	// 2 precio
	vector < pair<int, int>> v;

	for (int i = 0; i < N; i++) {
		int a, b;
		cin >> a >> b;
		v.push_back({ a,b });
	}

	Matriz<int> dp(N + 1, P + 1, -1);

	// escribir la solución
	cout << festival(v, dp, N, P) << "\n";
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
