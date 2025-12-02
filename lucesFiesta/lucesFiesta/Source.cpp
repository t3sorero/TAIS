
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include<algorithm>

using namespace std;

#include "Matriz.h"  // propios o los de las estructuras de datos de clase
#include"EnterosInf.h"
/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 hago un simil al problema de la mochila donde se puede repetir los objetos
 despues calculo cuales serian los minimos entre pmin y pmax, y me quedo con el mejor

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct Bombilla {
	int carga;
	int beneficio;
};

bool operator < (Bombilla const& b1, Bombilla const&  b2) {
	return b1.carga < b2.carga;
}

EntInf bombillas(Matriz<EntInf>& dp, vector<Bombilla> const& v, int i, int j) {

	//Casos Base

	if (i == 0) return Infinito;

	if (j == 0) return 0;

	if (dp[i][j] != EntInf(-1))
		return dp[i][j];

	//Caso recursivo, mochila con repeticion

	EntInf noCoger = bombillas(dp, v, i - 1, j);
	EntInf coger = Infinito;
	if (v[i - 1].carga <= j) { // puedo coger otra bombilla
		coger = bombillas(dp, v, i, j - v[i - 1].carga) + v[i - 1].beneficio;
	}
	dp[i][j] = min(noCoger, coger);

	return dp[i][j];
}


bool resuelveCaso() {
	int N, pMax, pMin;
	cin >> N >> pMax >> pMin;
	if (!std::cin)  // fin de la entrada
		return false;

	vector<Bombilla> luces;

	for (int i = 0; i < N; i++) {
		int a; cin >> a;
		luces.push_back({ a,0 });
	}
	for (int i = 0; i < N; i++) {
		cin >> luces[i].beneficio;
	}

	Matriz<EntInf> tablaDinamica(N + 1, pMax + 1, EntInf(-1));

	EntInf minCoste = Infinito;
	int potenciaOptima = -1;

	for (int p = pMin; p <= pMax; p++) {
		EntInf coste = bombillas(tablaDinamica, luces, N, p);
		if (coste < minCoste) {
			minCoste = coste;
			potenciaOptima = p;
		}
	}
	if (minCoste == Infinito)
		cout << "IMPOSIBLE\n";
	else
		cout << minCoste << " " << potenciaOptima << "\n";
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
