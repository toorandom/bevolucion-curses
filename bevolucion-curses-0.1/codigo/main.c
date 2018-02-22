/*
 * Aqui se implementa el algoritmo que se ve en el LEEME.txt
 */


#include "bevolucion.h"

extern int32_t poblacion_nacida;
int
main (int argc, char **argv)
{

  celula *poblacion, hijo;
  celula padre, madre, menos_apto;
  char *gs, *elite_str;
  int32_t ncromo = 4, ngenes = 10, habitantes = 25, pares_bases_x_gen = 35;
  int32_t cromosoma_referencia = rand_int (ncromo);
  int32_t gen_referencia = rand_int (ngenes) ;
  int32_t si_se_integro;
  int32_t generacion = 0;
/* INICIA CURSES */
  WINDOW *principal, *secundaria, *secundaria2;
  int startx, starty, width, height;
  int ch, i;

  initscr ();			/* Start curses mode            */
  cbreak ();			/* Line buffering disabled, Pass on
				   //  * everty thing to me           */
  keypad (stdscr, TRUE);	/* I need that nifty F1         */
  start_color ();
  height = habitantes +1 ;
  width = COLS;
  starty = 1;			/* Calculating for a center placement */
  startx = 1;			/* of the window                */
  refresh ();
  principal = create_newwin (height, width, starty, startx);
  secundaria = create_newwin (4, width, starty + height, startx);
  secundaria2 = create_newwin (3, width, starty + height + 5, startx);
  scrollok (principal, TRUE);
  scrollok (secundaria, TRUE);
  scrollok (secundaria2, TRUE);

/* FIN CURSES */




  gen gen_elite_referencia = gen_aleatorio (pares_bases_x_gen);

  poblacion_nacida = 0;

  gCromo_ref = cromosoma_referencia;
  gGen_ref = gen_referencia;
  gGen_elite = gen_elite_referencia;


  srand (getpid () * getpid ());

  poblacion =
    genera_poblacion_genes_aleatorios (ncromo, ngenes,
				       pares_bases_x_gen, habitantes);
  elite_str = (char *) gen_string (gGen_elite);

//  printf
//    ("El gen_elite=%s sera el objetivo evolutivo en la poblacion a la hora de reproducirse entre 'probablemente' los mas aptos\n\n",

  //    elite_str);


/* Mientras el mas adaptado de la poblacion (el primero de la jerarquia) no este completamente adaptado al gen_elite */
  while (adaptacion (poblacion[0]) != 0)
    {

      jerarquiza_poblacion_mas_aptos (poblacion, habitantes);

/* Escogemos dos padres con alta probabilidad de que se escojan "elite" (podrian no serlo para simular un escenario de la vida real */
      padre = padre_aleatorio_apto (poblacion, habitantes);
      madre = padre_aleatorio_apto (poblacion, habitantes);

/* No queremos que se escoja el mismo padre y madre*/
      while (padre.identidad == madre.identidad)
	madre = padre_aleatorio_apto (poblacion, habitantes);

      wprintw
	(secundaria,
	 "Padres escogidos con probabilidad de mejor adaptacion a gen_elite para engendrar %016llx y %016llx\n",
	 padre.identidad, madre.identidad);

/* Cruzamos los padres 75% probabilidad de mutacion 2 pares del gen (ya que la mutacion modifica 1/4 y podria no modificarla)  , y obtenemos hijo */
      entrecruzamiento_adn_padres (&padre, &madre, &hijo, 2);
/* Vemos quien es el menos apto */


      menos_apto = poblacion[habitantes - 1];
/*
      wprintw
	(secundaria,"El menos apto es id=%016llx con adaptacion = %d y gen_referencia(cromo=%d,gen=%d)=%s!=%s\n",
	 menos_apto.identidad, adaptacion (menos_apto), gCromo_ref, gGen_ref,
	 gs =
	 (char *) gen_string (menos_apto.cromosomas[gCromo_ref].
			      molecula_adn.genes[gGen_ref]), elite_str);
*/
      wprintw
	(secundaria,
	 "Menos muere apto id=%016llx adapt:=%d y GRef(cromo=%d,gen=%d)=",
	 menos_apto.identidad, adaptacion (menos_apto), gCromo_ref, gGen_ref);
      base_color (gs =
		  (char *) gen_string (menos_apto.cromosomas[gCromo_ref].
				       molecula_adn.genes[gGen_ref]),
		  secundaria);
      wprintw (secundaria, "!=");
      base_color (elite_str, secundaria);
      wprintw (secundaria, "\n");

      free (gs);

/* Insertamos al hijo en la poblacion */
      si_se_integro =
	integra_celula_poblacion_si_apta (hijo, poblacion, habitantes);

if(!si_se_integro)
	continue;
/*
      if (!si_se_integro)
	wprintw
	  (secundaria,"El hijo de %016llx y %016llx fue menos adaptado (%d) que el menos adaptado (%016llx) [%d]\n",
	   padre.identidad, madre.identidad, adaptacion (hijo),
	   poblacion[habitantes - 1].identidad,
	   adaptacion (poblacion[habitantes - 1]));
*/
      //   else
      //wprintw (secundaria,"Hijo se adapto a la poblacion con id %016llx\n",
      //hijo.identidad);

/* Reorganizamos ya con el hijo insertado */
      jerarquiza_poblacion_mas_aptos (poblacion, habitantes);

      wprintw (secundaria,
	       "Generacion %d (intentando alcanzar gen elite ",generacion); 
       base_color(elite_str,secundaria);
      wprintw(secundaria," envejecio (muto 1/5)\n");

      //     muestra_poblacion (poblacion, habitantes, cromosoma_referencia,
      //               gen_referencia, gen_elite_referencia, principal);
      generacion++;

/* Mutamos ADN (genes) de  1/3 de la poblacion menos adaptada 1 par de bases nitrogenadas por envejecimiento
 * despues de una generacion 
 */

      muta_poblacion_envejecimiento (poblacion, habitantes, habitantes / 5,
				     2);
      //wprintw
      //(secundaria,"Poblacion despues de que se afecto el ADN por envejecimiento de 1/3 de la poblacion menos adaptada por una base nitrogenada\n");
      jerarquiza_poblacion_mas_aptos (poblacion, habitantes);
      muestra_poblacion (poblacion, habitantes, cromosoma_referencia,
			 gen_referencia, gen_elite_referencia, principal);

      wrefresh (secundaria);
    //  wrefresh (principal);
    }

  jerarquiza_poblacion_mas_aptos (poblacion, habitantes);
  muestra_poblacion (poblacion, habitantes, cromosoma_referencia,
		     gen_referencia, gen_elite_referencia, principal);

  wprintw
    (secundaria2,
     "Se alcanzo el gen elite %s por celula id=%016llx con padres %016llx y %016llx en la generacion %d\n",
     elite_str, poblacion[0].identidad, padre.identidad, madre.identidad,
     generacion);
  wprintw (secundaria2,
	   "Preguntas, comentarios, Eduardo Ruiz Duarte, rduarte@ciencias.unam.mx (beck)\n");
  wrefresh (secundaria2);
  muestra_poblacion (poblacion, habitantes, cromosoma_referencia,
		     gen_referencia, gen_elite_referencia, principal);
  wrefresh (principal);
  free (elite_str);
  extermina_poblacion (poblacion);
  sleep (60);
  // destroy_win(principal);
  // destroy_win(secundaria);
  return 0;
}
