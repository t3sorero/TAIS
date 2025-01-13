
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#include "Matriz.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 bolloPan(i,j) cantidad maxima de beneficio que puede obtener por los bollos hechos con i tipos chorizo y j gramos de pan

 casos base 
 bolloPan (0,j) = 0
 bolloPan(i,0) = 0

 caso recursivo

 bolloPan(i,j) = max(bolloPan(i - 1, j - k * b.gramosPanPorBollo) + k * b.beneficio);
 siendo k el numero de bollos realizados con ese chorizo (0 <=k <=gramosTotales/gramosUsadosPorBollo)

 struct Bollo {
	int gramosTotales = Gramos totales que hay de cada tipo de chorizo
	int gramosUsadadosPorBollo = gramos de chorizo usados para hacer un bollo
	int gramosPanPorBollo = gramos de pan usados para hacer un bollo
	int beneficio = beneficio producido por cada bollo
	};

 Llamada inicial:
 bolloPan(N,M) siendo N el numero total de chorizos y M el numero Total de gramos de pan

 coste en tiempo: O(N*M*K) siendo K el numero de bollos que se pueden fabricar de un tipo de chorizo

 coste espacio adicional: O(N*M) realizado con programacion dinamica de forma descendente,
 si se realiza de forma ascendente y no se necesita saber el numero de bollos se puede mejorar el coste en O(M)

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct Bollo {
	int gramosTotales;
	int gramosUsadadosPorBollo;
	int gramosPanPorBollo;
	int beneficio;
};
	

bool resuelveCaso() {
	int tiposBollos, masaPanTotal;
	cin >> tiposBollos >> masaPanTotal;

	if (!std::cin)  // fin de la entrada
		return false;
	vector<Bollo> listaBollos;
	for (int i = 0; i < tiposBollos; i++) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		listaBollos.push_back({ a,b,c,d });
	}
	vector<int> bolloPan(masaPanTotal + 1, 0);

	for (int i = 1; i <= tiposBollos; i++) {
		
		Bollo b = listaBollos[i-1];

		for (int j = masaPanTotal; j >= 1; --j) {
			int k = 0;
			while (j - k * b.gramosPanPorBollo >= 0 && k * b.gramosUsadadosPorBollo <= b.gramosTotales) {
				bolloPan[j] = max(bolloPan[j], bolloPan[j - k * b.gramosPanPorBollo] + k * b.beneficio);
				++k;
			}
		}
	}

	cout << bolloPan[masaPanTotal] << "\n";
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
