/*
 * =========================================================================================
 * Name        : eventLib.cpp
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - Bach Khoa University
 * Description : Library for Assignment 2 - Data structures and Algorithms - Spring 2018
 *               This library contains functions used for event management
 * =========================================================================================
 */

#include "requestLib.h"

/// NOTE: each event will be separated by spaces, or endline character
void loadRequests(char* fName, L1List<VRequest> &rList) {
    ifstream inFile(fName);

    if (inFile) {
        string line;
        while (getline(inFile , line)) {
            /// On Windows, lines on file ends with \r\n. So you have to remove \r
            if (line[line.length() - 1] == '\r')
                line.erase(line.length() - 1);
            if (line.length() < 1) continue;

            istringstream iss(line);
            while (iss) {
                string sub;
                iss >> sub;
                if (sub.length()) {
                    if (sub.back() == ';') sub.pop_back();
                    rList.insertHead(VRequest(sub));
                }
            }
        }
        rList.reverse();
        inFile.close();
    }
    else {
        cout << "The file is not found!";
    }
}

void** distributeCODE(char code[REQUEST_CODE_SIZE]) {
    void** pR = new void* [MAX_PARAM_SIZE];
    char* token;
    token = strtok(code, "_");
    pR[0] = token;
    int i = 0;
    while(token != NULL) {
        i++;
        token = strtok(NULL, "_");
        pR[i] = token;
        if(!token) break;
    }
    return pR;
}
/*
bool check(char param[REQUEST_CODE_SIZE]) {
    int size = strlen(param);
    int count = 0;
    int i = 0;
    while(i < size) {
        
    }
}
*/
char* getRequestID(char codeID[REQUEST_CODE_SIZE]) {
    return codeID + 3;
}
bool isFloat(char myString[REQUEST_CODE_SIZE]) {
    if (myString[strlen(myString) - 1] == '.') return false;
    stringstream iss(myString);
    float f;
    iss >> noskipws >> f;
    return iss.eof() && !iss.fail();
}