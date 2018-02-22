/*
 * Inserta el grado de adaptacion con respecto al gen elite definido de manera global como gGen_elite.
 * dentro de la celula para mejor manejo
 */

#include "bevolucion.h"

void
inserta_adaptacion_gen_elite (celula * hijo)
{

  int32_t cr = gCromo_ref;
  int32_t gr = gGen_ref;
  gen ge = gGen_elite;

  hijo->cromosomas[cr].molecula_adn.genes[gr].aptitud =
    aptitud_gen (hijo->cromosomas[cr].molecula_adn.genes[gr], ge);
  return;

}
