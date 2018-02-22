/*
 * Te calcula la aptitud de un gen con respecto a la distancia de levenshtein
 * esta es usada para complementar aptitud_gen()
 *
 */
#include "bevolucion.h"
extern uint8_t pares_bases_adn[4];
extern uint8_t pares_bases_arn[4];

uint32_t
aptitud_gen_levenshtein (gen gen_inicial, gen gen_elite)
{
  uint32_t apt;
  uint8_t *gi = (uint8_t *) & gen_inicial.par_bases;
  uint8_t *ge = (uint8_t *) & gen_elite.par_bases;


  apt = distancia_levenshtein (gi, gen_inicial.tamano, ge, gen_elite.tamano);
  return apt;
}
