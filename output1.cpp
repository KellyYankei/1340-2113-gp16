#include <iostream> 
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

struct card {
    char suit;
    int num;
    int status;
};

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"

void printspace(int i){
    for (int k = 0; k < 5-i; k++){
                cout << "   ";
        }
}

void printcard_up(int status){
    if (status == 2)
        cout << GREEN << "©°©¤©¤©¤©¤©´" << RESET;
    else
        cout << "©°©¤©¤©¤©¤©´";
}

void printcard_mid(int status, char suit, int num){
    if (status == 2)
        cout << GREEN << "©¦" << " " << suit << num << " " << "©¦" << RESET;
    else if (status == 1)
        cout << "©¦" << " " << suit << num << " " << "©¦";
    else
        cout << "©¦    ©¦";
}

void printcard_bottom(int status){
    if (status == 2)
        cout << GREEN << "©¸©¤©¤©¤©¤©¼" << RESET;
    else
        cout << "©¸©¤©¤©¤©¤©¼";
}

void printmap(struct card map[]){
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

void Initialzing(card deck[]){
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

void print_deck(int &pos1, card deck[], int &oppo1)//pos1 means the position of the left card
{
    if(oppo1==0) cout<<"You have used up all the opportunities to flip the deck!"<<endl;
    if(pos1>=1 && pos1<=14)
    {
        printspace(2);
        printcard_up(2);
        printcard_up(2);
        cout << endl;
        printspace(2);
        printcard_mid(2, deck[pos1].suit, deck[pos1].num);
        printcard_mid(2, deck[pos1-1].suit, deck[pos1-1].num);
        cout << endl;
        printspace(2);
        printcard_bottom(2);
        printcard_bottom(2);  
    } 
    else if(pos1==0)
    {
	printspace(2);
        printcard_up(2);
        cout << endl;
        printspace(2);
        printcard_mid(2, deck[0].suit, deck[0].num);
        cout << endl;
        printspace(2);
        printcard_bottom(2);  
    }
    else
    {
	printspace(3);
        printcard_up(2);
        cout << endl;
        printspace(3);
        printcard_mid(2, deck[14].suit, deck[14].num);
        cout << endl;
        printspace(3);
        printcard_bottom(2);
    }
    pos1++;
    if(pos1==16)
    {
	pos1=0;
	oppo1--;
    }
	
    return;
}

int main(){
	/*
    srand(time(NULL));
    card deck[36];
    Initialzing(deck);
    shuffle(deck, 36);
    
    card pyramid[21];

    for (int i = 0; i < 21; i++){
    pyramid[i] = deck[i];
    }

    printmap(pyramid);

    string command;                  */
    
    int pos1=0;//use this to mark the position of the deck
    int oppo1=3;//use this to mark the remaining opportunities of flipping the deck
    while (true){
    /*    cout << "Which card to choose(type 'q' to quit): ";
        cin >> command;
        if (command == "q")
            break;
        char s = command[0];
        int n = command[1]-'0';
        searchpyramid(pyramid, s, n);    
        printmap(pyramid);                                */
        
       if(command == "\n") 
	   {
	   	    printmap(pyramid);
	   	    print_deck(pos1,deck,oppo1);
	   }
        
    }
}

//status 0--removed 1--exist 2--can be moved
