/*
 * Regresa un posible padre con altas probabilidades de ser apto
 * (pero podria no serlo)
 * esto es usando el producto y distribucion de probabilidad uniforme
 * para simular una sociedad elitista donde los mas aptos se juntan con los mas aptos
 * pero que existan excepciones.
 *
 * La funcion de probabilidad se comporta de tal manera que de 100  escogidos
 * siempre mas del 50% de las veces seran el 25% de los mas aptos
 */

#include "bevolucion.h"
celula
padre_aleatorio_apto (celula * poblacion, int32_t habitantes)
{

/* Como toda la poblacion estara organizada en orden del mas apto al menos apto
 * y el mas apto esta cercano a 0 con respecto a un gen elite
 * entonces  RAND*RAND*(TAMANO-1) me dara numeros aleatorios con mas probabilidad
 * de estar cerca de 0 pero sin perder la entropia, por lo que esto
 * simulara una sociedad donde se reproducen las personas "mayormente" en igualdad
 * de "elitismo" , esto es aprovechando que es una distribucion de producto uniforme
 * con respecto al valor de aptitud, y en palabras burdas.
 * un numero aleatorio tiene la misma probabilidad de salir en un universo uniforme
 * y el producto de dos numeros aleatorios tiene la probabilidad de ser un numero
 * grande.
 *
 * Y entre 0 y 1 reales , el producto de dos aleatorios, tiene la probabilidad
 * de ser chico, y escalado con el tamanio de la poblacion, dara numeros
 * bajor con mayor probabilidad y aleatorios
 */

  int32_t index =
    (int32_t) (rand_double1 () * rand_double1 () * (habitantes - 1));


  return poblacion[index];
}
