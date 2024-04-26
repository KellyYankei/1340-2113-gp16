#include <iostream> 
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <vector>
//#include <stdio.h>
//#include <ncurses.h>
#include "actions.h"
#include "structures.h"
//#include "board.h"

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define CLSCR   "\033c"

using namespace std;

void printspace(int i){
    for (int k = 0; k < 5-i; k++){
                cout << "   ";
        }
}

void printcard_up(int status){
    if (status == 2)
        cout << GREEN << "┌────┐" << RESET;
    else
        cout << "┌────┐";
}

void printcard_mid(int status, char suit, int num){
    if (status == 2)
        cout << GREEN << "│ " << suit << num << " │" << RESET;
    else if (status == 1)
        cout << "│ " << suit << num << " │";
    else
        cout << "│    │";
}

void printcard_bottom(int status){
    if (status == 2)
        cout << GREEN << "└────┘" << RESET;
    else
        cout << "└────┘";
}

void printmap(card map[]){
    for (int i = 0; i < 6; i++){
        printspace(i);
        for (int j = (i*(i+1))/2; j < (i*(i+1))/2 + i + 1; j++){
            printcard_up(map[j].status);
        }
        cout << endl;
        printspace(i);
        for (int j = (i*(i+1))/2; j < (i*(i+1))/2 + i + 1; j++){
            printcard_mid(map[j].status, map[j].suit, map[j].num);
        }
        cout << endl;
        printspace(i);
        for (int j = (i*(i+1))/2; j < (i*(i+1))/2 + i + 1; j++){
            printcard_bottom(map[j].status);
        } 
        cout << endl;
    }
}

void set_status(card pyramid[])
{
	if( (pyramid[0].status==1) && (pyramid[1].status==0) && (pyramid[2].status==0) ) pyramid[0].status=2; 
	if( (pyramid[1].status==1) && (pyramid[3].status==0) && (pyramid[4].status==0) ) pyramid[1].status=2; 
	if( (pyramid[2].status==1) && (pyramid[4].status==0) && (pyramid[5].status==0) ) pyramid[2].status=2; 
	if( (pyramid[3].status==1) && (pyramid[6].status==0) && (pyramid[7].status==0) ) pyramid[3].status=2; 
	if( (pyramid[4].status==1) && (pyramid[7].status==0) && (pyramid[8].status==0) ) pyramid[4].status=2; 
	if( (pyramid[5].status==1) && (pyramid[8].status==0) && (pyramid[9].status==0) ) pyramid[5].status=2; 
	if( (pyramid[6].status==1) && (pyramid[10].status==0) && (pyramid[11].status==0) ) pyramid[6].status=2; 
	if( (pyramid[7].status==1) && (pyramid[11].status==0) && (pyramid[12].status==0) ) pyramid[7].status=2; 
	if( (pyramid[8].status==1) && (pyramid[12].status==0) && (pyramid[13].status==0) ) pyramid[8].status=2; 
	if( (pyramid[9].status==1) && (pyramid[13].status==0) && (pyramid[14].status==0) ) pyramid[9].status=2; 
	if( (pyramid[10].status==1) && (pyramid[15].status==0) && (pyramid[16].status==0) ) pyramid[10].status=2; 
	if( (pyramid[11].status==1) && (pyramid[16].status==0) && (pyramid[17].status==0) ) pyramid[11].status=2; 
	if( (pyramid[12].status==1) && (pyramid[17].status==0) && (pyramid[18].status==0) ) pyramid[12].status=2; 
	if( (pyramid[13].status==1) && (pyramid[18].status==0) && (pyramid[19].status==0) ) pyramid[13].status=2; 
	if( (pyramid[14].status==1) && (pyramid[19].status==0) && (pyramid[20].status==0) ) pyramid[14].status=2; 
	if (pyramid[15].status==1) pyramid[15].status=2; 
	if (pyramid[16].status==1) pyramid[16].status=2; 
	if (pyramid[17].status==1) pyramid[17].status=2; 
	if (pyramid[18].status==1) pyramid[18].status=2; 
	if (pyramid[19].status==1) pyramid[19].status=2; 
	if (pyramid[20].status==1) pyramid[20].status=2; 
	
	return;
}

void Initialzing(card Cards[], card pyramid[], card deck[]){
    srand(time(NULL));
    card tmp;
    string suits = "SDHC";
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 9; j++){
            tmp.suit = suits[i];
            tmp.num = j + 1;
            tmp.status = 1;
            Cards[i*9 + j] = tmp;
        }
    }

    card temp;
    int randomIndex = 0;
    for (int i = 0; i < 36; i++){
        randomIndex = rand() % 36;
        temp = Cards[i];
        Cards[i] = Cards[randomIndex];
        Cards[randomIndex] = temp;
    }
    
    for (int i = 0; i < 21; i++){
        pyramid[i] = Cards[i];
    }

    for (int i = 0; i < 15; i++){
        deck[i] = Cards[i+21];
        deck[i].status = 2;
    }

}

int searchpyramid(card pyramid[], char s, int n){
    for (int i = 0; i < 21; i++){
        if (pyramid[i].suit == s && pyramid[i].num == n && pyramid[i].status == 2){
            return i; 
        }
    }
    return -1;
}

int searchshow(card show[], char s, int n){
    for (int i = 0; i < 21; i++){
        if (show[i].suit == s && show[i].num == n){
            return i; 
        }
    }
    return -1;
}

int print_deck(int pos1, card deck1[], int oppo1, card show[2])   //pos1 means the position of the left card in the array "deck" defined below (not deck1)
{//show means the present card displayed. The status will be 1 normally, and will be 0 if there is no card showed in the corresponding position.
    card deck[20];    //use this array to record the remaining cards in the deck below  
    int num=0;       //use this to count the number of remaining cards in the deck below
	
    for(int i=0;i<=14;i++)
    {
	    if(deck1[i].status!=0)
	    {
	        deck[num]=deck1[i];
	        num++;
	    } 
    } 
    
    if(num==0)  
	{
		cout<<"You have used up all the decks!"<<endl;
		show[0]=deck1[0];
	        show[1]=deck1[0];
	        show[0].status=0;
	        show[1].status=0;
		return 0;
	}

    if(oppo1==0)
    {
	    cout<<RED << "You have used up all the opportunities to move the decks!"<< RESET <<endl;
	    show[0]=deck1[0];
	    show[1]=deck1[0];
	    show[0].status=0;
	    show[1].status=0;
	    return 2;
    }
    
    if(pos1>=1 && pos1<num){
        printspace(2);
        printcard_up(2);
	    printspace(3);
        printcard_up(2);
        cout << endl;
        printspace(2);
        printcard_mid(2, deck[pos1].suit, deck[pos1].num);
	    printspace(3);
        printcard_mid(2, deck[pos1-1].suit, deck[pos1-1].num);
        cout << endl;
        printspace(2);
        printcard_bottom(2);
	    printspace(3);
        printcard_bottom(2);  
	    show[0]=deck[pos1];
	    show[1]=deck[pos1-1];
	    show[0].status=2;
	    show[1].status=2;
	    cout << endl;
    } 
    else if(pos1==0){   //if pos1==0,then only the first card in the deck need to be showed
	    printspace(2);
        printcard_up(2);
        cout << endl;
        printspace(2);
        printcard_mid(2, deck[0].suit, deck[0].num);
        cout << endl;
        printspace(2);
        printcard_bottom(2);
	    show[0]=deck[pos1];
	    show[1]=deck[pos1];
	    show[0].status=2;
	    show[1].status=0;
	    cout << endl;
    }
    else{    //if pos1==num, then only the last card in the deck need to be showed
	    printspace(-2);
        printcard_up(2);
        cout << endl;
        printspace(-2);
        printcard_mid(2, deck[num-1].suit, deck[num-1].num);
        cout << endl;
        printspace(-2);
        printcard_bottom(2);
	    show[0]=deck[num-1];
	    show[1]=deck[num-1];
	    show[0].status=0;
	    show[1].status=2;
	    cout << endl;
    }

    if(num==pos1) return 1; //This happens means the player have used up an opportunity to turn over the whole deck below. Special solution is needed outside.
    return 0; 
}

int main() {
    cout << CLSCR;
    card Cards[36], pyramid[21], deck[17], show[2];
    int pos = 0, oppo = 1;
    string s = "HSDC", n = "123456789";
    Initialzing(Cards, pyramid, deck);
    set_status(pyramid);
    printmap(pyramid);
    print_deck(pos, deck, oppo, show);
    
    string command, line;
    vector<string> commands;

    //if (start()!=1){return 0;}; //if chosen mode is "start new game"
	
    while (true){
        cout << "Enter your command(\'f\'--flip; \'q\'--quit): ";
        getline(cin,line);
        istringstream iss(line);
        while (iss >> command){
            commands.push_back(command);
        }
        
        if (commands.size() > 2){
            cout << CLSCR;
            printmap(pyramid);
            print_deck(pos, deck, oppo, show);
            cout << RED << "Invalid Input" << RESET << endl;
        }

        else if (commands.size() == 1){
            if (commands[0] == "q"){
                cout << CLSCR << RED << "Thank you for playing" << RESET;
                break;
                }

            else if (commands[0] == "f"){
                pos++;
                cout << CLSCR;
                printmap(pyramid);
                if (print_deck(pos, deck, oppo, show) == 1){
                   pos = -1; oppo--;
                }   
            }

            else if (commands[0].size() == 2){
                if (checkFormat(commands[0])) {
                    if (makeMatch(commands[0],"",pyramid,deck,pos,show)){
                        set_status(pyramid);
                        cout << CLSCR;
                    printmap(pyramid);
                    print_deck(pos, deck, oppo, show);
                    cout << RED << commands[0] << " has be eliminated" << RESET << endl;
                    }
                }
                else {
                    cout << CLSCR;
                    printmap(pyramid);
                    print_deck(pos, deck, oppo, show);
                    cout << RED << "Invalid Input" << RESET << endl;
                }
            }
        }
      
        else if (commands.size() == 2){
            if (checkFormat(commands[0]) && checkFormat(commands[1])){

                if (makeMatch(commands[0],commands[1],pyramid,deck,pos,show)) {
                    set_status(pyramid);
                    cout << CLSCR;
                    printmap(pyramid);
                    print_deck(pos, deck, oppo, show);
                    cout << RED << commands[0] << " has be eliminated" << RESET << endl;
                }
                else {
                    cout << CLSCR;
                    printmap(pyramid);
                    print_deck(pos, deck, oppo, show);
                    cout << RED << "Chosen cards are not paired" << RESET << endl;
                }
            }
        }
        commands.clear();
    }
    return 0;
}
