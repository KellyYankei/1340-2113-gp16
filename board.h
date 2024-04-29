#include <cursesw.h>
#include <stdio.h>
#include <ncurses.h>
#include <string>
using namespace std;

#define WIDTH 50
#define HEIGHT 8

extern "C" int choose_mode();
extern "C" void print_menu(WINDOW *win, int highlight);
extern "C" int ask_confirm(int highlight,int starty,int startx);
extern "C" void print_confirm(WINDOW * win,int confirm1,int highlight);
extern "C" int ask_if_exit();
extern "C" int choose_record();
extern "C" void print_record(WINDOW * win,int confirm1,int highlight);
extern "C" void print_quit(WINDOW * win,int confirm1, int highlight);
extern "C" int start();
