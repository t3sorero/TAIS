// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

#include"ConjuntosDisjuntos.h"
#include"GrafoValorado.h"
#include"PriorityQueue.h"


class Pueblos {
public:

    Pueblos(GrafoValorado<int> const& gv): pq(gv.aristas()), cj(gv.V()), maxim(0) {

        while (!pq.empty()) {
            auto a = pq.top();
            pq.pop();
            int v = a.uno(); int w = a.otro(v);
            if (!cj.unidos(v, w)) {
                cj.unir(v, w);
                maxim = max(maxim, a.valor());
                _ARM.push_back(a);
                if (_ARM.size() == gv.V()) break;
            }
        }
    }

    bool hayCamino() const {
        if (cj.num_cjtos() > 1)
            return false;
        return true;
    }

    int maximo() const {
        return maxim;
    }

private:
    PriorityQueue<Arista<int>> pq;
    ConjuntosDisjuntos cj;
    vector<Arista<int>> _ARM;
    int maxim;
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    int V, A;
    cin >> V >> A;

    GrafoValorado<int> gv(V);

    for (int i = 0; i < A; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        gv.ponArista({ --a, --b, c });
    }

    Pueblos p(gv);

    if (p.hayCamino())
        cout << p.maximo() << "\n";
    else
        cout << "IMPOSIBLE\n";


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