/*
 * Genera un gen aleatorio con n=num_pares pares de bases nitrogenadas
 */

#include "bevolucion.h"
gen
gen_aleatorio (int32_t num_pares)
{
  gen g;
  int32_t i;
  for (i = 0; i < num_pares; i++)
    g.par_bases[i] = pares_bases_adn[rand_int (4)];
  g.tamano = num_pares;
  return g;
}
