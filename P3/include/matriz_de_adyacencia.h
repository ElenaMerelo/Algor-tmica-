#ifndef __MATRIZ_DE_ADYACENCIA__
#define __MATRIZ_DE_ADYACENCIA__

#include <vector>
#include <utility>
#include <fstream>
#include <assert.h>
#include <algorithm>

using namespace std;

typedef pair<double, double> ciudad;

class matriz_de_adyacencia{
private:
  vector<vector<double> > m;
  vector<ciudad > ciudades;
  vector<bool> visitadas;

  double distancia_euclidea(ciudad c1, ciudad c2);
  void rellenar_matriz(const vector<ciudad> &v);
  bool end();
  bool forma_ciclo(vector<int> recorrido, int nodo);


public:
  //Crea la matriz de adyacencia a partir del fichero pasado como parámetro
  matriz_de_adyacencia(const char *fichero);

  //Obtiene el camino mínimo desde la fila i columna j de la matriz
  vector<int> min_path(int i, int j, double &longitud);
};

#endif
