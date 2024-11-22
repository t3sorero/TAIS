
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include<algorithm>
#include<unordered_map>

using namespace std;

#include "EnterosInf.h"  // propios o los de las estructuras de datos de clase
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

bool ordenado(pair<int, int> const& a, pair<int, int>const& b) {
	return a.second < b.second;
}

bool resuelveCaso() {
	int P, N;
	cin >> P >> N;
	if (!std::cin)  // fin de la entrada
		return false;
	// 1 personas
	// 2 precio
	vector < pair<int, int>> v;

	for (int i = 0; i < N; i++) {
		int a, b;
		cin >> a >> b;
		v.push_back({ a,b });
	}

	sort(v.begin(), v.end(), ordenado);
	// matriz de personas
	Matriz<int> concierto(N + 1, P + 1, -1);
	vector<bool> usar(N, false);


	for (int i = 1; i <= N; i++) {
		concierto[i][0] = 0;
		for (int j = 1; j <= P; j++) {
			if (j < v[i - 1].second)
				concierto[i][j] = concierto[i - 1][j];
			else
				if (concierto[i][j - v[i - 1].second] == v[i - 1].first)
					concierto[i][j] = concierto[i][j - 1];
				else
					concierto[i][j] = max(concierto[i][j - v[i - 1].second] + v[i - 1].first, concierto[i][j - 1]);
			
		}
	}
	if (concierto[N][P] == -1) cout << 0 << "\n";
	cout << concierto[N][P] << "\n";

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
