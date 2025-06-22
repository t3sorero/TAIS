/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <limits>

using namespace std;

#include "DigrafoValorado.h"  // propios o los de las estructuras de datos de clase
#include "IndexPQ.h"

 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class Dijkstra {
public:
    Dijkstra(DigrafoValorado<int> const& g, int origen)
        : origen(origen), dist(g.V(), INF), numCaminos(g.V(), 0), pq(g.V()) {

        dist[origen] = 0;
        numCaminos[origen] = 1;
        pq.push(origen, 0);

        while (!pq.empty()) {
            int v = pq.top().elem;
            pq.pop();

            for (auto a : g.ady(v))
                relajar(a);
        }
    }

    int distancia(int v) const {
        return dist[v];
    }

    bool hayCamino(int v) const {
        return dist[v] != INF;
    }

    long long numeroCaminosMinimos(int v) const {
        return numCaminos[v];
    }

private:
    const int INF = std::numeric_limits<int>::max();
    int origen;
    vector<int> dist;
    vector<long long> numCaminos;
    IndexPQ<int> pq;

    void relajar(AristaDirigida<int> a) {
        int v = a.desde();
        int w = a.hasta();

        if (dist[w] > dist[v] + a.valor()) {
            dist[w] = dist[v] + a.valor();
            numCaminos[w] = numCaminos[v];
            pq.update(w, dist[w]);
        }
        else if (dist[w] == dist[v] + a.valor()) {
            
            numCaminos[w] += numCaminos[v];
        }
    }
};

bool resuelveCaso() {
    int V, A;
    cin >> V >> A;

    if (!cin)
        return false;

    DigrafoValorado<int> g(V);

    for (int i = 0; i < A; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        g.ponArista({ a - 1, b - 1, c });
    }

    Dijkstra dijkstra(g, 0);

    cout << dijkstra.numeroCaminosMinimos(V - 1) << "\n";

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