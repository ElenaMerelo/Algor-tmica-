#include "matriz_de_adyacencia.h"


int main(int argc, char **argv){
  if(argc != 2){
    cout << "Número incorrecto de argumentos";
    exit(-1);
  }

  matriz_de_adyacencia m(argv[1]);
  double longitud, long_min;
  int origen, i;

  cout << "Introduzca ciudad por la que quiere empezar(0- dim-1): ";
  cin >> origen;
  vector<int> camino= m.min_path(origen, longitud);

  /* Descomentar si se quiere ver la matriz de adyacencia
  cout << "\nMatriz de adyacencia: \n";
  m.show_matrix();
  */

  cout << "\nEl recorrido con peso mínimo " << longitud << "es: ";
  for(i= 0; i< camino.size(); i++)
    cout << camino[i] << " ";

  vector<int> min= m.recorrido_optimo(long_min);
  cout << "\nEl camino más corto con peso " << long_min << " es: ";
  for(i= 0; i< min.size(); i++)
    cout << min[i] << " ";
}
