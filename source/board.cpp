#include <stdio.h>
#include <ncurses.h>
#include <cursesw.h>
#include <string>
#include "board.h"
using namespace std;

#define WIDTH 50
#define HEIGHT 8

int startx = 0;
int starty = 0;
int choose =1;
int confirm =1;
int record = 1;
int quit = 1;
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
int ask_confirm(int highlight);
void print_confirm(WINDOW * win,int confirm1,int highlight);
int ask_if_exit();
int choose_record();
void print_record(WINDOW * win,int confirm1,int highlight);
void print_quit(WINDOW * win,int confirm1, int highlight);

int start() //this is for the starting meun
{	
	int confirm_mode;
	while(1){
		while (choose){
			confirm_mode = choose_mode();
			if(confirm_mode==1)
				choose = 0;
		}
		refresh();
		if(highlight==5){
					if (ask_if_exit()==1){
						endwin();
						return 0;
					}
					else{
						endwin();
						choose = 1;
						continue;
						}
		}
		switch(highlight)  //highlight corresponds to the mode number;
			{	case 1: //new game
					endwin();
					return 1;
				case 2: // start from old game
					endwin();
					return 2;
				case 3: // play records
					choose_record();
					return 3;  // I think we can just show the deck but it cannot be operated, and player can choose to go back to meun
				case 4: //tutorial
					endwin();
					return 4;
			}
	}
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
		if(highlight==5){
			refresh();
			endwin();
			return 1;
			}//if choose exit, jump to confirm quit
		int confirm_mode = ask_confirm(highlight);//1 is confirm,2 is not confirm
		refresh();
		endwin();
		return confirm_mode;
}

int choose_record(){
	initscr();
	WINDOW * ask = newwin(HEIGHT, WIDTH, starty, startx);
	keypad(ask, TRUE);
	box(ask,0,0);
	int choice = 0;
	int input;
	print_record(ask,record,highlight);
	while(1)
	{	input = wgetch(ask);
		switch(input)
		{	case KEY_UP:
				if(record==1)
					record = 2;
				else
					record = 1;
				break;
			case KEY_DOWN:
				if(record==1)
					record = 2;
				else
					record = 1;
				break;
			case 10:
				choice = 1;
				break;
			default:
				refresh();
				break;
		}
		wrefresh(ask);
		print_record(ask,record,highlight);
		if(choice == 1)	
			break;
	}	
	endwin();
	return record;

}
void read_from_dir(){


}

int ask_if_exit(){
	initscr();
	WINDOW * ask = newwin(HEIGHT, WIDTH, starty, startx);
	keypad(ask, TRUE);
	box(ask,0,0);
	int choice = 0;
	int input;
	print_quit(ask,quit,highlight);
	while(1)
	{	input = wgetch(ask);
		switch(input)
		{	case KEY_UP:
				if(quit==1)
					quit = 2;
				else
					quit = 1;
				break;
			case KEY_DOWN:
				if(quit==1)
					quit = 2;
				else
					quit = 1;
				break;
			case 10:
				choice = 1;
				break;
			default:
				refresh();
				break;
		}
		wrefresh(ask);
		print_quit(ask,quit,highlight);
		if(choice == 1)	
			break;
	}	
	return quit;
}

/*this function asks confirmation after player chose mode,
the inputs is player's choice,output the confirm choice*/
int ask_confirm(int highlight){ 
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
void print_confirm(WINDOW * win,int confirm1,int highlight){
	int x, y, i;	
	x = 2;
	y = 2;
	char const*yesorno[] = {"YES","NO"};
	mvwprintw(win,y-1,x,"Are you sure you want to choose \"%s\" ?",mode[highlight-1]);
	box(win, 0, 0);
	for(i = 0; i < 2; ++i)
	{	if(confirm1 == i+1) /* High light the present choice */
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
void print_record(WINDOW * win,int confirm1,int highlight){
	int x, y, i;	
	x = 2;
	y = 2;
	char const*record[] = {"save 1","save 2"};
	mvwprintw(win,y-1,x,"Which old games you want to continue?");
	box(win, 0, 0);
	for(i = 0; i < 2; ++i)
	{	if(confirm1 == i+1) /* High light the present choice */
		{	wattron(win, A_REVERSE); 
			mvwprintw(win, y+2, x, "%s", record[i]);
			wattroff(win, A_REVERSE);
		}
		else
			mvwprintw(win, y+2, x, "%s", record[i]);
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

void print_quit(WINDOW * win,int confirm1, int highlight){
	int x, y, i;	
	x = 2;
	y = 2;
	char const*quit[] = {"YES","NO"};
	mvwprintw(win,y-1,x,"Are you sure you want to quit the game?");
	box(win, 0, 0);
	for(i = 0; i < 2; ++i)
	{	if(confirm1 == i+1) /* High light the present choice */
		{	wattron(win, A_REVERSE); 
			mvwprintw(win, y+2, x, "%s", quit[i]);
			wattroff(win, A_REVERSE);
		}
		else
			mvwprintw(win, y+2, x, "%s", quit[i]);
		y+=2;
	}

	wrefresh(win);

}
