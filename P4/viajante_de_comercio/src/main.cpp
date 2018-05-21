#include "tsp.h"


int main(int argc, char **argv){
  if(argc != 2){
    cout << "Número incorrecto de argumentos";
    exit(-1);
  }

  matriz_de_adyacencia m(argv[1]);
  double longitud;
  int origen, i, n;

  cout << "Introduzca ciudad por la que quiere empezar(0- dim-1): ";
  cin >> origen;
  vector<int> camino= m.min_path(origen, longitud);

  /* Descomentar si se quiere ver la matriz de adyacencia
  cout << "\nMatriz de adyacencia: \n";
  m.show_matrix();
  */

  cout << "\nMin path\n";
  m.show_path(camino, longitud);

  vector<int> cerrado= m.cierra_camino(camino, longitud);
  cout << "\nCierra camino\n";
  m.show_path(cerrado, longitud);

  vector<int> min= m.recorrido_optimo(longitud);
  cout << "\nRecorrido óptimo usando greedy\n";
  m.show_path(min, longitud);


}











//
