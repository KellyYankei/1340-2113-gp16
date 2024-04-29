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
#include "saveload.h"
#include "record.h"
//#include "board.h"
#include "reverse.h"
#include "printing.h"

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define CLSCR   "\033c"

using namespace std;

void set_status(card pyramid[]){
        for (int i = 0; i < 21; i++){
                if (pyramid[i].status != 0)
                        pyramid[i].status = 1;
        }
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

int main() {
    cout << CLSCR;
    card Cards[36], pyramid[21], deck[17], show[2];
    int pos = 0, oppo = 2;
    string s = "HSDC", n = "123456789";
    Initializing(Cards, pyramid, deck);
    set_status(pyramid);
    printmap(pyramid);
    print_deck(pos, deck, oppo, show);

    vector<action> record;
    int currentStateIndex = 0;
    string fileName;
    //saveGameProgress(fileName,record);    //shirley's version

    string command, line;
    vector<string> commands;

    //if (start()!=1){return 0;}; //if chosen mode is "start new game"

    while (true){
        cout << "Enter your command(\'f\'--flip; \'q\'--quit; \'s\'--save; \'r\'--reverse): ";
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
                cout << CLSCR << RED << "Thank you for playing" << RESET << endl;
                break;
                }

            else if (commands[0] == "f"){
                pos++;
                cout << CLSCR;
                printmap(pyramid);
                if (print_deck(pos, deck, oppo, show) == 1){
                   pos = -1; oppo--;
                }
cout<<"Main: "<<pos<<" "<<oppo<<endl;
            }
            else if (commands[0] == "s"){
                int slot;
                cout << "Choose the storing slot (1/2): ";
                cin >> slot;
                cout << endl;
                save(slot,pyramid,deck,record);
                break;
            }

            else if (commands[0] == "r"){
                if (deleteLastStep(record,pyramid,deck)){
                cout << CLSCR;
                set_status(pyramid);
                printmap(pyramid);
                print_deck(pos, deck, oppo, show);
                }
            }

            else if (commands[0].size() == 2){
                if (checkFormat(commands[0])) {
                    action match = makeMatch(commands[0],"",pyramid,deck,pos,show,oppo);
                    if (match.success){
                        set_status(pyramid);
                        cout << CLSCR;
                        printmap(pyramid);
                        print_deck(pos, deck, oppo, show);
                        record.push_back(match);
                        cout << RED << commands[0] << " has been eliminated" << RESET << endl;
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
                action match = makeMatch(commands[0],commands[1],pyramid,deck,pos,show,oppo);
                if (match.success) {
                    set_status(pyramid);
                    cout << CLSCR;
                    printmap(pyramid);
                    print_deck(pos, deck, oppo, show);
                    record.push_back(match);
                    cout << RED << commands[0] << " & " << commands[1] << " have been eliminated" << RESET << endl;
                }
                else {
                    cout << CLSCR;
                    printmap(pyramid);
                    print_deck(pos, deck, oppo, show);
                    cout << RED << "Chosen cards are not paired" << RESET << endl;
                }
            }
            else {
                cout << CLSCR;
                printmap(pyramid);
                print_deck(pos, deck, oppo, show);
                cout << RED << "Invalid Input" << RESET << endl;
            }
        }
        commands.clear();

        if(pyramid[0].status==0){
            cout << CLSCR;
            printmap(pyramid);
            print_deck(pos, deck, oppo, show);
            cout << RED << "Congratulations! Good game! " << RESET << endl;
            break;
        }
    }
    return 0;
}
