#ifndef __MATRIZ_DE_ADYACENCIA__
#define __MATRIZ_DE_ADYACENCIA__

#include <vector>
#include <utility>
#include <fstream>
#include <assert.h>
#include <algorithm>
#include <math.h>
#include <set>
#include <iostream>
#include <limits.h>

using namespace std;

typedef pair<double, double> city;

double euclidean_distance(city c1, city c2){ return sqrt(pow(c2.first - c1.first, 2) + pow(c2.second - c1.second, 2)); }

class graph{
  private:
    vector<vector<double> > m;
    vector<city> cities;
    vector<bool> visited;

    void fill(const vector<city> &v);
    bool finished_path();
    bool cycle(vector<int> path, int node);
    void clear();
    int easternmost_city();
    int westernmost_city();
    int northernmost_city();
    pair<int, double> particular_min(vector<int>& path, int x);
    pair<int, int> general_min(vector<int> &r);

  public:
    graph(const char* fichero);

    double get_weight(int i, int j);
    double total_weight(vector<int> path);

    void close_path(vector<int> &path, double &longitud);
    vector<int> optimal_path(double &l_min);

    int nearest_city(int i, double &min_dist);
    vector<int> min_path1(int i, double &l);
    vector<int> min_path2(int i, double &l);
    vector<int> min_path3(int i, double &l);

};

double graph::get_weight(int i, int j){

  assert(i<cities.size() && j<cities.size());

  if( i==j ) return 0;
  else if( i>j ) return m[j][i];
  else return m[i][j];
}

bool graph::finished_path(){ return count(visited.begin(), visited.end(), false) == 0; }

bool graph::cycle(vector<int> path, int node){
  for(unsigned int i= 0; i<path.size(); i++)
    if(path[i] == node)
      return true;
  return false;
}

void graph::fill(const vector<city> &v){
  int n= v.size();
  m.resize(n);

  for(unsigned int i= 0; i< m.size(); i++)
    m[i].resize(n);

  for(int i=0; i<n; i++)
    for(int j=i+1; j<n; j++)
      m[i][j]= euclidean_distance(v[i], v[j]);
}

graph::graph(const char *file){
  int num_cities, n;
  double x, y;
  string header;
  ifstream f;

  f.open(file);

  if(!f){
    cerr << "No se pudo abrir el fichero" << endl;
    exit(-1);
  }

  f >> header;
  f >> num_cities;

  for(int i=0; i< num_cities; i++){
    f >> n;
    f >> x;
    f >> y;
    cities.push_back( make_pair(x, y) );
  }

  visited.resize(n, false);

  fill(cities);

  f.close();
}

void graph::clear(){
  visited.clear();
  visited.resize(m.size(), false);
}

void graph::close_path(vector<int> &path, double &longitud){
  int j= path.back(), i= path.front();

  if(i > j)
    longitud += m[j][i];
  else
    longitud += m[i][j];

  path.push_back(i);
}

vector<int> graph::optimal_path(double &l_min){
  double l= 0;
  l_min= LONG_MAX;
  vector<int> current, min;

  for(int i=0; i<m.size(); i++){
    l= 0; clear();
    current= min_path1(i, l);
    if(l< l_min){
      min= current;
      l_min= l;
    }
  }

  return min;
}

int graph::nearest_city(int i, double &min_dist){
  int j, n= ciudades.size();
  set<pair<double, int> > posibilidades;
  set<pair<double, int> >::iterator it;

  min_dist= 0;

  for(j= 0; j< n; j++){
    //Si estamos en el triángulo superior de la matriz de adyacencia
    if(!visited[j]){
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


vector<int> graph::min_path1(int i, double &l){
  int n= cities.size(), j;
  l= 0;
  assert( i >= 0 && i < n);

  double min_dist;
  vector<int> r;

  //Mientras haya ciudades por recorrer
  while(!finished_path()){
    //Añadimos la ciudad destino a la lista de ciudades recorridas
    r.push_back(i);
    visited[i]= true;

    j= nearest_city(i, min_dist);
    //Sumamos la distancia a la cantidad de camino recorrido
    l += min_dist;

    //Nos situamos en la ciudad destino y buscamos desde ahí el mínimo camino a la siguiente que no haya sido recorrida
    i= j;
  }
  close_path(r, l);

  return r;
}

int graph::westernmost_city(){
  double x=LONG_MAX;
  int index;

  for(int i=0; i<cities.size(); i++)
    if( cities[i].first < x ){
      x=cities[i].first;
      index=i;
    }
  return index;
}

int graph::easternmost_city(){
  double x=-LONG_MAX;
  int index;
  for(int i=0; i<cities.size(); i++)
    if( cities[i].first > x ){
      x=cities[i].first;
      index=i;
    }
  return index;
}

int graph::northernmost_city(){
  double x=-LONG_MAX;
  int index;
  for(int i=0; i<cities.size(); i++)
    if( cities[i].second > x ){
      x=cities[i].second;
      index=i;
    }
  return index;
}

double graph::total_weight(vector<int> path){
  double l=0;
  for(int i=0; i<path.size()-1; i++){
    l+=get_weight(path[i], path[i+1]);
  }
  //Para cerrar el camino
  close_path(path, l);
  return l;
}

//Devuelve el indice <i> tal que al inserta la ciudad <x> el camino es el minimo
pair<int, double> graph::particular_min(vector<int>& path, int x){
  double aux=0, min=LONG_MAX;
  int index;

  for(int i=0; i<=path.size(); i++){
    path.insert(path.begin()+i, x);

    aux=total_weight(path);
    if( aux<min ){
      index=i;
      min=aux;
    }

    path.erase(path.begin()+i);
  }

  return make_pair(index, min);
}

//Devuelve un par <i,j> donde 'i' es el indice de la ciudad a insertar
//y 'j' es la posicion de 'r' tal que al insertar 'i' en 'j' el incremento
//del camino es minimo
pair<int, int> graph::general_min(vector<int> &r){

  set<pair<double,pair<int, int> > >posibilities;
  pair<int, double> aux;

  for(int i=0; i<cities.size(); i++){
    if( !visited[i] ){
      aux=particular_min(r, i);
      posibilities.insert( pair<double,pair<int, int> >( aux.second, make_pair(i, aux.first) ) );
    }
  }

  return make_pair( (*posibilities.begin()).second.first, (*posibilities.begin()).second.second );

}

//Calcula el camino minimo de un grafo utilizando un triangulo
//formado por las ciudades mas al oeste, este y sur
vector<int> graph::min_path2(int i, double &l){
  clear();
  vector<int> r;

  r.push_back( westernmost_city() );
  r.push_back( easternmost_city() );
  r.push_back( northernmost_city() );

  visited[r[0]]=true; visited[r[1]]=true; visited[r[2]]=true;

  pair<int, int> new_node;
  while( r.size() < cities.size() ){
    new_node = general_min(r);
    visited[new_node.first]=true;
    r.insert(r.begin()+new_node.second, new_node.first);
  }

  l=total_weight(r);
  return r;

}

vector<int> graph::min_path3(int i, double &l){
  clear();
  vector<int> r;

  set<pair<double, int> > posibilities;
  for(int j=0; j<cities.size(); j++)
    if(i!=j) posibilities.insert(make_pair( get_weight(i,j) , j) );

  r.push_back(i);
  r.push_back( (*posibilities.begin()).second );
  r.push_back( (*(++posibilities.begin())).second );

  visited[r[0]]=true; visited[r[1]]=true; visited[r[2]]=true;

  pair<int, int> new_node;
  while( r.size() < cities.size() ){
    new_node = total_min(r);
    visited[new_node.first]=true;
    r.insert(r.begin()+new_node.second, new_node.first);
  }

  l=total_weight(r);
  return r;
}

#endif
