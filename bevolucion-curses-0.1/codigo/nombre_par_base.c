/*
 * Dada una base en formato 8 bits, regresa su representacion en string, muy simple
 */
#include "bevolucion.h"
char *
nombre_par_base (int8_t n)
{
  char *ptr;

  switch (n)
    {
    case AT:
      //ptr = "\033[22;33mA";
      ptr = "A";
      break;
    case TA:
      //ptr = "\033[01;36mT";
      ptr = "T";
      break;
    case CG:
      //ptr = "\033[22;31mC";
      ptr = "C";
      break;
    case GC:
      //ptr = "\033[22;32mG";
      ptr = "G";
      break;
    case AU:
      //ptr = "\033[22;34mA";
      ptr = "A";
      break;
    case UA:
      //ptr = "\033[01;33mU";
      ptr = "U";
      break;
    default:
      fprintf (stderr,
               "ERROR, %x no representa ningun par complementario de bases nitrogenadas\n",
               n);
      ptr = NULL;
      exit (EXIT_FAILURE);

    }
  return ptr;
}
