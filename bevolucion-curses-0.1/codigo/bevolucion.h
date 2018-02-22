#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <ncurses.h>

#ifndef BEVOLUCION_H
#define BEVOLUCION_H


/* par_bases[k] es un par de bases nitrogenadas
 * de 8 bits
 *     Base1                 Base2
 * {b1, b2, b3, b4} <-> {b5, b6, b7, b8 } 
 *
 *  Adenina	1000     0x08
 *  Citosina	0100     0x04
 *  Guanina	0010     0x02
 *  Timina	0001     0x01 
 *
 *  Y en ARN
 *
 *  Uracilo     1111     0x0f
 *
 *  Las combinaciones entre Pirimidinas  y Purinas en ADN complementarias, por lo que 
 * 
 * Purinas = 	{ Adenina , Guanina }
 * Primidinas = { Citosina, Timina } U {Uracilo}    (Nota que en ARN no hay Timina)
 *
 * Por lo que las unicas combinaciones complementarias por par de bases en ADN son: 
 *
 * AT,TA := A,T ##  AT <- (1000<<4)|0001 , TA <- (0001<<4)|1000  ##  AT=(0x08<<4)|0x01 = 0x81 , TA=(0x01<<4)|0x08=0x18     (2 puentes de hidrogeno)
 * GC,CG := G,C ##  GC <- (0010<<4)|0100 , CG <- (0100<<4)|0010  ##  GC=(0x02<<4)|0x04 = 0x24 , CG=(0x04<<4)|0x02=0x42     (3 puentes de hidrogeno)
 *
 * En el ARN no hay Timina por lo que la complementariedad es 
 * AU,UA := A,U ## AU= (0x08<<4) | 0x0f = 0x8f , UA= (0x0f<<4)|0x08 = 0xf8      (2 puentes de hidrogeno)
 *
 */

/* Bases nitrogenadas */
#define Adenina     0x08
#define Citosina    0x04
#define Guanina     0x02
#define Timina      0x01
#define Uracilo     0x0f
/* ADN pares complementarios */
#define AT (int8_t)(Adenina<<4)|Timina
#define TA (int8_t)(Timina<<4) |Adenina
#define GC (int8_t)(Guanina<<4)|Citosina
#define CG (int8_t)(Citosina<<4)|Guanina
/* ARN pares complementarios */
#define AU (int8_t)(Adenina<<4)|Uracilo
#define UA (int8_t)(Uracilo<<4)|Adenina
/* Maximo nucleotidos por gen  (maximo de pares de bases nitrogenadas complementarias) */
#define MAX_NUC_GEN 50
/* Maximo numero de genes en el ADN */
#define MAX_GENES 50
/* Maximos hijos */
#define MAX_HIJOS 100
/* Maximo numero de cromosomas por celula */
#define MAX_CROMOSOMAS 46
/* Macro minimo entre 3 numeros */
#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))
/* Un gen tiene pares complementarias de bases nitrogenadas, el tamanio de los pares y el indice de aptitud con respecto al gen elite */


typedef struct gen_s
{
  uint8_t par_bases[MAX_NUC_GEN];
  uint16_t tamano;
  uint32_t aptitud;
} gen;

/* El ADN esta seccionado por genes */
typedef struct adn_s
{
  gen genes[MAX_GENES];
  int8_t recesivo;
} adn;

/* Un cromosoma tiene el ADN enrollado y tiene asociadas proteinas, especialmente histonas, aqui las podemos relacionar con el mismo indice */
typedef struct cromosoma_s
{
  adn molecula_adn;
/*
  uint64_t proteinas[MAX_GENES * MAX_NUC_GEN];
*/
} cromosoma;

/* la celula en su nucleo tiene los cromosomas, y cada cromosoma esta compuesto por cierto numero de genes */
/* En la celula tambien guardaremos su aptitud (capacidad de adaptacion) con respecto a un gen de referencia 
 * A cada celula se le asocia una identidad que sera el indice inicial, para no perderse cuando se jerarquice
 * o muera y lleva un registro de la identidad de sus padres, asi como los hijos
 */
typedef struct celula_s
{
  cromosoma cromosomas[MAX_CROMOSOMAS];
  int16_t num_cromo;
  int16_t num_genes;
  int32_t aptitud_gen_ref;
  uint64_t identidad;
  uint32_t padre, madre;
  int32_t num_hijos;
  int32_t hijos[MAX_HIJOS];
} celula;


/* Variables globales para el cromosoma, gen de referencia y modelo de gen elite */
int32_t gCromo_ref;
int32_t gGen_ref;
gen gGen_elite;

/* El estado del PRNG */
static int32_t rand_state ;

/* Definicion de pares de bases definidos para ADN y ARN */
static uint8_t pares_bases_adn[4] = { AT, TA, CG, GC };
static uint8_t pares_bases_arn[4] = { AU, UA, CG, GC };


/* Contador de poblacion */

int32_t poblacion_nacida ;


/* prototipos */





/* Regresa el coeficiente de adaptacion de una celula con respecto al gen_elite ubicado
 * en el cromosoma de referencia gCromo_ref y gen de referencia gGen_ref
 */
int32_t adaptacion (celula t);

/*
 * Inserta dentro de la estructura de la celula su coeficiente de adaptacion con respecto al gen_elite 
 */

void inserta_adaptacion_gen_elite (celula * hijo);

/*
 * Calcula el coeficiente de adaptacion de un gen con respecto a un gen elite
 */
uint32_t aptitud_gen (gen gen_inicial, gen gen_elite);

/*
 * Calcula el coeficiente de adaptacion con la funcion de distancia de levenshtein
 */

uint32_t aptitud_gen_levenshtein (gen gen_inicial, gen gen_elite);

/*
 * te regresa el par de bases nitrogenadas donde difieren dos genes en formato string
 */

uint8_t base_donde_difieren (uint8_t * g1, uint8_t s1, uint8_t * g2, uint8_t s2);

/* 
 * Calcula la distancia de hamming de dos strings 
 */
uint32_t distancia_hamming (uint8_t * a, uint8_t * b, int32_t na);

/*
 * Calcula la distancia de levenstein de dos strings 
 */
uint32_t distancia_levenshtein (uint8_t * s1, uint32_t t1, uint8_t * s2, uint32_t t2);

/*
 * Aparea dos celulas padre y madre y produce un hijo donde el hijo tiene 50% de genes de la madre y el padre
 * con cierto coeficiente de mutacion el cual modifica los n=mutacion pares de bases nitrogenadas en sus genes
 */

celula *entrecruzamiento_adn_padres (celula * padre, celula * madre, celula * hijo, int8_t mutacion);

/*
 * Nombre fancy para liberar toda la memoria de la poblacion
 */
void extermina_poblacion (celula * poblacion);
 
/*
 * Genera un gen aleatorio
 */

gen gen_aleatorio (int32_t num_pares);

/*
 * Genera toda una poblacion de con ADN aleatorio definiendo el numero de cromosomas, genes por cromosoma, pares de bases por gen y habitantes 
 */
celula *genera_poblacion_genes_aleatorios (uint16_t num_cromosomas, uint16_t num_genes, uint16_t num_pares_bases, uint16_t habitantes);

/*
 * Transforma un tipo gen en una palabra de la forma GCCGTAAT
 */
int8_t *gen_string (gen g);

/*
 * Integra una celula nueva (acabada de nacer) a una poblacion, regresa 0 si no se integro por tener peor adaptacion que el menos adaptado y 1 si si se adapta
 */

int32_t integra_celula_poblacion_si_apta (celula nueva, celula * poblacion,int32_t habitantes);

/*
 * Organiza la poblacion en orden de adaptacion al gen elite, poblacion[0] es la celula mas adaptada y poblacion[num_hab-1] es el menos adaptado
 */
void jerarquiza_poblacion_mas_aptos (celula * poblacion, int32_t num_hab);

/*
 * Imprime toda la poblacion con ciertas caracteristicas referentes al cromosoma referencia y gen referencia, en WINDOW w
 */
void muestra_poblacion (celula * poblacion, uint16_t habitantes, int16_t cromo_ref,int16_t gen_ref, gen gen_elite, WINDOW *w);

/*
 * Muta todo el genoma de una celula, definiendole el numero maximo de bases a mutar
 * existe probabilidad de que algunos genes no muten por probabilidad de 1/4 
 */
void muta_genoma_celula (celula * cel, uint8_t max_bases_mutar);


/*
 * Muta n=max_bases_amutar genes de los mas debiles de la poblacion (habitantes-debiles_a_mutar) 
 * esto sirve para envejecer en caso de que n=1 en cada generacion, existe la probabilidad
 * de que no muten algunos si n=1
 */
void muta_poblacion_envejecimiento (celula * p, int32_t habitantes,int32_t debiles_a_mutar,uint8_t max_bases_mutar);

/*
 * Regresa el string del nombre del par de bases nitrogenadas , ej. nombre_par_base(GC) = "GC"
 */
char *nombre_par_base (int8_t n);

/*
 * Aloja la estructura celula *p  con n=num habitantes
 */
void *organismos_alloc (uint16_t num);

/*
 * Regresa un padre apto usando la propiedad de producto de distribucion uniforme por aleatoriedad
 * de la poblacion, podria no ser de los mas aptos, pero la construccion esta hecha para regresar
 * "mas aptos" que "menos aptos" simulando el elitismo a la hora de reproducirse en organismos
 * para parecer una situacion mas real
 */

celula padre_aleatorio_apto (celula * poblacion, int32_t habitantes);

/*
 * Regresa un double aleatorio entre [0,1]
 */
double rand_double1 (void);

/*
 * Regresa un int aleatorio entre 0 y max
 */
int32_t rand_int (int max);

/* Funciones para manipular ventanas, e imprimir bases nitrogenadas con colores dif */
WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);
void base_color(char *s, WINDOW *win); 




#endif /* BEVOLUCION_H */
