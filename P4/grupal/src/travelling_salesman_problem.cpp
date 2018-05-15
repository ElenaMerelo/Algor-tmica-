#include "travelling_salesman_problem.h"

double graph::euclidean_distance(city c1, city c2){
  return sqrt(pow(c2.first - c1.first, 2) + pow(c2.second - c1.second, 2));
}

void graph::fill_matrix(const vector<city> &v){
  int n= v.size();

  //Inicializamos la matriz triangular superior
  m.resize(n);

  for(unsigned int i= 0; i< m.size(); i++)
    m[i].resize(n);

  for(int i= 0; i< n; i++)
    for(int j= i+1; j< n; j++)
      m[i][j]= euclidean_distance(v[i], v[j]);
}

bool graph::finished(){
  return nodos_vivos.empty();
}

void graph::clear(){
  visited.clear();
  visited.resize(m.size(), false);
}

//Creamos la matriz de adyacencia a partir del fichero pasado como argumento
graph::graph(const char *file){
  int num_cities, n;
  double x, y;
  string cabecera;
  ifstream f;

  f.open(file);

  if(!f){
    cout << "No se pudo abrir el fichero";
    exit(-1);
  }

  //Leemos hasta el primer espacio en blanco, lo correspondiente a "DIMENSION:"
  f >> cabecera;

  //Lo siguiente son el número de ciudades:
  f >> num_cities;

  //Creamos la lista con las ciudades y sus coordenadas en el mapa
  for(int i= 0; i< num_cities; i++){
    f >> n;
    f >> x;
    f >> y;
    cities.push_back(make_pair(x, y));
    nodos_vivos.push_back(i);
  }
  visited.resize(num_cities, false);
  fill_matrix(cities);
  f.close();
}



void graph::show_matrix(){
  for(unsigned int i= 0; i< m.size(); i++){
    for(unsigned int j= 0; j< m.size(); j++)
    cout << m[i][j] << " ";
    cout << "\n";
  }
}

void graph::show_path(vector<int> v, double longitud){
  cout << "Peso: " << longitud << ", recorrido: ";
  for(unsigned int i= 0; i< v.size(); i++)
    cout << v[i] << " ";
}

int graph::nearest_city(int i, double &min_dist){
  int j, n= cities.size();
  set<pair<double, int> > posibilidades;
  set<pair<double, int> >::iterator it;

  min_dist= 0;

  for(j= 0; j< nodos_vivos.size(); j++){
    //Si estamos en el triángulo superior de la matriz de adyacencia
    if( i > nodos[j])
    posibilidades.insert(make_pair(m[j][i], j));  //insertamos la distancia entre las ciudades y a qué ciudad va

    //Si no está en el triángulo superior obtenemos la coordenada simétrica
    else if( i< nodos[j])
    posibilidades.insert(make_pair(m[i][j], j));

    //Si i == j no se hace nada.
    }
  }

  //Como el set ordena automáticamente sus componentes, en la primera posición estará la mínima distancia
  it= posibilidades.begin();
  min_dist= it->first;
  return it->second;
}

vector<int> graph::min_path(int i, double &longitud){
  int j;
  longitud= 0;

  double min_dist;
  vector<int> r;

  for(int i= 0; i< recorridas.size(); i++)
    visited[recorridas[i]]= true;

  //Mientras haya ciudades por recorrer
  while(!finished()){
    //Añadimos la ciudad destino a la lista de ciudades recorridas
    r.push_back(i);
    visited[i]= true;

    j= nearest_city(i, min_dist);
    //Sumamos la distancia a la cantidad de camino recorrido
    longitud += min_dist;

    //Nos situamos en la ciudad destino y buscamos desde ahí el mínimo camino a la siguiente que no haya sido recorrida
    i= j;
  }
  return r;
}

vector<int> graph::close_path(vector<int> recorrido, double &longitud){
  vector<int> f= recorrido;
  int j= recorrido.back(), i= recorrido.front();

  if(i > j)
  longitud += m[j][i];
  else
  longitud += m[i][j];

  f.push_back(i);
  return f;
}

void graph::best_min_path(int node, double &l){
  double longitud_min= LONG_MAX;
  vector<int> actual;
  int next_city, position;
  recorridas.push_back(node);
  vector<int>::iterator it= find(nodos_vivos.begin(), nodos_vivos.end(), node);
  nodos_vivos.erase(it);

  while(!nodos_vivos.empty()){
    for(unsigned int i= 0; i< nodos_vivos.size(); i++){
      longitud= 0;
      //Hallamos el camino mínimo que comienza en el nodo i y pasa por las ciudades que no han sido recorridas
      actual= min_path(nodos_vivos[i], longitud);
      if(longitud< longitud_min){
        next_city= actual.front();
        position= i;
        longitud_min= longitud;
      }
    }
    recorridas.push_back(next_city);
    nodos_vivos.erase(position);

    l += longitud_min;
    best_min_path(next_city, l);
    }
  }



double graph::min_weight(vector<int> nodos_vivos){
  int i= nodos_vivos.front(), c2= nodos_vivos.back();
  clear();
  recorridas.push_back(c2);

  double longitud;
  vector<int> path= min_path(i, longitud);
  int j= path.back();


  path.push_back(c2);
  longitud += j < c2 ? m[j][c2] : m[c2][j];

  return longitud;
}

vector<int> graph::best_min_path(int i, double &longitud){

}








//
