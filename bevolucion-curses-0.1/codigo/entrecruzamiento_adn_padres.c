/*
 * Produce un hijo dados dos padres con distintos genes
 * este puede tener n=mutacion bases nitrogenadas mutadas
 * en el gen de referencia localizado en el cromosoma gCromo_ref y gen gGen_ref
 */
#include "bevolucion.h"

extern int32_t poblacion_nacida;

/* Al reproducirse generaremos una nueva celula con aproximadamente la mitad de genes del padre y madre */
celula *
entrecruzamiento_adn_padres (celula * padre, celula * madre, celula * hijo,
			     int8_t mutacion)
{
  int32_t i, j, r;
/* el hijo tiene el mismo numero de genes y cromosomas que los padres */

  memset (hijo, 0x0, sizeof (celula));

  hijo->num_cromo = padre->num_cromo;
  hijo->num_genes = padre->num_genes;


/* Identidad := {padre20}{madre20}{rand4}{ p ^ m  20}  */
/* La info unica de la celula esta dada por los ultimos 20 bits de su identidad, lo demas es info reservada y de los padres */
  hijo->padre = padre->identidad & 0x00000000000FFFFF;
  hijo->madre = madre->identidad & 0x00000000000FFFFF;



/* Metemos los datos del padre y madre en su identidad en los primeros 32 bits (16 y 16) */
  hijo->identidad =
    ((padre->identidad << 44) & 0xFFFFF00000000000) |
    ((madre->identidad << 24) & 0x00000FFFFF000000);

/* Metemos un idenficiador random en la posicion 40bit a 48 por si dos padres tienen varios hijos*/

  hijo->identidad |= (int64_t) (rand_int (0x0f) << 16);

/* Metemos el XOR del padre e hijo como parte de su identidad en los ultimos 20 bits (ultimos 20 bits de ambos) */

  hijo->identidad |= hijo->padre ^ hijo->madre;

/* Metemos al final de su identidad la suma de los hijos que han tenido los padres previamente */

  hijo->identidad += padre->num_hijos + madre->num_hijos + poblacion_nacida;

poblacion_nacida ++;


/* Insertamos la identidad del nuevo hijo en ambos padres en la posicion final o inicial si es 0*/

  padre->hijos[padre->num_hijos == 0 ? 0 : padre->num_hijos - 1] =
    hijo->identidad;

  madre->hijos[madre->num_hijos == 0 ? 0 : madre->num_hijos - 1] =
    hijo->identidad;

  padre->num_hijos++;
  madre->num_hijos++;



  for (i = 0; i < hijo->num_cromo; i++)
    for (j = 0; j < hijo->num_genes; j++)
      {
	r = rand_int (2);
	if (r)
	  hijo->cromosomas[i].molecula_adn.genes[j] =
	    padre->cromosomas[i].molecula_adn.genes[j];
	else
	  hijo->cromosomas[i].molecula_adn.genes[j] =
	    madre->cromosomas[i].molecula_adn.genes[j];

      }
  if (mutacion > 0)
    muta_genoma_celula (hijo, mutacion);

  inserta_adaptacion_gen_elite (hijo);

  return hijo;
}
