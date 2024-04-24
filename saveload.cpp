#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "structures.h"

using namespace std;

//2 slots offered
void save(int slot, card pyramid[21], card deck[15], vector<string> steps) {
	//initialize save
	string filename;
	if (slot == 1)
		filename = "save1.txt";
	else if (slot == 2)
		filename = "save2.txt";
	else {
		cout << "Slot does not exist." << endl;
		return;
	}

	//check if slot is occupied
	ifstream fin(filename.c_str());
	string sTmp, input;

	if (fin) {
		fin >> sTmp;
		if (!fin.eof()) {
			cout << "Existing save in this slot. Overwrite save? (y/n) ";
			getline(cin, input);
			while (input != "y" && input != "n")
				cout << endl << "Invalid input" << endl << "Existing save in this slot. Overwrite save? (y/n) ";
			if (input == "n") {
				cout << "Save cancelled.";
				return;
			}
		}
	}

	fin.close();

	//write save to file
	ofstream fout(filename.c_str());
	int i;

	if (fout.fail()) {
		cout << "Error occurred. Could not save." << endl;
		fout.close();
		return;
	}

	for (i = 0; i < 21; i++)
		fout << pyramid[i].suit << ' ' << pyramid[i].num << ' ' << pyramid[i].status << endl;

	for (i = 0; i < 15; i++)
		fout << deck[i].suit << ' ' << deck[i].num << ' ' << deck[i].status << endl;

	for (i = 0; i < steps.size(); i++)
		fout << steps[i] << endl;

	fout.close();
	cout << "Save successful." << endl;

	return;
}

void load(int slot, card pyramid[21], card deck[15], vector<string>& steps) {
	//initialize load
	string filename;
	if (slot == 1)
		filename = "save1.txt";
	else if (slot == 2)
		filename = "save2.txt";
	else {
		cout << "Slot does not exist." << endl;
		return;
	}

	//read file
	ifstream fin(filename.c_str());
	int i;
	string sTmp;

	if (fin.fail()) {
		cout << "Error occurred. Could not load." << endl;
		fin.close();
		return;
	}

	for (i = 0; i < 21; i++)
		fin >> pyramid[i].suit >> pyramid[i].num >> pyramid[i].status;

	for (i = 0; i < 15; i++)
		fin >> deck[i].suit >> deck[i].num >> deck[i].status;

	while (fin >> sTmp)
		steps.push_back(sTmp);

	fin.close();
	cout << "Load successful." << endl;

	return;
}