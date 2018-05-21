#!/bin/csh
@ inicio = 0
@ fin = 15
@ incremento = 1
@ i = $inicio
echo > tiempos_backtracking.dat
while ( $i <= $fin )
  echo Ejecución tam = $i
  echo `../bin/main $i` >> tiempos_backtracking.dat
  @ i += $incremento
end
