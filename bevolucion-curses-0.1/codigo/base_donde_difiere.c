/*
 * Esto solo regresa la base nitrogenada donde diferen dos genes en forma de strings
 */
#include "bevolucion.h"
uint8_t
base_donde_difieren (uint8_t * g1, uint8_t s1, uint8_t * g2, uint8_t s2)
{
  int32_t i;
  int32_t min;
  uint8_t ret = 0;

  min = s1 <= s2 ? s1 : s2;

  for (i = 0; i < min; i++)
    if (g1[i] != g2[i])
      ret = g1[i];
  return ret;

}
