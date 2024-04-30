#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <stdio.h>
#include <ncurses.h>
#include "actions.h"
#include "structures.h"
#include "saveload.h"
#include "record.h"
#include "board.h"
#include "reverse.h"
#include "printing.h"
#include "judgement.h"
#include "tutorial.h"

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define CLSCR   "\033c"

using namespace std;

int main() {
    cout << CLSCR;
    card Cards[36], pyramid[21], deck[17], show[2];
    int pos = 0, oppo = 2;
    string s = "HSDC", n = "123456789";

    int state = start();
    vector <action> record;
    while (true) {

        switch (state) {
            case 1:
                endwin();
                break;
            case 21: // start from the old game save1 
                endwin();
                load(1,pyramid,deck,show,record,pos,oppo);
                break;
            case 22: // start from the old game save2
                endwin();
                load(2,pyramid,deck,show,record,pos,oppo);
                break;
            case 3: // tutorial
                endwin();
                tutorial();
                return 0;
            case 0:
                return 0;
        }
        if (state == 1|| state == 21 || state == 22) break;
    }
    if(state ==1){
        Initializing(Cards, pyramid, deck);
        set_status(pyramid);
    }
    printmap(pyramid);
    print_deck(pos, deck, oppo, show);

    int currentStateIndex = 0;
    string fileName;
    //saveGameProgress(fileName,record);    //shirley's version

    string command, line;
    vector<string> commands;

    while (true){
        cout << "Enter your command(\'f\'--flip; \'q\'--quit; \'s\'--save; \'r\'--reverse): ";
        getline(cin,line);
        cin.ignore();
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
                if (ask_if_exit()==1){
                endwin();
                cout << CLSCR << RED << "Thank you for playing" << RESET << endl;
                break;
                }
                else{ endwin();
                cout << RESET << endl;}
            }

            else if (commands[0] == "f"){
                pos++;
                cout << CLSCR;
                printmap(pyramid);
                if (print_deck(pos, deck, oppo, show) == 1){
                   pos = -1; oppo--;
                }
            }
            else if (commands[0] == "s"){
                int slot = 0;
                string slotstr;
                while (slot != 1 && slot != 2) {
                    cout << "Choosing the storing slot(1/2): ";
                    getline(cin,slotstr);
                    istringstream iss(slotstr);
                    iss>>slot;
                    if(slot!=1&&slot!=2){
                        cout<< "Invalid input. Please enter either 1 or 2." << endl;
                    }
                }
                save(slot,pyramid,deck,show,record,pos,oppo);
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
