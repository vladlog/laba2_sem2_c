#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;


struct TeleProg{
    string NameOfProgram,text;
    int h_start,m_start,h_end,m_end;
    vector <string> split(string line,char del);
    TeleProg(string line){
        text = line + '\n';
        vector<string> parts = split(line,' ');
        NameOfProgram = parts[0];
        h_start = stoi(split(parts[1],':')[0]);
        m_start = stoi(split(parts[1],':')[1]);
        h_end = stoi(split(parts[2],':')[0]);
        m_end = stoi(split(parts[2],':')[1]);
    }
};

string nameOfFile();
void create(string );
void output(string );
void show_list(string );
void newfile(string );
int lengthOfProgram(TeleProg prog);