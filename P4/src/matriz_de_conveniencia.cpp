#include <iostream>
#include <stdlib.h> //srand, rand
#include <time.h> //time
#include <vector>
#include <algorithm> //count

using namespace std;

class matriz_de_conveniencia{
private:
  vector<vector<int> > m;
  vector<int> solucion;
  int num_soluciones, max_conv, conv;

public:
  //Crea una matriz n*n con enteros aleatorios y la diagonal principal rellena de ceros
  matriz_de_conveniencia(int n){
    int i, j;
    //Inicializamos la semilla para generar los números aleatorios
    srand(time(NULL));
    num_soluciones= 0; max_conv= 0; conv= 0;

    m.resize(n);

    for(i= 0; i< n; i++)
      m[i].resize(n);

    for(i= 0; i< n ; i++)
      for(j= 0; j< n; j++)
        m[i][j]= i != j? rand() % 100: 0; //el número generado es un entero entre 0 y 100

  }

  vector<int> get_solucion(){
    return solucion;
  }

  int get_num_soluciones(){
    return num_soluciones;
  }

  int conveniencia_total(vector<int> v){
    int sum= 0, n= v.size();

    for(int i= 1; i<n-1; i++)
      sum+=m[ v[i] ][ v[i+1] ] + m[ v[i] ][ v[i-1] ];

    sum+=m[ v[n-1] ][ v[n-2] ] + m[ v[n-1] ][ v[0] ];
    sum+=m[ v[0] ][ v[1] ] + m[ v[0] ][ v[n-1] ];

    return sum;
  }

  //Comprueba si el invitado x ya ha sido considerado
  bool sentado(vector<int> v, int x){
    return count(v.begin(), v.end(), x) == 1;
  }

  vector<int> aux(vector<int> v, int n){
    vector<int> result;
    for(int i= 0; i< n; i++)
      if(!sentado(v, i))
        result.push_back(i);

    return result;
  }

  int max_nivel_conv(vector<int> &v){
    vector<int> por_sentar= aux(v, m.size());

    for(int i= 0; i< por_sentar.size(); i++){
      v.push_back(por_sentar[i]);

      if(v.size() == m.size())
        num_soluciones++;

      conv= conveniencia_total(v);

      if(conv > max_conv){
        max_conv= conv;
        solucion= v;
        max_nivel_conv(v);
      }

      v.pop_back();
    }
    return max_conv;
  }
};
