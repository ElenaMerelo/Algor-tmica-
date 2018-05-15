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
  vector<int> recorridas, nodos_vivos;

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

  //Busca la ciudad más cercana a una dada de entre las disponibles
  int nearest_city(int city, double &min_dist);

  //Obtiene cuál es el camino mínimo que hay que hacer para recorrer todas las ciudades empezando por i
  vector<int> min_path(int i, double &longitud);

  //Añade al recorrido total la vuelta al punto de partida, con el peso adicional que eso conlleve
  vector<int> close_path(vector<int> recorrido, double &longitud);


  //Obtiene el peso del camino mínimo de entre todas las ciudades que no han sido visitadas
  double lower_bound();

  //Comprueba si el camino desde la ciudad c hasta el final es menor que la cota inferior
  //bool valid_city(int c);

  //Devuelve el peso del menor recorrido que hay de la ciudad c1 en la que se comienza hasta la final o c2
  double min_weight(int c1, int c2);

  //Empezando en la ciudad i encuentra el mejor recorrido de todos empleando branch and bound
  vector<int> best_min_path(int i, double &longitud);
};

#endif
