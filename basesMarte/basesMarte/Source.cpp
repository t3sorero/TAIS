
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include<queue>

using namespace std;

#include "IndexPQ.h"  // propios o los de las estructuras de datos de clase
#include"PriorityQueue.h"
/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct Bateria{
	long long int id;
	long long int ttl; // tiempo maximo de vida
	long long int carga; // carga actual de la bateria
};
bool operator < (Bateria b1, Bateria b2) {
	if (b1.carga == b2.carga) {
		return b1.id < b2.id;
	}
	else
		return b1.ttl < b2.ttl;
}
bool resuelveCaso() {
	long long int P;
	cin >> P;
	if (!std::cin)  // fin de la entrada
		return false;
	vector<Bateria> pilas;
	for (int i = 0; i < P; i++) {
		long long int d; cin >> d;
		pilas.push_back({ i,d,d });
	}
	long long int R; cin >> R;

	queue<Bateria> reserva;
	for (int i = 0; i <R; i++) {
		long long int d; cin >> d;
		reserva.push({ P + i,d,d });
	}
	long long int Z, T;
	cin >> Z >> T;

	PriorityQueue<Bateria> pq(pilas);
	
	while (!pq.empty() && pq.top().ttl <= T)  {
		auto p = pq.top();
		if (p.carga - Z > 0) {
			p.carga -= Z; // disminuyo la carga
			p.ttl += p.carga; // aumento su ttl
			pq.pop();
			pq.push(p);
		}
		else {
			pq.pop();
			if (!reserva.empty()) {
				auto r = reserva.front();
				reserva.pop();
				r.ttl += p.ttl;
				pq.push(r);

			}
		}
	}

	if (pq.empty()) {
		cout << "ABANDONEN LA BASE INMEDIANTAMENTE\n";
	}
	else {
		if (pq.size() == P) {
			cout << "CORRECTO\n";
		}
		else {
			cout << "FALLO EN EL SISTEMA\n";
		}
		while (!pq.empty()) {
			cout << pq.top().id + 1 << " " << pq.top().ttl << "\n";
			pq.pop();
		}
	}
	cout << "---\n";
		
	// resolver el caso posiblemente llamando a otras funciones

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
