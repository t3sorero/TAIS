
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

struct Intervalo {
	int ini;
	int fin;

	Intervalo(int i, int f): ini(i),fin(f){
	
	}

	bool operator<(Intervalo const& otro) {
		if (ini == otro.ini) return fin < otro.fin;
		else return ini < otro.ini;
	}
};

bool resuelveCaso() {
	int C, F, N;
	cin >> C >> F >> N;

	if (C==0 && F==0 && N==0)
		return false;

	vector<Intervalo> v;
	for (int i = 0; i < N; i++) {
		int a, b; cin >> a >> b;
		v.push_back({ a,b });
	}

	sort(v.begin(), v.end());
	int cont = 0; int cubierto = C;
	int i = 0;              
	bool posible = true;

	while (cubierto < F && posible && i < N) {
		int mejorFin = cubierto;

		while (i < N && v[i].ini <= cubierto) {
			mejorFin = max(mejorFin, v[i].fin);
			i++;
		}

		if (mejorFin == cubierto) {
			posible = false;
		}
		else {
			cubierto = mejorFin;
			cont++;
		}
	}

	if (cubierto < F) {
		posible = false;
	}

	// Escribir la solución
	if (posible) {
		cout << cont << endl;
	}
	else {
		cout << "Imposible" << endl;
	}

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
