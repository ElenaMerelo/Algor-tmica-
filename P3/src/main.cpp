#include <iostream>
#include <fstream>
#include "matriz_de_adyacencia.h"

using namespace std;

int main(int argc, char *argv){
  if(argc != 2){
    cout << "Número incorrecto de argumentos";
    exit(-1);
  }

  //Abrimos el fichero
  ifstream flujo;
  flujo.open(argv[1], ios::in);
  if (!flujo) {
    cout << "No se pudo abrir " << argv[1];
    exit(-1);
  }

  matriz_de_adyacencia m(flujo);

  double longitud= 0;
  vector<int> camino= m.min_path(0, longitud);

  cout << "Recorrido con peso mínimo " << longitud << ": ";
  for(int i= 0; i< camino.size(); i++)
    cout << i << " ";

  flujo.close();
}
