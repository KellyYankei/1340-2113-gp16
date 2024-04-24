#include <stdio.h>
#include <ncurses.h>
#include <string>

#define WIDTH 50
#define HEIGHT 8

int startx = 0;
int starty = 0;
int choose =1;
int confirm =1;
int highlight = 1;
char const *mode[] = { 
			"New Game",
			"Start from the old Games",
			"Records",
			"Tutorial",
			"Exit",
		  };
int n_choices = sizeof(mode) / sizeof(char *);
void choose_mode();
void print_menu(WINDOW *win, int highlight);
int ask_confirm(int highlight,int starty,int startx);
void print_confirm(WINDOW * win,int confirm,int highlight);
int main();
