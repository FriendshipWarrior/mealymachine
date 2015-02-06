//  CS3240 Program 1
//  main.cpp
//  Mealy Macine A.2
//
//  Created by Dustin Hurst on 2/3/15.
//  Copyright (c) 2015 Dustin Hurst. All rights reserved.
//
//  This program will print any input character that is not being commented out (i.e. /*...*/).
//  Will not work for '//' type of commenting.
#include <cassert>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, const char * argv[]) {
    enum State {q0,q1,q2,q3};       /* 4 states for the mealy machine */
    State state = q0;               /* start state is q0 */
    
    ifstream inFile;                /* input file */
    ofstream outFile;               /* output file */
    
    inFile.open("chars.txt");       /* existing file I made called chars.txt */
    
    vector<char> vec;               /* a vector to hold all of the chars from the .txt file */
    char value;
    
    while(inFile >> value){         /* load the chars into the vector */
        vec.push_back(value);
    }
    
    inFile.close();
    outFile.open("newChars.txt");
    
    for (int i = 0; i < vec.size(); i++){
        char c = vec[i];
        
        switch(state){              /* switch statement between states. Won't print commented chars */
            case q0:
                if(c == '/')
                    state = q1;
                else
                    outFile << c;
                break;
            case q1:
                if(c == '/')
                    state = q1;
                else if (c == '*')
                    state = q2;
                else
                    state = q0;
                break;
            case q2:
                if(c == '*')
                    state = q3;
                break;
            case q3:
                if(c =='/')
                    state = q0;
                else if(c == '*')
                    state = q3;
                else
                    state = q2;
                break;
            default:
                break;
        }
    }
    
    outFile.close();
    return 0;
}
