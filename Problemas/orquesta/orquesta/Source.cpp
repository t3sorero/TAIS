
/*@ <authors>
 *

Javier Martín-Tesorero Ruiz TAIS064

Rafael Hernado Herias TAIS049
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include "Header.h"

using namespace std;

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */

struct InfoGrupo {
	int partituras;
	int tamanyo;
};

 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

bool operator > (const InfoGrupo &t1, const InfoGrupo &t2) {
	return t1.tamanyo*t2.partituras > t2.tamanyo*t1.partituras;
}

void orquesta(PriorityQueue<InfoGrupo, greater<InfoGrupo>> &queue ,int& n) {
	if (n == queue.size()) return;
	else {
		n--;
		InfoGrupo aux = queue.top();
		aux.partituras++;
		queue.pop();
		queue.push(aux);
		orquesta(queue, n);
	}
}
bool resuelveCaso(){

	int p, n;
	cin >> p >> n;
	if (!std::cin)  // fin de la entrada
		return false;

	PriorityQueue<InfoGrupo, greater<InfoGrupo>> queue;

	for (int i = 0; i < n; i++) {
		int aux;
		cin >> aux;
		queue.push({1, aux});
	}
	orquesta(queue, p);
	if (queue.top().tamanyo% queue.top().partituras == 0) 
		cout << queue.top().tamanyo / queue.top().partituras << endl;
	else 
		cout << (queue.top().tamanyo / queue.top().partituras) + 1 << endl;

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
