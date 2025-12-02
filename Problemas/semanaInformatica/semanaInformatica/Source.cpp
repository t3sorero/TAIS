
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

#include "IndexPQ.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 El problema se resuelve utilizando una estrategia voraz combinada con una cola de prioridad para organizar las actividades y 
 determinar el mínimo número de recursos necesarios (en este caso, compañeros). La solución tiene en cuenta que las actividades 
 se pueden solapar, y busca asignar cada actividad al compañero que pueda cubrirla sin conflictos de horario.

 Primero, las actividades se ordenan en función de su tiempo de inicio. Esto garantiza que procesemos las actividades en el orden 
 en que comienzan, facilitando la asignación eficiente de recursos.

 Se utiliza una cola de prioridad variable donde se guarda donde va a terminar la actividad de cada compañero utilizado (incluido yo)
 Si este termina mas tarde de cuando empieza la siguiente actividad necesito un nuevo compañero, al cual le asigno la prioridad de cuando acabe su tarea
 En el otro caso actualizo la prioridad al compañero actual con la del final de actividad actual

 EL coste del sort esta  O(N log N) siendo N el numero de actividades
 El procesamiento de las actividades: log K siendo K mis compañeros usados en el push() y update() y se realiza N veces siendo N el numero de actividades:
 O(N log K)
 Coste total: O(N log N)
 Espacio adicional: vector actividades O(N)

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct Actividad {
	int inicio;
	int final;
};
bool operator < (Actividad a1, Actividad a2) {
	return a1.inicio < a2.inicio;
}


bool resuelveCaso() {
	int N;
	cin >> N;

	if (N ==0)  // fin de la entrada
		return false;
	vector<Actividad> v(N);
	for (int i = 0; i < N; i++) {
		cin >> v[i].inicio >> v[i].final;
	}

	sort(v.begin(), v.end());

	IndexPQ<int> pq(N);
	pq.update(0, v[0].final);
	int k = 0;
	for (int i = 1; i < N; i++) {
		
		if (pq.top().prioridad > v[i].inicio) {
			k++;
			pq.push(k, v[i].final);
		}
		else
			pq.update(pq.top().elem, v[i].final);
	}
	cout << k << "\n";

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
