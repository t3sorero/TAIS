
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

int vacas(Matriz<int>& dp, vector<int> const& comida, int i, int j, int turnos) {

	//Casos Base
	
	if (i > j)
		return 0;

	if (dp[i][j] != -1)
		return dp[i][j];
	//caso recursivo, distingo si como yo o come devoradora

	if (turnos % 2 == 1) { // me toca
		dp[i][j] = max(vacas(dp, comida, i + 1, j, turnos + 1) + comida[i], vacas(dp, comida, i, j - 1, turnos + 1) + comida[j]);
	}
	else { // su turno, come el que mas comida tenga
		int izq = comida[i];
		int der = comida[j];

		if (izq >= der) {
			dp[i][j] = vacas(dp, comida, i + 1, j, turnos + 1);
		}
		else {
			dp[i][j] = vacas(dp, comida, i, j - 1, turnos + 1);
		}
	}
	return dp[i][j];
}

bool resuelveCaso() {
	// leer los datos de la entrada
	int n; cin >> n;

	if (n == 0)  // fin de la entrada
		return false;
	
	vector<int> comida;
	for (int i = 0; i < n; i++) {
		int a; cin >> a;
		comida.push_back(a);
	}

	Matriz<int> dp(n, n, -1);

	int res = vacas(dp, comida, 0, n - 1, 1);
	cout << res << "\n";
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
