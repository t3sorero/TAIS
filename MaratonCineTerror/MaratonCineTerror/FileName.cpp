/*@ <authors>
 *
 * Nombre, apellidos y usuario del juez (TAISXXX) de los autores de la solución.
 *
 *@ </authors> */
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

/*@ <answer>

 Este problema se resuelve mediante un algoritmo voraz.

 La estrategia es:
 1. Ordenar las películas por hora de finalización (inicio + duración)
 2. Seleccionar siempre la película que termine antes y que no solape con la anterior

 El coste es O(n log n) donde n es el número de películas, debido a la ordenación.

 @ </answer> */

 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct Hora {
    int horas;
    int minutos;

    Hora(int h = 0, int m = 0) : horas(h), minutos(m) {}

    int aMinutos() const {
        return horas * 60 + minutos;
    }

    Hora operator+(int min) const {
        int totalMinutos = aMinutos() + min;
        return Hora(totalMinutos / 60, totalMinutos % 60);
    }

    bool operator<(const Hora& otra) const {
        return aMinutos() < otra.aMinutos();
    }

    bool operator<=(const Hora& otra) const {
        return aMinutos() <= otra.aMinutos();
    }
};

struct Pelicula {
    Hora comienzo;
    int duracion;
    Hora fin; 

    Pelicula(Hora c, int d) : comienzo(c), duracion(d), fin(c + d) {}

    bool operator<(const Pelicula& otra) const {
        return fin < otra.fin;
    }
};

bool resuelveCaso() {
    // leer los datos de la entrada
    int P;
    cin >> P;

    if (P == 0)
        return false;

    vector<Pelicula> peliculas;

    for (int i = 0; i < P; i++) {
        int h, m, d;
        char sep;
        cin >> h >> sep >> m >> d;
        peliculas.push_back(Pelicula(Hora(h, m), d));
    }

 
    sort(peliculas.begin(), peliculas.end());

    int cont = 1; 
    Hora finUltimaPeli = peliculas[0].fin;

    for (int i = 1; i < P; i++) {
        if ((finUltimaPeli + 10) <= peliculas[i].comienzo) {
            cont++;
            finUltimaPeli = peliculas[i].fin;
        }
    }

    cout << cont << "\n";

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