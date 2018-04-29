#include "matriz_de_adyacencia.h"


int main(int argc, char **argv){
  if(argc != 2){
    cout << "Número incorrecto de argumentos";
    exit(-1);
  }

  matriz_de_adyacencia m(argv[1]);
  double longitud= 0;
  int origen;

  cout << "Introduzca ciudad por la que quiere empezar(0- dim-1): ";
  cin >> origen;
  vector<int> camino= m.min_path(origen, longitud);

  cout << "Recorrido con peso mínimo " << longitud << ": ";
  for(unsigned int i= 0; i< camino.size(); i++)
    cout << camino[i] << " ";

}
