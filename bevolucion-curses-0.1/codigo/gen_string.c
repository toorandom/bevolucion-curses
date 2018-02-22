/*
 * Regresa el gen en formato de palabra para imprimirse
 */
#include "bevolucion.h"
int8_t *
gen_string (gen g)
{
  int8_t *gs;
  int32_t i;
  //int8_t blanco[] = "\033[01;37m";
  int8_t blanco[] = "";

  gs = calloc (sizeof (int8_t), 10*MAX_NUC_GEN);
  for (i = 0; i < g.tamano; i++)
	strcat((char *)gs,nombre_par_base(g.par_bases[i]));
   // memcpy (gs + (i*strlen(blanco)), nombre_par_base (g.par_bases[i]), strlen(blanco)-1);
  strcat((char *)gs,(char *)blanco);
 // memcpy(gs+ ((i+1)*strlen(blanco)), &blanco,strlen(blanco));
 // write(1,gs,10*20);
  return gs;
}
