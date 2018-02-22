/*
 * Numero al azar entre [0,1]
 */
#include "bevolucion.h"

double
rand_double1 ()
{
  srand (getpid () + time (NULL) + rand_state);
  rand_state += rand () + rand_int (0xffff);
  return (float) rand () / (float) (RAND_MAX);
}
