
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <string>

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

const int IGUALES = 0;
const int INSERTO_IZQ = 1;
const int INSERTO_DER = 2;
int aibofobia(string const& patitos, Matriz<int>& M, Matriz<int> &decision, int i, int j) {
	if (i >= j)
		return 0;
	if (M[i][j] != -1)
		return M[i][j];
		
	if (patitos[i] == patitos[j]) {

		M[i][j] = aibofobia(patitos, M, decision, i + 1, j - 1);
		decision[i][j] = IGUALES;
	}
	else {

		int izq = aibofobia(patitos, M, decision, i + 1, j);
		int der = aibofobia(patitos, M, decision, i, j - 1);

		if (izq <= der) {
			M[i][j] = izq + 1;
			decision[i][j] = INSERTO_IZQ;
		}
		else {
			M[i][j] = der + 1;
			decision[i][j] = INSERTO_DER;
		}
	}
		
	return M[i][j];
		
}

string reconstruir(string const& patitos, Matriz<int> const& decision, int i, int j) {
	if (i > j) return "";

	if (i == j) {
		// Un solo carácter en el medio
		return string(1, patitos[i]);
	}

	if (decision[i][j] == IGUALES) {
		// Los caracteres son iguales - los ponemos en los extremos
		string medio = reconstruir(patitos, decision, i + 1, j - 1);
		return patitos[i] + medio + patitos[j];
	}
	else if (decision[i][j] == INSERTO_IZQ) {
		// Insertamos el carácter izquierdo también al final
		string resto = reconstruir(patitos, decision, i + 1, j);
		return patitos[i] + resto + patitos[i];
	}
	else { // INSERTAR_DER
		// Insertamos el carácter derecho también al principio
		string resto = reconstruir(patitos, decision, i, j - 1);
		return patitos[j] + resto + patitos[j];
	}
}

bool resuelveCaso() {
	string patitos;
	cin >> patitos;

	if (!std::cin)  // fin de la entrada
		return false;
	int n = patitos.size();
	Matriz<int> M(n, n, -1);
	Matriz<int> decision(n, n, -1);

	for (int i = 0; i < n; i++) {
		M[i][i] = 0;
	}
	int sol = aibofobia(patitos, M, decision ,0,n-1);
	string izq,der;
	
	string res = reconstruir(patitos, decision, 0, n - 1);
	cout << sol << " " << res << "\n";
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
