#include "travelling_salesman_problem.h"


int main(int argc, char **argv){
  if(argc != 2){
    cout << "Número incorrecto de argumentos";
    exit(-1);
  }

  graph m(argv[1]);
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

  vector<int> cerrado= m.close_path(camino, longitud);
  cout << "\nCierra camino\n";
  m.show_path(cerrado, longitud);

  double cota_inferior= m.lower_bound();
  cout << "\nCota inferior";
  cout << "\nRecorrido óptimo\n";
  m.show_path(camino, cota_inferior);

  int c1, c2;
  cout << "\nMin weight";
  cout << "\nIntroduzca ciudad desde la que quiere empezar y en cuál quiere acabar: ";
  cin >> c1 >> c2;
  cout << "\nEl recorrido mínimo de una a otra es: " << m.min_weight(c1, c2);

}











//
