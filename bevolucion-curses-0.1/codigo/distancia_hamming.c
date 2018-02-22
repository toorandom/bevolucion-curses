/*
 * Distancia de hamming en dos strings de tamanio igual
 */
#include "bevolucion.h"
uint32_t
distancia_hamming (uint8_t * a, uint8_t * b, int32_t na)
{

  uint32_t d = 0;
  while (na)
    {
      if (*a != *b)
        ++d;

      --na;
      ++a;
      ++b;
    }

  return d;
}
