#include "matriz_de_adyacencia.h"


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
  cout << "\nRecorrido óptimo\n";
  m.show_path(min, longitud);

  cout << "\nIntroduzca ciudad de partida para 1 electricista(aplicando reparto_multiple): ";
  cin>> origen;

  vector<vector<int> > rm1= m.reparto_multiple(origen, 1, longitud);
  cout << "\nSi hay 1 electricista(reparto_multiple). Longitud mínima: " << longitud << ". Recorrido: ";
  for(i= 0; i< rm1.size(); i++){
    for(int j= 0; j< rm1[i].size(); j++)
      cout << rm1[i][j] << " ";
    cout << "\n";
  }

  cout << "\nIntroduzca ciudad de partida y número de electricistas: ";
  cin>> origen;
  cin >> n;

  vector<vector<int> > rm2= m.reparto_multiple(origen, n, longitud);
  cout << "\nLongitud mínima: " << longitud << ". Recorrido de cada uno de los electricistas: ";
  for(i= 0; i< rm2.size(); i++){
    for(int j= 0; j< rm2[i].size(); j++)
      cout << rm2[i][j] << " ";
    cout << "\n";
  }
}











//
