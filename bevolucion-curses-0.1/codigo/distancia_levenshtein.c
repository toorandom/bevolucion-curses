/*
 * Funcion para calcular la distancia de levenshtein
 * esta es usada por aptitud_gen_levenshtein()
 */
#include "bevolucion.h"
uint32_t
distancia_levenshtein (uint8_t * s1, uint32_t t1, uint8_t * s2, uint32_t t2)
{
  uint32_t x, y;
  uint32_t matrix[t2 + 1][t1 + 1];
  matrix[0][0] = 0;
  for (x = 1; x <= t2; x++)
    matrix[x][0] = matrix[x - 1][0] + 1;
  for (y = 1; y <= t1; y++)
    matrix[0][y] = matrix[0][y - 1] + 1;
  for (x = 1; x <= t2; x++)
    for (y = 1; y <= t1; y++)
      matrix[x][y] =
        MIN3 (matrix[x - 1][y] + 1, matrix[x][y - 1] + 1,
              matrix[x - 1][y - 1] + (s1[y - 1] == s2[x - 1] ? 0 : 1));

  return (matrix[t2][t1]);
}
