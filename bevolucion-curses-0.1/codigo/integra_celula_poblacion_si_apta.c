/*
 * Integra una celula 'nueva' a una poblacion, esta podria no integrarse en caso
 * de que al nacer sea menos apta que el menos apto de la poblacion
 */
#include "bevolucion.h"
int32_t
integra_celula_poblacion_si_apta (celula nueva, celula * poblacion,
				  int32_t habitantes)
{

  jerarquiza_poblacion_mas_aptos (poblacion, habitantes);
/* Entre mas grande el coeficiente de adaptacion (lejano de 0) menos adaptado */
  if (adaptacion (poblacion[habitantes - 1]) >= adaptacion (nueva))
    {
/*
           memcpy (&poblacion[habitantes - 1 ], &nueva,
            sizeof (celula));
*/
      poblacion[habitantes - 1] = nueva;

      /* reorganizamos la poblacion con los menos aptos hasta abajo */

      jerarquiza_poblacion_mas_aptos (poblacion, habitantes);
      return 1;
    }
  /* reorganizamos la poblacion con los menos aptos hasta abajo */
  jerarquiza_poblacion_mas_aptos (poblacion, habitantes);

  return 0;

}
