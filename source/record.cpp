#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <vector>
#include <cmath>
#include "record.h"

using namespace std;

struct GameState {
    int type;   //1~6
    int pyramid1[2], pyramid2[2];
    int deck1, deck2;
    GameState* next;
    GameState(int a) {
        type = a;
    }   //for type 1, flip cards in pile
    GameState(int a, int index[2]) {
        type = a;
        pyramid1[0], pyramid1[1] = index[0], index[1];
    }   //for type 2, erase 9 in pyramid
    GameState(int a, int index) {
        type = a;
        deck1 = index;
    }   //for type 3, erase 9 in pile
    GameState(int a, int index1[2],int index2[2]) {
        type = a;
        pyramid1[0], pyramid1[1] = index1[0], index1[1];
        pyramid2[0], pyramid2[1] = index2[0], index2[1];
    }   //for type 4, combine two cards from pyramid
    GameState(int a, int index1[2],int index2) {
        type = a;
        pyramid1[0], pyramid1[1] = index1[0], index1[1];
        deck1 = index2;
    }   //for type 5, combine two cards respectively from pyramid & pile
    GameState(int a, int index1,int index2) {
        type = a;
        deck1, deck2 = index1, index2;
    }   //for type 6, combine two cards from pile
};

// Function to record the current game state
string recordGameState(GameState state) {
    string newline = "state" + to_string(state.type) + ": ";
    switch (state.type) {
        case 1:
            newline += "flip";
        break;
        case 2:
            newline += "erase 9 at pyramid[" + to_string(state.pyramid1[0]) + "][" +
                to_string(state.pyramid1[1]) + "]";
        break;
        case 3:
            newline += "erase 9 at pile[" + to_string(state.deck1) + "]";
        break;
        case 4:
            newline += "combine pyramid[" + to_string(state.pyramid1[0]) + "][" +
                to_string(state.pyramid1[1]) + "]";
            newline += "pyramid[" + to_string(state.pyramid2[0]) + "][" +
                to_string(state.pyramid2[1]) + "]";
        break;
        case 5:
            newline += "combine pyramid[" + to_string(state.pyramid1[0]) + "][" +
                to_string(state.pyramid1[1]) + "]"; + 
                "pile[" + to_string(state.deck2) + "]";
        break;
        case 6:
            newline += "combine pile[" + to_string(state.deck1) + "] " + "pile[" +
                to_string(state.deck2) + "]";
        break;
    }   return newline;
}

// Function to revert to the previous game state

void revertToPreviousState(int currentStateIndex, vector<GameState> &record) {
    if (currentStateIndex > 0) {
        GameState lastState = record.back();
        int index1,index2;
        switch (lastState.type) {
            case 1:
                //reverse flip
                break;
            case 2:
                index1 = (pow(lastState.pyramid1[0],2) + lastState.pyramid1[0]) / 2 + lastState.pyramid1[1] + 1;
                //pyramid[index1].status = 2;
                break;
            case 3:
                //deck[lastState.deck1] = 2;
                break;
            case 4:
                index1 = (pow(lastState.pyramid1[0],2) + lastState.pyramid1[0]) / 2 + lastState.pyramid1[1] + 1;
                index2 = (pow(lastState.pyramid2[0],2) + lastState.pyramid2[0]) / 2 + lastState.pyramid2[1] + 1;
                //pyramid[index1].status = 2;
                //pyramid[index2].status = 2;
                break;
            case 5:
                index1 = (pow(lastState.pyramid1[0],2) + lastState.pyramid1[0]) / 2 + lastState.pyramid1[1] + 1;
                //pyramid[index].status = 2;
                //deck[lastState.deck1].status = 2;
                break;
            case 6:
                //deck[lastState.deck1] = 2;
                //deck[lastState.deck2] = 2;
                break;
        }
        currentStateIndex--;
        
    } else {
        cout << "No previous state available." << endl;
    }
}

// Function to save the game progress to a file

void saveGameProgress(const string& fileName, vector<GameState> record) {
    ofstream recordFile (fileName);
    vector<GameState>::iterator itr;
    for (itr=record.begin();itr!=record.end();itr++){
        recordFile << recordGameState(*itr) << endl;
        for (int i=0; i<25; i++) recordFile << '-';
        recordFile << endl;
    }
    recordFile.close();
}

// Function to load the game progress from a file
void loadGameProgress(int currentStateIndex, string& fileName) { //parameter may also contain &pyramid and &deck
    ifstream recordFile(fileName);
    if (recordFile.fail()) exit(1);
    string line;
    while (getline(recordFile,line)) {
        stringstream ss(line);
        string word;
        ss >> word;
        int row1, col1, index1, row2, col2, index2;
        switch (word[5]){
            case '1':
                //flip card in deck
                break;
            case '2':
                for (int i=0; i<4; i++) ss >> word;
                row1 = word[8] - '0';
                col1 = word[11] - '0';
                index1 = (pow(row1,2) + row1) / 2 + col1 + 1;
                //pyramid[index1] = 0;
                break;
            case 3:
                for (int i=0; i<4; i++) ss >> word;
                index1 = word[5] - '0';
                //deck[index1] = 0;
                break;
            case 4:
                for (int i=0; i<4; i++) ss >> word;
                row1, col1 = word[8] - '0', word[11] - '0';
                index1 = (pow(row1,2) + row1) / 2 + col1 + 1;
                ss >> word;
                row2, col2 = word[8] - '0', word[11] - '0';
                index2 = (pow(row2,2) + row2) / 2 + col2 + 1;
                //pyramid[index1].status = 0;
                //pyramid[index2].status = 0;
                break;
            case 5:
                for (int i=0; i<2; i++) ss >> word;
                row1, col1 = word[8] - '0', word[11] - '0';
                index1 = (pow(row1,2) + row1) / 2 + col1 + 1;
                ss >> word;
                index2 = word[5] - '0';
                //pyramid[index1].status = 0;
                //deck[index2].status = 0;
                break;
            case 6:
                for (int i=0; i<2; i++) ss >> word;
                index1 = word[5] - '0';
                ss >> word;
                index2 = word[5] - '0';
                //deck[lastState.deck1] = 2;
                //deck[lastState.deck2] = 2;
                break;
        }
    }
}

int main(){
    int currentStateIndex = 0;
    GameState* head;
    GameState* current;
    string fileName;
    time_t rawtime;
    time(&rawtime);
    fileName = ctime(&rawtime); //generate a timestamp as record fileName
    //However if player choose 读档, fileName should be what they choose
    int pyramid1[2] ={3,5};
    vector<GameState> record;
    record.push_back(GameState(2,pyramid1));
    record.push_back(1);
    saveGameProgress(fileName,record);
}
