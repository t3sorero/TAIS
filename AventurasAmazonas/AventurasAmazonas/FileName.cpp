
/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include<algorithm>
#include<limits>

using namespace std;

#include"IndexPQ.h"
#include"DigrafoValorado.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 Utilizo Dijkstra para cada vertice del grafo. Asi tengo todos los caminos minimos de cada vertice
 El coste esta en O(V * (A * log V)) siendo V en numero de vertices y A el numero de Aristas
 y coste O(V*V) en espacio adicional


 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
template<typename Valor>
class CaminosMinimos {
public:
	CaminosMinimos(DigrafoValorado<Valor> const& g, int orig) : origen(orig),
		dist(g.V(), INF), ulti(g.V()), pq(g.V()) {
		dist[origen] = 0;
		pq.push(origen, 0);
		while (!pq.empty()) {
			int v = pq.top().elem; pq.pop();
			for (auto a : g.ady(v))
				relajar(a);
		}
	}

	bool hayCamino(int v) const { return dist[v] != INF; }
	Valor distancia(int v) const { return dist[v]; }

private:
	const Valor INF = std::numeric_limits<Valor>::max();
	int origen;
	std::vector<Valor> dist;
	std::vector<AristaDirigida<Valor>> ulti;
	IndexPQ<Valor> pq;
	void relajar(AristaDirigida<Valor> a) {
		int v = a.desde(), w = a.hasta();
		if (dist[w] > dist[v] + a.valor()) {
			dist[w] = dist[v] + a.valor(); ulti[w] = a;
			pq.update(w, dist[w]);
		}
	}
};

bool resuelveCaso() {  
   // leer los datos de la entrada  
   int n; cin >> n;  

   if (!std::cin)  // fin de la entrada  
       return false;  

   DigrafoValorado<int> g(n);  
   for (int i = 0; i < n; i++) {  
       for (int j = i +1; j < n; j++) {  
           int d; cin >> d;  
		   g.ponArista({ i,j,d });
       }  
   }  

   for (int i = 0; i < n; i++) {  
       CaminosMinimos<int> cm(g, i);  

       for (int j = i + 1; j < n; j++) {  
           cout << cm.distancia(j) << " ";  
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
