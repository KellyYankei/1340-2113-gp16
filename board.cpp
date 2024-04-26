#include <stdio.h>
#include <ncurses.h>
#include <string>
#include "board.h"
using namespace std;

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
			"Play Records",
			"Tutorial",
			"Exit",
		  };
int n_choices = sizeof(mode) / sizeof(char *);
int choose_mode();
void print_menu(WINDOW *win, int highlight);
int ask_confirm(int highlight,int starty,int startx);
void print_confirm(WINDOW * win,int confirm_mode,int highlight);

int start() //this is for the starting meun
{	
	int confirm_mode;
	while (choose){
		confirm_mode = choose_mode();
		if(confirm_mode==1)
			choose = 0;
	}
	refresh();
	return highlight;
	//highlight corresponds to the mode number;
}


int choose_mode(){ //this is for player to choose mode
	WINDOW *win;
	int choice = 0;
	int c,ywin,xwin;

	initscr();
	clear();
	noecho();
	cbreak();	
	getmaxyx(stdscr,ywin,xwin);
	startx = (xwin - WIDTH) / 2;  
	starty = (ywin - HEIGHT) / 2; 
	win = newwin(HEIGHT, WIDTH, starty, startx); //define a window
	keypad(win, TRUE); //allow users to use keyboard
	attron(A_REVERSE);
	char hint[] =  "Use arrow keys to go up and down, Press enter to select a choice";
	mvprintw(1,(xwin-sizeof(hint))/2,"Use arrow keys to go up and down, Press enter to select a choice");
	attroff(A_REVERSE);
	refresh();
	print_menu(win, highlight);
	while(1)
	{	c = wgetch(win);
		switch(c)
		{	case KEY_UP:
				if(highlight == 1)
					highlight = n_choices;
				else
					--highlight;
				break;
			case KEY_DOWN:
				if(highlight == n_choices)
					highlight = 1;
				else 
					++highlight;
				break;
			case 10:
				choice = highlight;
				break;
			default:
				refresh();
				break;
		}
		wrefresh(win);
		print_menu(win, highlight);
		if(choice != 0)	
			break;
	}	
	werase(win);
	int confirm_mode = ask_confirm(highlight,starty,startx);//1 is confirm,2 is not confirm
	refresh();
	endwin();
	return confirm_mode;
}
void choose_record(){


}
void read_from_dir(){


}

/*this function asks confirmation after player chose mode,
the inputs are their choice(represent by int highlight, and the windows'xy coordinate),output the confirm choice*/
int ask_confirm(int highlight,int starty,int startx){ 
	initscr();
	WINDOW * ask = newwin(HEIGHT, WIDTH, starty, startx);
	keypad(ask, TRUE);
	box(ask,0,0);
	confirm = 1;
	int choice = 0;
	int input;
	print_confirm(ask,confirm,highlight);
	while(1)
	{	input = wgetch(ask);
		switch(input)
		{	case KEY_UP:
				if(confirm==1)
					confirm = 2;
				else
					confirm = 1;
				break;
			case KEY_DOWN:
				if(confirm==1)
					confirm = 2;
				else
					confirm = 1;
				break;
			case 10:
				choice = 1;
				break;
			default:
				refresh();
				break;
		}
		wrefresh(ask);
		print_confirm(ask,confirm,highlight);
		if(choice == 1)	
			break;
	}	
	return confirm;
}

/*this function print the window of the confirmation, inputs are window pointer, confirm and mode info,output the print*/
void print_confirm(WINDOW * win,int confirm,int highlight){
	int x, y, i;	
	x = 2;
	y = 2;
	char const*yesorno[] = {"YES","NO"};
	mvwprintw(win,y-1,x,"Are you sure you want to choose \"%s\" ?",mode[highlight-1]);
	box(win, 0, 0);
	for(i = 0; i < 2; ++i)
	{	if(confirm == i+1) /* High light the present choice */
		{	wattron(win, A_REVERSE); 
			mvwprintw(win, y+2, x, "%s", yesorno[i]);
			wattroff(win, A_REVERSE);
		}
		else
			mvwprintw(win, y+2, x, "%s", yesorno[i]);
		y+=2;
	}

	wrefresh(win);

}

/*this funciton print the start meun, inputs are window pointer, the mode chosen, output the print*/
void print_menu(WINDOW *menu_win, int highlight)
{
	int x, y, i;	
	x = 2;
	y = 2;
    const char mes[] = "Welcome to Pyramid!";
	mvwprintw(menu_win,y-1,x,mes);
	box(menu_win, 0, 0);
	for(i = 0; i < n_choices; ++i)
	{	if(highlight == i + 1) /* High light the present choice */
		{	wattron(menu_win, A_REVERSE); 
			mvwprintw(menu_win, y, x, "%s", mode[i]);
			wattroff(menu_win, A_REVERSE);
		}
		else
			mvwprintw(menu_win, y, x, "%s", mode[i]);
		++y;
	}

	wrefresh(menu_win);
}

