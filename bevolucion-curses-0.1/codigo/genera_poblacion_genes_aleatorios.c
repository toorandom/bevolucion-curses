/*
 * Genera una poblacion con ciertos cromosomas, genes y pares de bases
 */
#include "bevolucion.h"
celula *
genera_poblacion_genes_aleatorios (uint16_t num_cromosomas,
                                   uint16_t num_genes,
                                   uint16_t num_pares_bases,
                                   uint16_t habitantes)
{
  int32_t i, j, k, w;
  celula *poblacion = organismos_alloc (habitantes);

  printf ("Generando poblacion aleatoria\n");

  for (k = 0; k < habitantes; k++)
    {
      poblacion[k].num_cromo = num_cromosomas;
      poblacion[k].num_genes = num_genes;
      poblacion[k].identidad = k;
      /* La identidad del padre en los primeros 20 bits, madre en los segundos 20 bits, FFFFF,FFFFF porque ellos no fueron hijos de nadie */
      poblacion[k].identidad |= 0xFFFFFFFFFF000000;



      poblacion[k].padre = poblacion[k].madre = 0xFFFFF;

      for (i = 0; i < num_cromosomas; i++)
        for (j = 0; j < num_genes; j++)
          {

            poblacion[k].cromosomas[i].molecula_adn.genes[j].tamano =
              num_pares_bases;
            for (w = 0; w < num_pares_bases; w++)
              poblacion[k].cromosomas[i].molecula_adn.genes[j].par_bases[w] =
                pares_bases_adn[rand_int (4)];
          }
      inserta_adaptacion_gen_elite (&poblacion[k]);
    }
  return poblacion;
}
