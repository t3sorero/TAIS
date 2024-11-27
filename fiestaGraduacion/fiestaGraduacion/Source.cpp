
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <sstream>
#include<string>
#include<stack>

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


bool resuelveCaso() {
	
	string linea;
	getline(cin, linea);
	if (!std::cin)  // fin de la entrada
		return false;
	stringstream bufferM(linea);
	string man;
	
	vector<string> manyana;
	while (bufferM >> man)
		manyana.push_back(man);
	int n = manyana.size();

	getline(cin, linea);
	stringstream bufferT(linea);

	vector<string> tarde;
	while (bufferT >> man)
		tarde.push_back(man);
	int m = tarde.size();

	Matriz<int>canciones(n + 1, m + 1, -1);
	
	for (int i = 0; i < n; i++)
		canciones[i][0] = 0;


	for (int i = 0; i < m; i++)
		canciones[0][i] = 0;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {

			if (manyana[i-1] == tarde[j-1]) {
				canciones[i][j] = canciones[i - 1][j - 1] + 1;
			}
			else {
				canciones[i][j] = max(canciones[i - 1][j], canciones[i][j - 1]);
			}
		}
	}

	int i = n, j = m;
	stack<string> sol;
	while (i > 0 && j > 0) {
		if (manyana[i-1] == tarde[j-1]) {
			sol.push(manyana[i-1]);
			i--; j--;
		}
		else if (canciones[i - 1][j] > canciones[i][j-1]) {
			i--;
		}
		else {
			j--;
		}
	}
	while (!sol.empty()) {
			cout << sol.top() << " ";
			sol.pop();
	}
	
	cout << "\n";

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
