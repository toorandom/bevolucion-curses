/*
 * Organiza la poblacion de tal manera ascendente donde el de indice=0 es el mayor adaptado
 * con respecto al gen elite, la celula poblacion[num_hab-1] es el menos adaptado
 * el cual tiene altas probabilidades de morir
 */
#include "bevolucion.h"
void
jerarquiza_poblacion_mas_aptos (celula * poblacion, int32_t num_hab)
{

  int i, j, min;
  celula t;

  for (i = 0; i < num_hab - 1; ++i)
    {
      min = i;
      for (j = i + 1; j < num_hab; ++j)
        {
          if (adaptacion (poblacion[j]) < adaptacion (poblacion[min]))
            min = j;
        }
/*
      memcpy (&t, &poblacion[i], sizeof (celula));
      memcpy (&poblacion[i], &poblacion[min], sizeof (celula));
      memcpy (&poblacion[min], &t, sizeof (celula));
*/
      t = poblacion[i];
      poblacion[i] = poblacion[min];
      poblacion[min] = t;
    }
}
