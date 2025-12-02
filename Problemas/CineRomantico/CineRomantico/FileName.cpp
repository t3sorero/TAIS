
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

#include "Matriz.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
struct Hora {
	int horas;
	int minutos;

	Hora(int h, int m) :horas(h), minutos(m) {

	}

	int aMinutos() const {
		return horas * 60 + minutos;
	}

	Hora aHoras(int minutos) const {

		return Hora(minutos / 60, minutos % 60);
	}
};

struct Pelicula {
	int duracion;
	Hora comienzo;
	Hora fin;
};

static const bool esCompatible(Hora const& fin, Hora const& ini)  {
	return fin.aMinutos() + 10 < ini.aMinutos();
}
int cine(Matriz<int>& dp, vector<Pelicula> const& p, int i, int j) {

	//Caso base

	if (i >= p.size())
		return 0;

	if (dp[i][j+1] != -1)
		return dp[i][j+1];

	//Caso recursivo

	int noVeo = cine(dp, p, i + 1, j);

	int veo = -1;

	if (j == -1) {// no he visto ninguna pelicula
		veo = cine(dp, p, i + 1, i) + p[i].duracion;
	}
	else {
		if (esCompatible(p[j].fin, p[i].comienzo))
			veo = cine(dp, p, i + 1, i) + p[i].duracion;
	}

	dp[i][j + 1] = max(noVeo, veo);

	return dp[i][j + 1];
}
bool resuelveCaso() {
	// leer los datos de la entrada
	int n; cin >> n;

	if (n == 0)  // fin de la entrada
		return false;
	vector<Pelicula> v;
	for (int i = 0; i < n; i++) {
		int hora, min, d;
		char sep;
		cin >> hora >> sep >> min >> d;
		Hora ini(hora, min);
		Hora fin(ini.aHoras(ini.aMinutos() + d));
		v.push_back({ d, ini,fin });
	}

	Matriz<int> dp(n, n + 1, -1);

	cout << cine(dp, v, 0, -1) << "\n";
	
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
