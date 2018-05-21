#include "tsp.h"

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


bool matriz_de_adyacencia::recorrido_terminado(){
  return count(visitadas.begin(), visitadas.end(), false) == 0;
}

void matriz_de_adyacencia::clear(){
  visitadas.clear();
  visitadas.resize(m.size(), false);
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
  }
  visitadas.resize(num_cities, false);
  rellenar_matriz(ciudades);
  flujo.close();
}

void matriz_de_adyacencia::show_matrix(){
  for(unsigned int i= 0; i< m.size(); i++){
    for(unsigned int j= 0; j< m.size(); j++)
    cout << m[i][j] << " ";
    cout << "\n";
  }
}

void matriz_de_adyacencia::show_path(vector<int> v, double longitud){
  cout << "Peso: " << longitud << ", recorrido: ";
  for(unsigned int i= 0; i< v.size(); i++)
    cout << v[i] << " ";
  }

int matriz_de_adyacencia::ciudad_mas_cercana(int i, double &min_dist){
  int j, n= ciudades.size();
  set<pair<double, int> > posibilidades;
  set<pair<double, int> >::iterator it;

  min_dist= 0;

  for(j= 0; j< n; j++){
    //Si estamos en el triángulo superior de la matriz de adyacencia
    if(!visitadas[j]){  //si no forma ciclo
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

  vector<int> matriz_de_adyacencia::min_path(int i, double &longitud){
  int j;
  longitud= 0;

  double min_dist;
  vector<int> r;

  //Mientras haya ciudades por recorrer
  while(!recorrido_terminado()){
    //Añadimos la ciudad destino a la lista de ciudades recorridas
    r.push_back(i);
    visitadas[i]= true;

    j= ciudad_mas_cercana(i, min_dist);
    //Sumamos la distancia a la cantidad de camino recorrido
    longitud += min_dist;

    //Nos situamos en la ciudad destino y buscamos desde ahí el mínimo camino a la siguiente que no haya sido recorrida
    i= j;
  }
  return r;
}

vector<int> matriz_de_adyacencia::cierra_camino(vector<int> recorrido, double &longitud){
  vector<int> f= recorrido;
  int j= recorrido.back(), i= recorrido.front();

  if(i > j)
    longitud += m[j][i];
  else
    longitud += m[i][j];

  f.push_back(i);
  return f;
}

vector<int> matriz_de_adyacencia::recorrido_optimo(double &longitud_min){
  double longitud;
  longitud_min= LONG_MAX;
  vector<int> actual, min;

  for(unsigned int i= 0; i< m.size(); i++){
    longitud= 0;
    clear();
    actual= min_path(i, longitud);
    if(longitud< longitud_min){
      min= actual;
      longitud_min= longitud;
    }
  }
  return min;
}

vector<int> matriz_de_adyacencia::vector_suplementario(vector<int> v){
  vector<int> r;
  for(int i= 0; i< m.size(); i++)
    if(count(v.begin(), v.end(), i) == 0)
      r.push_back(i);

  return r;
}

double matriz_de_adyacencia::coste_camino(vector<int> c){
  double peso= 0;
  for(int i= 0; i< c.size() -1; i++){
    if(c[i] > c[i+1])
      peso += m[c[i+1]][c[i]];
    else
      peso += m[c[i]][c[i+1]];
  }
  return peso;
}

double matriz_de_adyacencia::coste_posible(vector<int> nodos_recorridos){
  double coste_total= coste_camino(nodos_recorridos), coste_min= LONG_MAX, coste_actual;
  vector<int> fila= vector_suplementario(nodos_recorridos), columna= fila;


  fila.push_back(nodos_recorridos.back());
  columna.push_back(nodos_recorridos.front());

  for(int i= 0; i< fila.size(); i++){
    for(int j= 0; j< columna.size(); j++){
      if(i > j)
        coste_actual = m[columna[j]][fila[i]];
      else
        coste_actual = m[fila[i]][columna[j]];

      if(coste_actual < coste_min)
        coste_min= coste_actual;

    }
    coste_total += coste_min;
    coste_min= LONG_MAX;
  }
  return coste_total;
}

vector<nodo> matriz_de_adyacencia::nivel_siguiente(vector<int> nodos){
  vector<nodo> v;
  vector<int> w= nodos, sup= vector_suplementario(w);

  for(int j= 0; j< sup.size(); j++){
    w.push_back(sup[j]);
    v.push_back(make_pair(coste_posible(w), w));
    w.pop_back();
  }

  return v;
}


/*
vector<int> matriz_de_adyacencia::branch_and_bound(vector<int> &recorrido){
  vector<nodo> nodos= nivel_siguiente(recorrido);
  set<nodo> posibilidades(nodos.begin(), nodos.end());

  //El set los coloca de menor coste posible a mayor, luego el mejor nodo para expandir es el primer elemento del mismo

  branch_and_bound()


*/











//
