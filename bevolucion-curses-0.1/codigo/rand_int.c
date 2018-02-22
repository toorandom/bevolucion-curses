/*
 * Numero al azar entre 0 y max
 */
#include "bevolucion.h"
int32_t
rand_int (int max)
{
  srand (getpid () + time (NULL) + rand_state);
  rand_state = rand ();
  return rand () % max;
}
