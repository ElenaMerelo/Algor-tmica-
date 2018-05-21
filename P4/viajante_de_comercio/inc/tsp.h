#ifndef __TSP__
#define __TSP__

#include <vector>
#include <utility>
#include <fstream>
#include <assert.h>
#include <algorithm>
#include <math.h>
#include <limits.h>
#include <set>
#include <iostream>

using namespace std;

typedef pair<double, double> ciudad;
typedef pair <double, vector<int> > nodo;

class matriz_de_adyacencia{
private:
  vector<vector<double> > m;
  vector<ciudad > ciudades;
  vector<bool> visitadas;

  double distancia_euclidea(ciudad c1, ciudad c2);
  void rellenar_matriz(const vector<ciudad> &v);
  bool recorrido_terminado();
  void clear();


public:
  //Crea la matriz de adyacencia a partir del fichero pasado como parámetro
  matriz_de_adyacencia(const char* fichero);

  //Muestra la matriz de adyacencia
  void show_matrix();

  //Muestra el camino y su longitud
  void show_path(vector<int> path, double longitud);

  //Busca la ciudad más cercana a una dada
  int ciudad_mas_cercana(int city, double &min_dist);

  //Obtiene el camino mínimo desde la fila i columna j de la matriz
  vector<int> min_path(int i, double &longitud);

  //Añade al recorrido total la vuelta al punto de partida, con el peso adicional que eso conlleve
  vector<int> cierra_camino(vector<int> recorrido, double &longitud);

  //Obtiene el camino mínimo de todos los posibles, comparando entre todos los recorridos que hay (tantos como ciudades)
  vector<int> recorrido_optimo(double &longitud);

  //Dado por ejemplo un vector con los nodos visitados, obtiene los que quedan por visitar
  vector<int> vector_suplementario(vector<int> v);

  //Dado un camino, obtiene el coste resultante de recorrerlo
  double coste_camino(vector<int> c);

  //Obtiene el posible peso de recorrer
  double coste_posible(vector<int> nodos_recorridos);

  //Desarrolla el primer nivel del árbol comenzando por el nodo i
  vector<nodo> nivel_siguiente(vector<int> nodos_recorridos);

  //Obtiene el camino óptimo empleando el método de ramifiación y poda
  void branch_and_bound(vector<int> &recorrido);
};

#endif
