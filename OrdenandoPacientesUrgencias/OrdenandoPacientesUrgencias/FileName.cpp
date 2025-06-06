
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>

using namespace std;

#include "PriorityQueue.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct Paciente {
	int indice;
	int dolor;
	string nombre;
	bool operator>(Paciente const& otro) const {
		return dolor > otro.dolor || (dolor == otro.dolor && indice < otro.indice);
	};
};

bool resuelveCaso() {
	int n; cin >> n;
	if (n == 0)  // fin de la entrada
		return false;

	PriorityQueue<Paciente, greater<Paciente>> pq;
	for (int i = 0; i < n; i++)
	{
		char A; cin >> A;

		if (A == 'A')
		{
			auto paciente = pq.top(); pq.pop();
			cout << paciente.nombre << endl;
		}
		else if (A == 'I') {
			string name; int dolor;
			cin >> name >> dolor;
			pq.push({ i, dolor,name });
		}
	}

	cout << "---\n";

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