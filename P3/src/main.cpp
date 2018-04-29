#include "matriz_de_adyacencia.h"


int main(int argc, char **argv){
  if(argc != 2){
    cout << "Número incorrecto de argumentos";
    exit(-1);
  }

  matriz_de_adyacencia m(argv[1]);

  double longitud= 0;
  vector<int> camino= m.min_path(1, longitud);

  cout << "Recorrido con peso mínimo " << longitud << ": ";
  for(int i= 0; i< camino.size(); i++)
    cout << camino[i] << " ";

}
