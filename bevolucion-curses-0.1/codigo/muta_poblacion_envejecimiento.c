/*
 * Muta parte de la poblacion mas debil (habitantes-debiles_a_mutar) por n=max_bases_mutar
 * si n=1 puede servir como envejecimiento despues de 1 generacion
 */
#include "bevolucion.h"
/* muta m=max_bases_mutar pares de bases en los mas debiles k=debiles_a_mutar de una poblacion p de n=habitantes  */
/* Es util el valor max_bases_mutar=1   y debiles_a_mutar=habitantes/3 para simular envejecimiento por generacion */

void
muta_poblacion_envejecimiento (celula * p, int32_t habitantes,
                               int32_t debiles_a_mutar,
                               uint8_t max_bases_mutar)
{
  int32_t i;
  if (debiles_a_mutar > habitantes)
    {
      printf
        ("ERROR: Definiste mas debiles a mutar que el total de la poblacion\n");
      exit (EXIT_FAILURE);
    }
/* Mutamos cada habitante, podria no mutar si se intercambia un par de bases con sigo misma si le toca al azar*/
  for (i = habitantes - debiles_a_mutar; i < habitantes; i++)
    muta_genoma_celula (&p[i], max_bases_mutar);
  return;
}
