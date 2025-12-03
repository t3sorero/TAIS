# Técnicas Algorítmicas en Ingeniería del Software (TAIS)

**Universidad Complutense de Madrid (UCM)**  
**Grado en Ingeniería del Software - 3º Curso**  
**Curso 2024-2025**

## 📋 Descripción

Repositorio de la asignatura **Técnicas Algorítmicas en Ingeniería del Software** del tercer curso del Grado en Ingeniería del Software en la UCM. Esta asignatura profundiza en estructuras de datos avanzadas y algoritmos sobre grafos, aplicando técnicas de diseño algorítmico a problemas complejos de ingeniería del software.

## 🎯 Contenido de la Asignatura

### Estructuras de Datos Avanzadas
- **Árboles de Búsqueda Binaria (BST)**: Operaciones y balanceo
- **Árboles AVL**: Árboles de búsqueda autobalanceados
- **Montículos (Heaps)**: Implementación de colas de prioridad
- **Conjuntos Disjuntos (Union-Find)**: Estructura para particiones dinámicas

### Algoritmos sobre Grafos
- **Representación de Grafos**: Listas de adyacencia, matrices
- **Recorridos**: BFS (Búsqueda en Anchura) y DFS (Búsqueda en Profundidad)
- **Caminos Mínimos**:
  - Algoritmo de Dijkstra (caminos más cortos desde un origen)
  - Algoritmo de Floyd-Warshall (caminos más cortos entre todos los pares)
- **Árboles de Expansión Mínima**:
  - Algoritmo de Kruskal
  - Algoritmo de Prim
- **Grafos Dirigidos**: Componentes fuertemente conexas, ordenación topológica

### Técnicas de Diseño
- **Algoritmos Voraces (Greedy)**: Aplicaciones avanzadas
- **Programación Dinámica**: Optimización en grafos y problemas complejos

## 🛠️ Tecnologías Utilizadas

- **Lenguaje**: C++17
- **STL**: Uso extensivo de contenedores y algoritmos de la biblioteca estándar
- **Compilador**: g++ con flags de optimización
- **Estructuras propias**: TADs proporcionados por el profesorado (Creative Commons)

## 📂 Estructura del Repositorio
```
TAIS/
├── README.md
└── Problemas/            # Ejercicios del juez online sin clasificar
    ├── problema_01
    ├── problema_15
    ├── problema_23
    └── ...
```

> **Nota:** Este repositorio contiene los ejercicios resueltos del juez online de la asignatura. Actualmente no están organizados por carpetas temáticas, pero cada problema implementa algoritmos y estructuras de datos avanzadas: árboles balanceados, montículos, grafos (BFS, DFS, Dijkstra, Kruskal, Prim), conjuntos disjuntos, y técnicas como voraz y programación dinámica.

## 🚀 Cómo Compilar y Ejecutar

### Compilación
```bash
g++ -std=c++17 -O2 -o problema problema.cpp
./problema < casos.txt
```

### Con debugging
```bash
g++ -std=c++17 -g -o problema problema.cpp
gdb ./problema
```

## 🔍 Problemas Resueltos

Este repositorio contiene soluciones a problemas del juez online de la asignatura. Los ejercicios están actualmente sin organizar por carpetas temáticas, pero cada uno aplica conceptos específicos de:
- Árboles de búsqueda balanceados (AVL, BST)
- Montículos y colas de prioridad
- Algoritmos sobre grafos (recorridos, caminos mínimos, árboles de expansión)
- Estructuras Union-Find
- Técnicas de programación dinámica y algoritmos voraces

Cada solución incluye:
- Código fuente optimizado para el juez online
- Implementación eficiente cumpliendo límites de tiempo y memoria
- Uso apropiado de TADs y STL de C++

## 📚 Conceptos Clave

### Complejidad
- **Árboles balanceados**: O(log n) en operaciones de búsqueda, inserción y borrado
- **Dijkstra**: O((V + E) log V) con cola de prioridad
- **Kruskal**: O(E log E) ordenando aristas
- **Floyd-Warshall**: O(V³) para todos los pares de caminos

### Aplicaciones en Ingeniería del Software
- Optimización de redes y routing
- Planificación de tareas con dependencias
- Diseño de sistemas distribuidos
- Análisis de dependencias en sistemas software

## 📖 Recursos

- Material de la asignatura (UCM Virtual)
- [Visualgo - Visualización de algoritmos](https://visualgo.net/)
- Bibliografía:
  - "Algorithms" - Robert Sedgewick, Kevin Wayne
  - "Introduction to Algorithms" - CLRS

## 👤 Autor

**Javier Martín-Tesorero Ruiz**  
Estudiante de Ingeniería del Software - UCM  
[GitHub](https://github.com/t3sorero) | [LinkedIn](https://linkedin.com/in/javier-martín-tesorero-0127a62b5)

## 📄 Licencia

Proyecto con fines educativos. Las implementaciones de TADs del profesorado están bajo licencia Creative Commons. El código de las soluciones puede ser usado como referencia académica.
