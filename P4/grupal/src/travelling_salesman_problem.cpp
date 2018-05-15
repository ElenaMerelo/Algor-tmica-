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
  return count(visited.begin(), visited.end(), false) == 0;
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

  for(j= 0; j< n; j++){
    //Si estamos en el triángulo superior de la matriz de adyacencia
    if(!visited[j]){  //si no forma ciclo
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
  return it->second;
}

vector<int> graph::min_path(int i, double &longitud){
  int n= cities.size(), j;
  longitud= 0;

  double min_dist;
  vector<int> r;

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

double graph::lower_bound(vector<int> &best_min_path){
  double longitud, longitud_min= LONG_MAX;
  vector<int> actual;

  //best_min_path.clear();

  for(unsigned int i= 0; i< m.size(); i++){
    longitud= 0;
    clear();
    actual= min_path(i, longitud);
    if(longitud< longitud_min){
      best_min_path= actual;
      longitud_min= longitud;
    }
  }
  return longitud_min;
}

/*bool graph::valid_city(int start, int c){
  vector<int> path= min_path()
}*/

double graph::min_weight(int i, int c2){
  assert(i >= 0 && i< cities.size() && c2 >= 0 && c2< cities.size());
  clear();
  visited[c2]= true;

  double longitud;
  vector<int> path= min_path(i, longitud);
  int j= path.back();


  path.push_back(c2);
  longitud += j < c2 ? m[j][c2] : m[c2][j];
}











//
