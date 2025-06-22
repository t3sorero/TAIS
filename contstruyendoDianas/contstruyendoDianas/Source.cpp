
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

#include "EnterosInf.h"  // propios o los de las estructuras de datos de clase
#include"Matriz.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
EntInf calculaPuntuacion(Matriz<EntInf>& m, vector<int> const& v, int i, int j, Matriz<bool>& decision) {

	//Casos Base

	//No hay sectores, no hay puntuacion posible
	if (i == 0) return Infinito;

	// Conseguimos la puntuacion objetivo
	if (j == 0) return 0	;

	if (m[i][j] != EntInf(-1))
		return m[i][j];

	//No usar el sector i
	EntInf sinUsar = calculaPuntuacion(m, v, i - 1, j, decision);

	//Usarlo si es posible
	EntInf usandolo = Infinito;
	if (v[i-1] <= j) {
		 usandolo = calculaPuntuacion(m, v, i, j - v[i-1], decision) + 1;
	}

	// Tomar la decisión óptima y guardarla para reconstruccion
	if (sinUsar < usandolo) {
		m[i][j] = sinUsar;
		decision[i][j] = false;  // No usamos el sector i
	}
	else if(usandolo < sinUsar){
		m[i][j] = usandolo;
		decision[i][j] = true;   // Sí usamos el sector i
	}
	else {
		m[i][j] = usandolo;
		decision[i][j] = true;
	}

	return m[i][j];
}

vector<int> reconstruirSolucion(Matriz<bool>& decision, vector<int>& v, int S, int P) {
	vector<int> sol;
	int i = S, j = P;

	while (i > 0 && j > 0) {
		if (decision[i][j]) {
			// Usamos el sector i
			sol.push_back(v[i - 1]);
			j -= v[i - 1];
		}
		else {
			// No usamos el sector i
			i--;
		}
	}

	return sol;
}

bool resuelveCaso() {
	int P, S;
	cin >> P >> S;

	if (!std::cin)  // fin de la entrada
		return false;
	vector <int> v;
	for (int i = 0; i < S; i++) {
		int a; cin >> a;
		v.push_back(a);
	}

	//Nos aseguramos que los valores grandes estan al principio, para cumplir criterio de elegir mas grande si empate
	reverse(v.begin(), v.end());

	/*
	* Recurrencia aplicada
	*				{ dianas (i-1,j) si v[i-1] > j

	dianas(i,j) = 	{min(dianas(i-1,j), dianas (i, j-v[i-1]) +1) si v[i-1] <= j

	*/



	Matriz<EntInf> dianas(S + 1, P + 1, EntInf(-1));

	// true = usamos el sector i
	// false = no usamos el sector i
	Matriz<bool> decision(S + 1, P + 1, false);

	//Llamada inicial con todas los sectores disponibles y toda la puntuacion
	EntInf res = calculaPuntuacion(dianas, v, S, P, decision);

	if (res == Infinito)
		cout << "Imposible\n";
	else {
		//reconstruir solucion
		vector<int> sol = reconstruirSolucion(decision, v, S, P);
		sort(sol.begin(), sol.end(), greater<int>());
		cout << res << ": ";
		for (int k = 0; k < sol.size(); k++) {
			if (k > 0) cout << " ";
			cout << sol[k];
		}
		cout << "\n";
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
