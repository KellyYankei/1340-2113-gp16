#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include "printing.h"
#include "structures.h"

using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"

//functions for formatting
void printspace(int i){
    for (int k = 0; k < 5-i; k++)
        cout << "   ";
}

void printcard_up(int status){
    if (status == 2)
        cout << GREEN << "┌────┐" << RESET;
    else
        cout << "┌────┐";
}

void printcard_mid(int status, char suit, int num){
    if (status == 2)
        cout << GREEN << "│" << " " << suit << num << " " << "│" << RESET;
    else if (status == 1)
        cout << "│" << " " << suit << num << " " << "│";
    else
        cout << "│    │";
}

void printcard_bottom(int status){
    if (status == 2)
        cout << GREEN << "└────┘" << RESET;
    else
        cout << "└────┘";
}

//function for printing the pyramid
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

//random generation of game set
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

//look for a certain card in the pyramid
int searchpyramid(card pyramid[], char s, int n){
    for (int i = 0; i < 21; i++){
        if (pyramid[i].suit == s && pyramid[i].num == n && pyramid[i].status == 2){
			return i;
		}   
    }
	return -1
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
	    cout<<"You have used up all the opportunities to move the decks!"<<endl;
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
	    show[0].status=1;
	    show[1].status=1;
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
	    show[0].status=1;
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
	    show[1].status=1;
	    cout << endl;
    }

    if(num==pos) return 1; //This happens means the player have used up an opportunity to turn over the whole deck below. Special solution is needed outside.
    return 0; 
}


//status 0--removed 1--exist 2--can be moved
