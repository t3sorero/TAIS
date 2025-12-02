// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>

#include"Matriz.h"

using namespace std;

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    int k, s;

    cin >> k >> s;

    if (k == 1)
        cout << k << "\n";
    else {
        Matriz<int> dados(k+1, s+1, 0);

        for (int i = 1; i <= s; i++) {
            dados[1][i] = 1;
        }

        for (int i = 2; i <= k; i++) {
            for (int j = 1; j <= s; j++) {

                if (i > j) {
                    dados[i][j] = dados[i - 1][j];
                }
                else if (i == j) {
                    dados[i][j] = dados[i - 1][j] + 1;
                }
                else {
                    dados[i][j] = dados[i - 1][j] + dados[i][j - i];
                }
            }
        }

        cout << dados[k][s] << "\n";
    }
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}