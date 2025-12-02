
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include<string>
#include<vector>
using namespace std;

using Mapa = vector<string>;

using elemento = pair<char, char>;

#include "ConjuntosDisjuntos.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>


const vector<pair<int, int>> Dirs = { {0,1},{0,-1},{1,0},{-1,0},{1,1},{-1,-1},{-1,1},{1,-1} };

const vector<pair<int, int>> DirsLectura = { {0,-1},{-1,0},{-1,-1},{-1,1} };

bool posCorrecta(int i, int j, int F, int C) {
	return (i >= 0 && i < F && j >= 0 && j < C);
}
bool resuelveCaso() {
	int F, C;
	cin >> F >> C;

	if (!std::cin)  // fin de la entrada
		return false;
	Mapa mapa(F);
	ConjuntosDisjuntos cj(F * C);
	int maximo = 0;
	int i = 0;
	for (string& first : mapa) {
		cin >> first;
		mapa[i] = first;
		for (int j = 0; j < C; j++) {
			if (first[j] == '#') {
				for (auto dirs : DirsLectura) {
					int ni = i + dirs.first;
					int nj = j + dirs.second;
					if (posCorrecta(ni, nj, F, C) && mapa[ni][nj] == '#') { 
						cj.unir(C * i + j, C * ni + nj); 
						maximo = max(maximo, cj.cardinal(C * i + j));
					}
				}
			}
		}
		i++;
	}

	cout << maximo << " ";
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int f, c; cin >> f >> c;
		for (auto dirs : Dirs) {
			int ni = f - 1 + dirs.first;
			int nj = c - 1 + dirs.second;
			if (posCorrecta(ni, nj, F, C) && mapa[ni][nj] == '#') {
				cj.unir(ni * C + nj, (f - 1) * C + c - 1); 
				maximo = max(maximo, cj.cardinal(ni * C + nj));
			}
		}
		cout << maximo << " ";
	}
	cout << endl;
	// escribir la solución

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
