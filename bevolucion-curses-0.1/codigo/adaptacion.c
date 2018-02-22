#include "bevolucion.h"
extern uint8_t pares_bases_adn[4];
extern uint8_t pares_bases_arn[4];

/* Regresa el grado de adaptacion con respecto al gen elite */
int32_t
adaptacion (celula t)
{
  int32_t cr = gCromo_ref;
  int32_t gr = gGen_ref;
  return t.cromosomas[cr].molecula_adn.genes[gr].aptitud;
}

