#include "matriz_de_adyacencia.h"

double matriz_de_adyacencia::distancia_euclidea(ciudad c1, ciudad c2){
  return sqrt(pow(c2.first - c1.first, 2) + pow(c2.second - c1.second, 2));
}

void matriz_de_adyacencia::rellenar_matriz(const vector<ciudad> &v){
  int n= v.size();

  //Inicializamos la matriz triangular superior
  m.resize(n);

  for(unsigned int i= 0; i< m.size(); i++)
    m[i].resize(n);

  for(int i= 0; i< n; i++)
    for(int j= i+1; j< n; j++)
      m[i][j]= distancia_euclidea(v[i], v[j]);
}

//Creamos la matriz de adyacencia a partir del fichero pasado como argumento
matriz_de_adyacencia::matriz_de_adyacencia(const char *fichero){
  int num_cities, n;
  double x, y;
  string cabecera;
  ifstream flujo;

  flujo.open(fichero);

  if(!flujo){
    cout << "No se pudo abrir el fichero";
    exit(-1);
  }

  //Leemos hasta el primer espacio en blanco, lo correspondiente a "DIMENSION:"
  flujo >> cabecera;

  //Lo siguiente son el número de ciudades:
  flujo >> num_cities;

  //Creamos la lista con las ciudades y sus coordenadas en el mapa
  for(int i= 0; i< num_cities; i++){
    flujo >> n;
    flujo >> x;
    flujo >> y;
    ciudades.push_back(make_pair(x, y));
    visitadas.push_back(false);
  }

  rellenar_matriz(ciudades);
  flujo.close();
}

bool matriz_de_adyacencia::recorrido_terminado(){
  return count(visitadas.begin(), visitadas.end(), false) == 0;
}

bool matriz_de_adyacencia::forma_ciclo(vector<int> recorrido, int nodo){
  for(unsigned int i= 0; i< recorrido.size(); i++)
    if(recorrido[i] == nodo)
      return true;

  return false;
}

vector<int> matriz_de_adyacencia::min_path(int i, double &longitud){
  int n= ciudades.size(), j;
  assert( i >= 0 && i < n);

  set<pair<double, int> > posibilidades;
  set<pair<double, int> >::iterator it;
  double min_dist, destino;
  vector<int> r;
  r.push_back(i);
  visitadas[i]= true;

  //Mientras haya ciudades por recorrer
  while(!recorrido_terminado()){
    for(j= 0; j< n; j++){
      //Si estamos en el triángulo superior de la matriz de adyacencia
      if(!forma_ciclo(r, j)){
        if( i > j)
        posibilidades.insert(make_pair(m[j][i], j));  //insertamos la distancia entre las ciudades y a qué ciudad va

        //Si no está en el triángulo superior obtenemos la coordenada simétrica
        else if( i< j)
        posibilidades.insert(make_pair(m[i][j], j));

        //Si i == j no se hace nada.
      }
    }

    //Como el set ordena automáticamente sus componentes, en la primera posición estará la mínima distancia
    it= posibilidades.begin();
    min_dist= it->first;
    destino= it->second;

    //Sumamos la distancia a la cantidad de camino recorrido
    longitud += min_dist;

    //Añadimos la ciudad destino a la lista de ciudades recorridass
    r.push_back(destino);
    visitadas[destino]= true;
    //Nos situamos en la ciudad destino y buscamos desde ahí el mínimo camino a la siguiente que no haya sido recorrida
    i= destino;

    posibilidades.clear();
  }
  return r;
}












//
