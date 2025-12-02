
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

struct Tesoro{
	int profundidad;
	int valor;
};

int cazatesoros(Matriz<int>& dp, Matriz<bool>& decision, vector<Tesoro> const& v, int i, int j) {

	//Casos Base

	if (i == 0 || j == 0)
		return 0;

	if (dp[i][j] != -1)
		return dp[i][j];

	//Caso Recursivo

	//No cogo el objeto
	int noCoger = cazatesoros(dp, decision, v, i - 1, j);

	int tiempo = v[i - 1].profundidad + 2 * v[i - 1].profundidad;
	int coger = -1;
	if (tiempo <= j) {
		coger = cazatesoros(dp, decision, v, i - 1, j - tiempo) + v[i-1].valor;
	}

	if (coger >= noCoger) {
		dp[i][j] = coger;
		decision[i][j] = true;
	}
	else {
		dp[i][j] = noCoger;
		decision[i][j] = false;
	}
	return dp[i][j];

}

void reconstruir(Matriz<bool> const& decision, vector<Tesoro>const& v, int T, int S, vector<Tesoro>& tesorosElegidos) {

	int i = T; int j = S;
	
	while (i > 0 && j > 0) {
		if (decision[i][j]) {
			tesorosElegidos.push_back(v[i - 1]);
			int tiempo = v[i - 1].profundidad + 2 * v[i - 1].profundidad;
			j -= tiempo;
		}
		i--;
	}
	reverse(tesorosElegidos.begin(), tesorosElegidos.end());
}

bool resuelveCaso() {
	// leer los datos de la entrada
	int S; cin >> S;

	if (!std::cin)  // fin de la entrada
		return false;

	int T; cin >> T;

	vector<Tesoro> tesoros;
	for (int i = 0; i < T; i++) {
		int p, v; cin >> p >> v;
		tesoros.push_back({ p,v });
	}
	
	Matriz<int> dp(T + 1, S + 1, -1);
	Matriz<bool> decision(T + 1, S + 1, false);

	int res = cazatesoros(dp, decision, tesoros, T, S);

	cout << res << "\n";
	vector<Tesoro> elegidos;
	reconstruir(decision, tesoros, T, S, elegidos);
	cout << elegidos.size() << "\n";

	for (auto t : elegidos) {
		cout << t.profundidad << " " << t.valor << "\n";
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
