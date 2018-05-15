#ifndef __TRAVELLING_SALESMAN_PROBLEM__
#define __TRAVELLING_SALESMAN_PROBLEM__

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

typedef pair<double, double> city;

class graph{
private:
  vector<vector<double> > m;
  vector<city > cities;
  vector<bool> visited;

  double euclidean_distance(city c1, city c2);
  void fill_matrix(const vector<city> &v);
  bool finished();
  void clear();


public:
  //Crea la matriz de adyacencia a partir del fichero pasado como parámetro
  graph(const char* file);

  //Muestra la matriz de adyacencia
  void show_matrix();

  //Muestra el camino y su longitud
  void show_path(vector<int> path, double longitud);

  //Busca la ciudad más cercana a una dada
  int nearest_city(int city, double &min_dist);

  //Obtiene el camino mínimo desde la fila i columna j de la matriz
  vector<int> min_path(int i, double &longitud);

  //Añade al recorrido total la vuelta al punto de partida, con el peso adicional que eso conlleve
  vector<int> close_path(vector<int> recorrido, double &longitud);

  //Obtiene el camino mínimo de todos los posibles, comparando entre todos los recorridos que hay (tantos como ciudades)
  vector<int> best_min_path(double &longitud);

  //Reparte el recorrido entre varios electricistas
  vector<vector<int> > reparto_multiple(int origen, int n_electricians, double &longitud);

};

#endif
