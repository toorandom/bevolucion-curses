/*
 * Muta todo el genoma de una celula, es decir , cambia n=max_bases_mutar bases nitrogenadas
 * si n=1 existe 1/4 de probabilidad de no cambiar nada
 */
#include "bevolucion.h"
/* muta una base nitrogenada de cada gen */
void
muta_genoma_celula (celula * cel, uint8_t max_bases_mutar)
{
  int32_t i, j, k, num_pares_en_gen;


  for (i = 0; i < cel->num_cromo; i++)
    for (j = 0; j < cel->num_genes; j++)
      {
        num_pares_en_gen = cel->cromosomas[i].molecula_adn.genes[j].tamano;
        for (k = 0; k < max_bases_mutar; k++)
          cel->cromosomas[i].molecula_adn.genes[j].
            par_bases[rand_int (num_pares_en_gen)] =
            pares_bases_adn[rand_int (4)];
      }
  return;
}
