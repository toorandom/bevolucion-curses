/*
 * Solo destruye la memoria alojada para una poblacion de celulas
 */
#include "bevolucion.h"
/* Nombre fancy */
void
extermina_poblacion (celula * poblacion)
{
  free (poblacion);
}
