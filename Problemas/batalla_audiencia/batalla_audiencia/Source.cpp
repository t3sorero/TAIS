
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include "IndexPQ.h"
#include"PriorityQueue.h"

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

struct Resultado  
{  
   int canal;  
   int tiempo;  

   bool operator> (Resultado const& otro) const {  
	   if (tiempo == otro.tiempo)
		   return canal < otro.canal;
	   else
		   return tiempo > otro.tiempo;
   }
};

bool resuelveCaso() {
	int D, C, N, d;
	cin >> D >> C >> N;
	if (!std::cin)  // fin de la entrada
		return false;
	IndexPQ<int, greater<int>> queue(C);
	vector<int> lideres(C, 0);
	for (int i = 0; i < C; i++) {
		int aux;
		cin >> aux;
		queue.push(i, aux);
	}
	int oldD = 0;
	int anteriorLider = queue.top().elem;
	for (int i = 0; i < N; i++) {
		cin >> d;
		lideres[anteriorLider] += d - oldD;
		int canal;
		cin >> canal;
		while (canal != -1) {
			int nuevaAudiencia;
			cin >> nuevaAudiencia;
			queue.update(canal - 1, nuevaAudiencia);
			cin >> canal;
		}
		oldD = d;
		anteriorLider = queue.top().elem;
	}
	lideres[anteriorLider] += D - oldD;
	PriorityQueue<Resultado, greater<Resultado>> pq;
	for (int i = 0; i < C; i++) {
		if (lideres[i] > 0) {
			pq.push({ i + 1, lideres[i] });
		}
	}
	while (!pq.empty()) {
		Resultado r = pq.top(); pq.pop();
		cout << r.canal << " " << r.tiempo << endl;
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
