
#include <stdio.h>
#include <ncurses.h>
#include <string>
using namespace std;

#define WIDTH 50
#define HEIGHT 8

extern "C" int choose_mode();
extern "C" void print_menu(WINDOW *win, int highlight);
extern "C" int ask_confirm(int highlight,int starty,int startx);
extern "C" void print_confirm(WINDOW * win,int confirm_mode,int highlight);
extern "C" int start();
