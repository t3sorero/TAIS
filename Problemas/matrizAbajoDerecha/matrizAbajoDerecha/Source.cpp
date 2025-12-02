
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>

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

int formas(Matriz<int> const& matrix, int i, int j, Matriz<int> &tablaDinamica) {
	// casos base
	if (!matrix.posCorrecta(i, j))
		return 0;
	else if (i == matrix.numfils() - 1 && j == matrix.numcols() - 1)
		return 1;
	//caso recursivo
	else {
		if (tablaDinamica[i][j] == -1)
			return tablaDinamica[i][j] = formas(matrix, i + matrix[i][j], j, tablaDinamica) + formas(matrix, i, matrix[i][j] + j, tablaDinamica);
		else
			return tablaDinamica[i][j];
	}
}

bool resuelveCaso() {
	int N, M;
	cin >> N >> M;
	if (!std::cin)  // fin de la entrada
		return false;
	Matriz<int> matrix(N, M, 0);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> matrix[i][j];
		}
	}
	Matriz<int> tablaDinamica(N, M, -1);
	int sol = formas(matrix, 0, 0, tablaDinamica);
	cout << sol << "\n";
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
