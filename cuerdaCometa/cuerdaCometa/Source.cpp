#include <iostream>
#include <fstream>
#include <vector>
#include <climits>

using namespace std;

#include "EnterosInf.h"
#include "Matriz.h"

bool resuelveCaso() {
    int N, L;
    cin >> N >> L;

    if (!cin) return false;

    vector<pair<int, int>> cuerdas(N);
    for (int i = 0; i < N; i++) {
        cin >> cuerdas[i].first >> cuerdas[i].second;
    }
    /*
    * USANDO MATRICES DA RUN ERROR POR USO EXCESIVO DE MEMORIA
    * 
    * 
    // Tres matrices para los tres subproblemas
    // formas[i][j] = número de formas de conseguir longitud j con las primeras i cuerdas
    Matriz<long long> formas(N + 1, L + 1, 0);
    // minCuerdas[i][j] = mínimo número de cuerdas para longitud j con las primeras i cuerdas
    Matriz<EntInf> minCuerdas(N + 1, L + 1, Infinito);
    // minCoste[i][j] = mínimo coste para longitud j con las primeras i cuerdas
    Matriz<EntInf> minCoste(N + 1, L + 1, Infinito);

    // Casos base: longitud 0 se consigue con 0 cuerdas
    for (int i = 0; i <= N; i++) {
        formas[i][0] = 1;
        minCuerdas[i][0] = 0;
        minCoste[i][0] = 0;
    }

    // Llenar las matrices (MOCHILA 0/1)
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= L; j++) {
            // Opción 1: No usar la cuerda i-1
            formas[i][j] = formas[i - 1][j];
            minCuerdas[i][j] = minCuerdas[i - 1][j];
            minCoste[i][j] = minCoste[i - 1][j];

            // Opción 2: Usar la cuerda i-1 (si cabe)
            int longitud = cuerdas[i - 1].first;
            int precio = cuerdas[i - 1].second;

            if (j >= longitud) {
                // Para el número de formas: SUMAR las nuevas formas
                formas[i][j] += formas[i - 1][j - longitud];

                // Para el mínimo número de cuerdas
                if (minCuerdas[i - 1][j - longitud] != Infinito) {
                    EntInf nuevasCuerdas = minCuerdas[i - 1][j - longitud] + 1;
                    if (nuevasCuerdas < minCuerdas[i][j]) {
                        minCuerdas[i][j] = nuevasCuerdas;
                    }
                }

                // Para el mínimo coste
                if (minCoste[i - 1][j - longitud] != Infinito) {
                    EntInf nuevoCoste = minCoste[i - 1][j - longitud] + precio;
                    if (nuevoCoste < minCoste[i][j]) {
                        minCoste[i][j] = nuevoCoste;
                    }
                }
            }
        }
    }

    // Resultado final
    if (formas[N][L] == 0) {
        cout << "NO\n";
    }
    else {
        cout << "SI " << formas[N][L] << " " << minCuerdas[N][L] << " " << minCoste[N][L] << "\n";
    }
    */

    // Vectores para los tres subproblemas
    vector<long long> formas(L + 1, 0);
    vector<EntInf> minCuerdas(L + 1, Infinito);
    vector<EntInf> minCoste(L + 1, Infinito);

    // Casos base
    formas[0] = 1;
    minCuerdas[0] = 0;
    minCoste[0] = 0;

    // Procesar cada cuerda
    for (int i = 0; i < N; i++) {
        int longitud = cuerdas[i].first;
        int precio = cuerdas[i].second;

        // IMPORTANTE: R    ecorremos de DERECHA a IZQUIERDA
        // Esto evita usar la misma cuerda más de una vez
        for (int j = L; j >= longitud; j--) {
            // Si podemos formar la longitud j-longitud
            if (formas[j - longitud] > 0) {
                // Actualizar formas
                formas[j] += formas[j - longitud];

                // Actualizar mínimo número de cuerdas
                if (minCuerdas[j - longitud] != Infinito) {
                    EntInf nuevasCuerdas = minCuerdas[j - longitud] + 1;
                    if (nuevasCuerdas < minCuerdas[j]) {
                        minCuerdas[j] = nuevasCuerdas;
                    }
                }

                // Actualizar mínimo coste
                if (minCoste[j - longitud] != Infinito) {
                    EntInf nuevoCoste = minCoste[j - longitud] + precio;
                    if (nuevoCoste < minCoste[j]) {
                        minCoste[j] = nuevoCoste;
                    }
                }
            }
        }
    }

    if (formas[L] == 0) {
        cout << "NO\n";
    }
    else {
        cout << "SI " << formas[L] << " " << minCuerdas[L] << " " << minCoste[L] << "\n";
    }
    return true;
}

int main() {
#ifndef DOMJUDGE
    ifstream in("casos.txt");
    if (!in.is_open())
        cout << "Error: no se ha podido abrir el archivo de entrada." << endl;
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
    cout << "Pulsa Intro para salir..." << flush;
    cin.get();
#endif
    return 0;
}