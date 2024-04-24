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
