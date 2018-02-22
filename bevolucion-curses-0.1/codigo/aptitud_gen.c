/* 
 * Calcula que tan apto es un gen con respecto a un gen elite
 */
#include "bevolucion.h"
uint32_t
aptitud_gen (gen gen_inicial, gen gen_elite)
{
  uint32_t apt = 0, i;
  for (i = 0; i < gen_elite.tamano; i++)
    apt +=
      (gen_elite.par_bases[i] -
       gen_inicial.par_bases[i]) * (gen_elite.par_bases[i] -
                                    gen_inicial.par_bases[i]);
  gen_inicial.aptitud = apt;
  apt +=
    aptitud_gen_levenshtein (gen_inicial,
                             gen_elite) +
    strncmp ((char *) gen_inicial.par_bases, (char *) gen_elite.par_bases,
             gen_elite.tamano);

  apt +=
    base_donde_difieren (gen_inicial.par_bases, gen_inicial.tamano,
                         gen_elite.par_bases, gen_elite.tamano);


  apt +=
    distancia_hamming (gen_inicial.par_bases, gen_elite.par_bases,
                       gen_elite.tamano);

  return apt >= 0 ? apt : -1 * apt;
}
