#include <iostream>
#include <vector>
#include "saveload.h"
#include "actions.h"
#include "structures.h"
#include "reverse.h"
using namespace std;

bool deleteLastStep(vector<action> record, card pyramid[21], card deck[15]){
    if (record.size() == 0){
        cout << "No previous step." << endl;
        return false;
    }
    else {
        action step = record.back();
        int index1 = step.index1;
        int index2 = step.index2;
        switch (step.type){
            case 1:
                pyramid[index1].status = 2;
            break;
            case 2:
                pyramid[index1].status = 2;
                pyramid[index2].status = 2;
            break;
            case 3:
                deck[index1].status = 2;
            break;
            case 4:
                pyramid[index1].status = 2;
                deck[index2].status = 2;
            break;
            case 5:
                deck[index1].status = 2;
                deck[index2].status = 2;
            break;
        }
        record.pop_back();
        return true;
    }
}