
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

int main()    //the main funciton in this area, but still need to be changed
{	
	while (choose){
		choose_mode();
		if(confirm==1)
			choose = 0;
	}
	return 0;
}
void choose_mode(){
	WINDOW *win;
	int choice = 0;
	int c,ywin,xwin;

	initscr();
	clear();
	noecho();
	cbreak();	
	getmaxyx(stdscr,ywin,xwin);
	startx = (xwin - WIDTH) / 2;  //25
	starty = (ywin - HEIGHT) / 2; //8
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
	int confirm = ask_confirm(highlight,starty,startx);//1 is confirm,2 is not confirm
	getch();
	clrtoeol();
	refresh();
	endwin();
}
int ask_confirm(int highlight,int starty,int startx){
	initscr();
	WINDOW * ask = newwin(HEIGHT, WIDTH, starty, startx);
	keypad(ask, TRUE);
	box(ask,0,0);
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
