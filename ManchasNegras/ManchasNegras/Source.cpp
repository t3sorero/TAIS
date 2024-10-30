
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include "Grafo.h"
#include<vector>
#include<string>

using namespace std;

using Mapa = vector<string>;

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>



class ManchasNegras {
public:
	ManchasNegras(const Mapa & M) : F(M.size()), C(M[0].size()), visitados(F, vector<bool>(C, false)), manchas(0), maxim(0) {
		for (int i = 0; i < F; i++) {
			for (int j = 0; j < C; j++) {
				if (!visitados[i][j] && M[i][j] == '#') {
					manchas++;
					int tam = dfs(M, i, j);
					maxim = max(tam, maxim);
				}
			}
		}
	}

	int maximo() const { return maxim; }
	int numero() const { return manchas; }
	

private:
	int F, C;
	vector < vector<bool>> visitados;
	int maxim;
	int manchas;
	const vector<pair<int, int>> dirs = { {1,0},{-1,0},{0,1},{0,-1} };
	bool posCorrecta(int i, int j) {
		return 0 <= i && i < F && 0 <= j && j < C;
	}

	int dfs(const Mapa& M, int i, int j) {
		visitados[i][j] = true;
		int tam = 1;
		for (auto d : dirs) {
			int ni = i + d.first;
			int nj = j + d.second;
			if (posCorrecta(ni, nj) && M[ni][nj] == '#' && !visitados[ni][nj]) tam += dfs(M, ni, nj);
		}
		return tam;
	}
};

bool resuelveCaso() {
	int F, C;
	cin >> F >> C;

	if (!std::cin)  // fin de la entrada
		return false;

	Mapa mapa(F);

	for (string & linea : mapa) 
		cin >> linea;
	
	ManchasNegras manchas(mapa);
	cout << manchas.numero() << " " << manchas.maximo() << endl;
	
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
