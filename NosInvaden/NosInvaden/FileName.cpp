
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
	// leer los datos de la entrada
	int n; cin >> n;

	if (!std::cin)  // fin de la entrada
		return false;
	vector<int> enemigos;
	for (int i = 0; i < n; i++) {
		int a; cin >> a;
		enemigos.push_back(a);
	}
	sort(enemigos.begin(), enemigos.end());

	vector<int>aliados;
	for (int i = 0; i < n; i++) {
		int a; cin >> a;
		aliados.push_back(a);
	}
	sort(aliados.begin(), aliados.end());
	// resolver el caso posiblemente llamando a otras funciones
	int exitos = 0;
	int indexEnemigos = 0;
	for (int i = 0; i < n; i++) {
		if (enemigos[indexEnemigos] <= aliados[i]) {
			indexEnemigos++;
			exitos++;
		}
	}
	// escribir la solución
	cout << exitos << "\n";
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
