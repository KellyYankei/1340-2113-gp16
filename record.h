#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <vector>
#include <cmath>

#ifndef STATUS_H
#define STATUS_H

struct GameState;
string recordGameState(GameState state);
void revertToPreviousState(int currentStateIndex, vector<GameState> &record);
void saveGameProgress(const string& fileName, vector<GameState> record);
void loadGameProgress(int currentStateIndex, string& fileName);

#endif
