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

void status(card pyramid[])
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
    int k = 0;
    for (int i = 0; i < 21; i++){
        if (pyramid[i].suit == s && pyramid[i].num == n){
            cout << RED << "You choosed " << pyramid[i].suit << pyramid[i].num << RESET << endl;
            k = 1; 
        }
    }
    if (k == 0)
        cout << RED << "This card is not in pyramid" << RESET << endl;
}

int main(){
    
    srand(time(NULL));
    card deck[36], pyramid[21];
    Initialzing(deck);
    shuffle(deck, 36);

    for (int i = 0; i < 21; i++){
        pyramid[i] = deck[i];
    }
    printmap(pyramid);
    
    status(pyramid);
    printmap(pyramid);
    
    pyramid[15].status = 0;
    status(pyramid);
    printmap(pyramid);
    
    pyramid[16].status = 0;
    status(pyramid);
    printmap(pyramid);



    // string command;
    
    
    // while (true){
    //     cout << "Which card to choose(type 'q' to quit): ";
    //     cin >> command;
    //     if (command == "q")
    //         break;
    //     char s = command[0];
    //     int n = command[1]-'0';
    //     searchpyramid(pyramid, s, n);
    //     printmap(pyramid);
    // }
    // return 0;
}
