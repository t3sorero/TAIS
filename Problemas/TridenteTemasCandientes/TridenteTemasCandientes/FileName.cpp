
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <climits>

using namespace std;

#include "IndexPQ.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct Tema {
	int puntuacion;
	int tendencia_reciente;

	bool operator >(Tema const& otro) const{
		if (puntuacion == otro.puntuacion)
			return tendencia_reciente > otro.tendencia_reciente;
		else
			return puntuacion > otro.puntuacion;
	}
};
bool resuelveCaso() {
	int n; cin >> n;
	if (!std::cin)  // fin de la entrada
		return false;

	IndexPQ<string, Tema, greater<Tema>> pq;

	for (int i = 0; i < n; ++i) {
		string c; cin >> c;

		if (c == "C") {
			string nombre; int puntuacion; cin >> nombre >> puntuacion;
			if (pq.contains(nombre)) {
				Tema t = pq.priority(nombre);
				pq.update(nombre, { t.puntuacion + puntuacion, i});
			}
			else
			{
				pq.push(nombre, { puntuacion,i });
			}
				
		}
		else if (c == "E") {
			string nombre; int puntuacion; cin >> nombre >> puntuacion;
			if (pq.contains(nombre)) {
				Tema t = pq.priority(nombre);
				if (t.puntuacion == puntuacion) {
					pq.update(nombre, { INT_MAX,i });
					pq.pop();
				}
				else {
					pq.update(nombre, { t.puntuacion - puntuacion,t.tendencia_reciente });
				}
			}

		}
		else if (c == "TC") {
			int range = min(3, pq.size());
			vector<pair<string, Tema>>temp;
			for (int i = 0; i < range; i++) {
				auto t = pq.top(); pq.pop();
				cout << i + 1 << " " << t.elem << "\n";
				temp.push_back({ t.elem,{t.prioridad.puntuacion ,t.prioridad.tendencia_reciente} });
				
			}
			for (int i = 0; i < range; i++) {
                pq.push(temp[i].first, temp[i].second);
			}
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
