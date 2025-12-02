
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

#include "Matriz.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class TurronALaPuerta {
public:
	// Constructor
	TurronALaPuerta(int N, int S, vector<int> const& posLocales, vector<int> const& benLocales)
		: N(N), S(S), posLocales(posLocales), benLocales(benLocales), res(N+1,N+1,-1), decision(N+1,N+1,-1) {
		maxBeneficio = turron(N, N);
		reconstruirSolucion();
	}
	// Método para resolver el caso
	int beneficio() const{
		return maxBeneficio;
	}
	vector<int> elegidos() const {
		return localesElegidos;
	}
	


private:
	int N;  // Número de locales
	int S;  // Distancia máxima
	vector<int> posLocales;  // Posiciones de los locales
	vector<int> benLocales;  // Beneficios de los locales
	Matriz<int> res; // Matriz para almacenar resultados intermedios
	Matriz<int> decision; // Matriz para almacenar decisiones	
	int maxBeneficio = 0; // Variable para almacenar el beneficio máximo
	vector<int> localesElegidos;
	
	int turron(int i, int j) {
		if (i == 0)
			return 0; // Caso base: no hay locales
		else {
			if (res[i][j] != -1) {
				return res[i][j]; // Devolver el resultado ya calculado
			}
			else {
				int posUltima;
				if (j == N) {
					posUltima = posLocales[j - 1] + S;
				}
				else {
					posUltima = posLocales[j];
				}
				int ben = 0;
				if (posUltima - posLocales[i - 1] < S) {
					// Si el local i está dentro de la distancia S del local j
					ben = turron(i - 1, j);
				}
				else {
					int noPoner = turron(i - 1, j);
					int poner = benLocales[i - 1] + turron(i - 1, i - 1);
					if (poner > noPoner) {
						ben = poner;
						decision[i][j] = i;
					}
					else {
						ben = noPoner;
					}
				}
				res[i][j] = ben;
				return ben;
			}
		}
	}

	void reconstruirSolucion() {
		int i = N, j = N;
		while (i > 0) {
			if (decision[i][j] == i) {
				localesElegidos.push_back(posLocales[i-1]);
				j = i - 1;
			}
			--i;
		}
		reverse(localesElegidos.begin(), localesElegidos.end());
	}
	
};
bool resuelveCaso() {
	// leer los datos de la entrada
	int N, S;
	cin >> N >> S;

	if (!std::cin)  // fin de la entrada
		return false;

	vector<int> posLocales(N);
	for (int i = 0; i < N; ++i) {
		cin >> posLocales[i];
	}
	vector<int>benLocales(N);
	for (int i = 0; i < N; ++i) {
		cin >> benLocales[i];
	}

	// resolver el caso posiblemente llamando a otras funciones
	TurronALaPuerta tp(N, S, posLocales, benLocales);
	// escribir la solución
	cout << tp.beneficio() << ":";
	for (int i : tp.elegidos())
		cout << " " << i;
	cout << endl;
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
