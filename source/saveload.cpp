#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "structures.h"
#include "actions.h"
#include "saveload.h"

using namespace std;

//This function is used to save the game situation into txt files. 2 slots are offered to store it. The input includes all the parameters needed. 
//The function returns true for successful storing, and false for failure.
bool save(int slot, card pyramid[21], card deck[15], card deck_movable[2], vector<action> steps, int pos, int oppo) {
	//initialize save
	string filename;
	if (slot == 1)
		filename = "save1.txt";
	else if (slot == 2)
		filename = "save2.txt";
	else {
		cout << "Slot does not exist." << endl;
		return false;
	}

	//check if slot is occupied
	ifstream fin(filename.c_str());
	string sTmp, input;

	if (fin) {
		fin >> sTmp;
		if (!fin.eof()) {
			cout << "Existing save in this slot. Overwrite save? (y/n) ";
			getline(cin, input);
			while (input != "y" && input != "n") {
				cout << endl << "Invalid input" << endl << "Existing save in this slot. Overwrite save? (y/n) ";
				getline(cin, input);
			}
			if (input == "n") {
				cout << endl << "Save cancelled.";
				return false;
			}
		}
	}

	cout << endl;
	fin.close();

	//write save to file
	ofstream fout(filename);
	int i;

	if (fout.fail()) {
		cout << "Error occurred. Could not save." << endl;
		return false;
	}
	cout << "open file" << endl;
	for (i = 0; i < 21; i++)
		fout << pyramid[i].suit << ' ' << pyramid[i].num << ' ' << pyramid[i].status << endl;

	for (i = 0; i < 15; i++)
		fout << deck[i].suit << ' ' << deck[i].num << ' ' << deck[i].status << endl;

	fout << deck_movable[0].suit << ' ' << deck_movable[0].num << ' ' << deck_movable[0].status << endl;
	fout << deck_movable[1].suit << ' ' << deck_movable[1].num << ' ' << deck_movable[1].status << endl;

//	for (i = 0; i < steps.size(); i++)
//		fout << steps[i] << endl;

	fout << pos << endl << oppo << endl;

	fout.close();
	cout << "Save successful." << endl;

	return true;
}

//This function is used to load the game situation from the previous saving in the txt files. The input includes the commands that which slot to load,
//and all the useful parameters (all pass by reference). The function will update the values of the variables to load the previous game situation. 
//It will return true if the loading is successful, and return false otherwise.
bool load(int slot, card pyramid[21], card deck[15], card deck_movable[2], vector<action>& steps, int& pos, int& oppo) {
	//initialize load
	string filename;
	if (slot == 1)
		filename = "save1.txt";
	else if (slot == 2)
		filename = "save2.txt";
	else {
		cout << "Slot does not exist." << endl;
		return false;
	}

	//read file
	ifstream fin(filename.c_str());
	int i;
	string sTmp;

	if (fin.fail()) {
		cout << "Error occurred. Could not load." << endl;
		return false;
	}

	for (i = 0; i < 21; i++)
		fin >> pyramid[i].suit >> pyramid[i].num >> pyramid[i].status;

	for (i = 0; i < 15; i++)
		fin >> deck[i].suit >> deck[i].num >> deck[i].status;

	fin >> deck_movable[0].suit >> deck_movable[0].num >> deck_movable[0].status;
	fin >> deck_movable[1].suit >> deck_movable[1].num >> deck_movable[1].status;

//	while (fin >> sTmp)
//		steps.push_back(sTmp);

	fin >> pos >> oppo;

	fin.close();
	cout << "Load successful." << endl;

	return true;
}
