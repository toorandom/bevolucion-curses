#include "bevolucion.h"

void base_color(char *s, WINDOW *win) {
    
    int i;
    init_pair('A'-'A'+1, COLOR_RED, COLOR_BLACK);
    init_pair('C'-'A'+1, COLOR_YELLOW,COLOR_BLACK);
    init_pair('G'-'A'+1, COLOR_BLUE,COLOR_BLACK);
    init_pair('T'-'A'+1, COLOR_GREEN,COLOR_BLACK);
    init_pair('U'-'A'+1, COLOR_MAGENTA,COLOR_BLACK);
    
   for(i=0;i<strlen(s);i++) {
    wattron(win,COLOR_PAIR(s[i]-'A'+1));
    wprintw(win,"%c",s[i]);
    wattroff(win,COLOR_PAIR(s[i]-'A'+1));
 //   wrefresh(win);
  }
 return;
    
}

