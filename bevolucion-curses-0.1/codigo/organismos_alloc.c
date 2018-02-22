/*
 * Aloja memoria para la poblacion
 *
 */
#include "bevolucion.h"
void *
organismos_alloc (uint16_t num)
{

  void *ptr;
  ptr = calloc (sizeof (celula), num);
  if (ptr == NULL)
    {
      perror ("calloc");
      exit (EXIT_FAILURE);
    }
  return ptr;
}
