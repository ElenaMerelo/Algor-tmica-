/*
Enunciado: Se va a celebrar una cena de gala a la que asistirán n invitados.
Todos se van a sentar alrededor de una única gran mesa rectangular, de forma que
cada invitado tendrá sentados junto a él a otros dos comensales (uno a su izquierda
y otro a su derecha). En función de las caracterı́sticas de cada invitado (por ejemplo categorı́a
o puesto, lugar de procedencia,...) existen unas normas de protocolo que
indican el nivel de conveniencia de que dos invitados se sienten en lugares
contiguos (supondremos que dicho nivel es un número entero entre 0 y 100). El
nivel de conveniencia total de una asignación de invitados a su puesto en la mesa es la suma
de todos los niveles de conveniencia de cada invitado con cada uno de los dos
invitados sentados a su lado.
Se desea sentar a los invitados de forma que el nivel de conveniencia global sea lo mayor posible. Diseñar
e implementar un algoritmo vuelta atrás para resolver este problema. Realizar un estudio empı́rico de su
eficiencia.*/

#include "matriz_de_conveniencia.cpp"
using namespace std;

int main(int argc, char **argv){
  struct timespec cgt1, cgt2;
  double ncgt;  //para tiempo de ejecución

  if(argc != 2){
    cout << "\nNúmero de argumentos incorrecto";
    exit(-1);
  }

  int n= atoi(argv[1]), max_conv;
  matriz_de_conveniencia m(n);
  vector<int> v, f;

  clock_gettime(CLOCK_REALTIME, &cgt1);
  max_conv=  m.max_nivel_conv(v);
  clock_gettime(CLOCK_REALTIME, &cgt2);

  cout << "\nEl máximo nivel de conveniencia es: " << m.max_nivel_conv(v);
  cout << "\nNúmero de soluciones calculadas: " << m.get_num_soluciones();
  f= m.get_solucion();
  cout << "\nPara ello los invitados han de estar sentados en el orden: ";
  for(int i= 0; i< f.size(); i++)
    cout << f[i] << " ";

  ncgt= (double)(cgt2.tv_sec - cgt1.tv_sec) + (double) ((cgt2.tv_nsec - cgt1.tv_nsec) / (1.e+9));
  cout << "\nTiempo de ejecución: " << ncgt;
}
