Si la cota superior es menor que el mejor valor conocido en una
región, no puede existir un óptimo global en el subespacio de la región
factible asociada a ese nodo, por lo que puede ser eliminado
para posteriores consideraciones.

La búsqueda sigue hasta que se eliminan o podan todos los nodos
Estimación del beneficio- media de la cota superior e inferior. Ayuda a
decidir qué parte del árbol evaluar primero.

# Estrategia de poda

> Caso 1

Si a partir de un nodo siempre podemos obtener solución válida, entonces podar
nodo i  CS(i) <= CI(j) para algún nodo generado j.

> Caso 2

Si a partir de un nodo puede que no lleguemos a una solución válida, entonces
podemos podar un nodo i si CS(i) <= beneficio (j) para algún j solución final factible.

La lista de nodos puede ser una cola, en cuyo caso el recorrido es en anchura, o bien una pila, con recorrido en profundidad. Usando la estimación del beneficio, lo mejor será buscar por los nodos con mayor valor estimado.

La estrategia Least Cost elige, entre todos los nodos de la lista de nodos vivios, el que tenga mayor beneficio o menor coste para explorar a continuación. En caso de empate(de beneficio o coste estimado) deshacerlo usando un criterio LIFO o FIFO (LC-FIFO seleccion de la lnv el que tenga mayor beneficio y en caso de empate escoge el primero que se introdujo, LC-LIFO escoge el último que se introdujo en caso de empate).












#
