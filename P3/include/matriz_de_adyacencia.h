#ifndef __MATRIZ_DE_ADYACENCIA__
#define __MATRIZ_DE_ADYACENCIA__

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

class matriz_de_adyacencia{
private:
  vector<vector<double> > m;
  vector<ciudad > ciudades;
  vector<bool> visitadas;

  double distancia_euclidea(ciudad c1, ciudad c2);
  void rellenar_matriz(const vector<ciudad> &v);
  bool recorrido_terminado();
  bool forma_ciclo(vector<int> recorrido, int nodo);
  void clear();


public:
  //Crea la matriz de adyacencia a partir del fichero pasado como parámetro
  matriz_de_adyacencia(const char* fichero);

  //Muestra la matriz de adyacencia
  void show_matrix();

  //Busca la ciudad más cercana a una dada
  int ciudad_mas_cercana(int i, double &min_dist, vector<int> recorrido);

  //Obtiene el camino mínimo desde la fila i columna j de la matriz
  vector<int> min_path(int i, double &longitud);

  //Obtiene el camino mínimo de todos los posibles, comparando entre todos los recorridos que hay (tantos como ciudades)
  vector<int> recorrido_optimo(double &longitud);

  //Reparte el recorrido entre varios electricistas
  //vector<vector<int> > reparto_multiple(int i, int n_electricians, double &longitud);

};

#endif
