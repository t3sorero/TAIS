

#include <iostream>
#include <iomanip>
#include <fstream>
#include "Grafo.h"
#include<vector>

using namespace std;
// función que resuelve el problema
class AmigosDeAmigos {
public:

    AmigosDeAmigos(const Grafo& g) : visitados(g.V(), false), maximo(0) {
        for (int i = 0; i < g.V(); i++) {
            if (!visitados[i]) {
                int tam = masGrupo(g, i);
                maximo = max(tam, maximo);
            }
        }
    }
    int masGrande() {
        return maximo;
    }

private:
    vector<bool> visitados;
    int maximo;
    int masGrupo(const Grafo& g, int v) {
        visitados[v] = true;
        int tam = 1;
        for (int i : g.ady(v)) {
            if (!visitados[i]) {
                tam += masGrupo(g, i);
            }
        }
        return tam;
    }
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    int N, M; // n = personas, m = pares de personas que conoces
    cin >> N >> M;
    Grafo g(N);
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        g.ponArista(a-1, b-1);
    }
    AmigosDeAmigos grupo(g);
    int sol = grupo.masGrande();
    cout << sol << endl;


}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
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