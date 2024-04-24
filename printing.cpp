#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include "structures.h"

using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"

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

void shuffle(card deck[], int len){
    card temp;
    int randomIndex = 0;
    for (int i = 0; i < len; i++){
        randomIndex = rand() % len;
        temp = deck[i];
        deck[i] = deck[randomIndex];
        deck[randomIndex] = temp;
    }
}

void Initializing(card deck[]){
    card tmp;
    string suits = "SDHC";
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 9; j++){
            tmp.suit = suits[i];
            tmp.num = j + 1;
            tmp.status = 1;
            deck[i*9 + j] = tmp;
        }
    }
}

void searchpyramid(card pyramid[], char s, int n){
    for (int i = 0; i < 21; i++){
        if (pyramid[i].suit == s && pyramid[i].num == n)
            pyramid[i].status = 2;
    }
}

void print_deck(int &pos1, card deck1[], int &oppo1)//pos1 means the position of the left card
{
    card deck[20];
    int num=0;
    for(int i=0;i<=14;i++)
    {
	    if(deck1[i].status!=0)
	    {
	        deck[num]=deck1[i];
	        num++;
	    } 
    } 
    
    if(num==0)//num=15
	{
		cout<<"You have used up all the decks!"<<endl;
		return;
	}

    if(oppo1==0)
    {
	    cout<<"You have used up all the opportunities to move the decks!"<<endl;
	    return;
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
	    cout << endl;
    } 
    else if(pos1==0){
	    printspace(2);
        printcard_up(2);
        cout << endl;
        printspace(2);
        printcard_mid(2, deck[0].suit, deck[0].num);
        cout << endl;
        printspace(2);
        printcard_bottom(2);
	    cout << endl;
    }
    else{
	    printspace(-2);
        printcard_up(2);
        cout << endl;
        printspace(-2);
        printcard_mid(2, deck[14].suit, deck[14].num);
        cout << endl;
        printspace(-2);
        printcard_bottom(2);
	    cout << endl;
    }
    
    return;
}


//status 0--removed 1--exist 2--can be moved