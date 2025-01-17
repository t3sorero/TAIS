
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

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct Bombilla {
	int carga;
	int beneficio;
};

bool operator < (Bombilla b1, Bombilla b2) {
	return b1.carga < b2.carga;
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

	Matriz<EntInf> tablaDinamica(N + 1, pMax + 1, Infinito);

	for (int i = 1; i <= N; i++) {
		tablaDinamica[i][0] = 0;
	}
	
	EntInf minim = Infinito;
	int potenciaUsada;
	for (int i = 1; i <= N; i++) {

		for (int j = 1; j <= pMax; j++) {
			if (luces[i-1].carga <= j) {
				EntInf izquierda, arriba;
				izquierda = tablaDinamica[i][j - luces[i - 1].carga] +  luces[i - 1].beneficio;
				arriba = tablaDinamica[i - 1][j];
				if (j > pMin) { //estoy en tramo
					tablaDinamica[i][j] = min(tablaDinamica[i][j - 1], min(izquierda, arriba));

					if (tablaDinamica[i][j] < minim) {
						minim = tablaDinamica[i][j];
						potenciaUsada = j;
						if (minim == tablaDinamica[i][j - 1])
							potenciaUsada = j - 1;
					}
				}
				else {
					tablaDinamica[i][j] = min(izquierda, arriba);
				}

			}
			else {
				tablaDinamica[i][j] = tablaDinamica[i - 1][j];
			}
		}
	}
	// resolver el caso posiblemente llamando a otras funciones
	if (tablaDinamica[N][pMax] != Infinito)
		cout << tablaDinamica[N][pMax] << " " << potenciaUsada << "\n";
	else
		cout << "IMPOSIBLE\n";

	

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
