/*
 * Imprime toda la poblacion con ciertas caracteristicas
 */
#include "bevolucion.h"

void
muestra_poblacion (celula * poblacion, uint16_t habitantes, int16_t cromo_ref,
		   int16_t gen_ref, gen gen_elite, WINDOW *win)
{
  int32_t i, j, k, w,c,ca;
  gen gen_actual;
  int8_t *gen_str;
refresh();
  
  for (k = 0; k < habitantes; k++)
    for (i = 0; i < poblacion[k].num_cromo; i++)
      for (j = 0; j < poblacion[k].num_genes; j++)
	if ((i == cromo_ref) && (j == gen_ref))
	  {
	    wprintw
	      (win,"celula[indice=%02d]{id=%016llx}->cromosoma[%02d]->gen[%02d] = ",
	       k, poblacion[k].identidad, i, j);
	    gen_actual = poblacion[k].cromosomas[i].molecula_adn.genes[j];
	    gen_str = gen_string(gen_actual);
	    wprintw(win,"{");
            base_color((char *)gen_str,win);
            wprintw(win,"}");
/*
	    for (w = 0; w < gen_actual.tamano; w++)
	      printf ("%s", nombre_par_base (gen_actual.par_bases[w]));
*/
	    wprintw
	      (win,"cercania adaptacion gen_elite(%d,%d): ",
	       cromo_ref, gen_ref);
	c = gen_actual.aptitud;

   if(c<1000) ca=COLOR_BLUE;
   else if(c>1000 && c < 5000) ca=COLOR_GREEN;
   else if(c>5000) ca=COLOR_RED;
   c=10;
	//	wattron(win,gen_actual.aptitud);
		init_pair(c, ca  ,COLOR_BLACK);
		wattron(win,COLOR_PAIR(c));
                wprintw(win,"%d\n", gen_actual.aptitud);
		wattroff(win,COLOR_PAIR(c));
	//	wattroff(win,gen_actual.aptitud);
	  }
wrefresh(win);
//  wprintw (win,"\n");
}
