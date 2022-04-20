#include "myLib.h"


vector <string> TeleProg::split(string line,char del){
    string str = "";
    vector <string> parts;
    line += del;
    for (int i = 0;i < line.length();i++){
        if (line[i] == del){
            if (str.length() > 0){
                parts.push_back(str);
            }
            str = "";        }
        else
            str+=line[i];
    }
    return parts;
}

int lengthOfProgram(TeleProg prog){
    int length = (prog.h_end * 60 + prog.m_end) - (prog.h_start * 60 + prog.m_start);
    return length;
}

string nameOfFile(){
    string name;
    cout << "Enter name of file: ";
    cin >> name;
    return name;
}

bool isInBase(TeleProg prog, vector <TeleProg> base) {
    for (int i = 0; i < base.size(); i++) {
        if (base[i].NameOfProgram == prog.NameOfProgram) return true;
        else if ((base[i].h_end*60 + base[i].m_end > prog.h_end*60 + prog.m_end) && (prog.h_end * 60 + prog.m_end > base[i].h_start*60 + base[i].m_start))
            return true;
        else if ((prog.h_start*60 + prog.m_start < base[i].h_start * 60 + base[i].m_start) && (prog.h_end * 60 + prog.m_end > base[i].h_end * 60 + base[i].m_end))
            return true;
        else if ((base[i].h_start * 60 + base[i].m_start < prog.h_start * 60 + prog.m_start) && (prog.h_start * 60 + prog.m_start < base[i].h_end * 60 + base[i].m_end))
            return true;
    }
    return false;
}

void create(string name){
    char mode;
    string text;
    vector<TeleProg> base;
    ifstream fileif;
    cout << "Would you like to append your input?If so,enter 'a'.Otherwise enter 'w'" << endl;
    cin >> mode;
    while(true) {
        if (mode == 'a') {
            char letter;
            fileif.open(name, ios::binary);
            if (fileif.is_open()) {
                while (fileif.read((char *) &letter, sizeof(char))) {
                    if (letter == ' ') {
                        base.push_back(text);
                        text = "";
                    }
                    text += letter;
                }
                cout << "Error" << endl;
            }
            fileif.close();
            break;
        }
        else if(mode == 'w'){
            break;
        }
        while (mode != 'a' && mode != 'w'){
            cout << "Enter correct letter: " << endl;
            cin >> mode;
        }
    }
    ofstream fileof(name,ios::binary);
    string line;
    cout << "Enter the data as (name h:m h:m) \n To end the line | press ---> ENTER\n To end the input | input ---> 'end'" << endl;
    cin.ignore();
    getline(cin, line);
    while(line != "end"){
        TeleProg program (line);
        if (base.size() == 0){
            base.push_back(program);
            getline(cin,line);
            continue;
        }
        if (!isInBase(program,base)){
            base.push_back(program);
        }
        else{
            cout << "Enter not repeating name or not overlapping time" << endl;
        }
        getline(cin,line);
    }
    for(int i = 0;i < base.size();i++){
        fileof.write(base[i].text.c_str(),base[i].text.length());
    }
    fileof.close();
}

void output (string name){
    ifstream fileif(name,ios::binary);
    char letter;
    while(fileif.read((char*)&letter,sizeof (char))){
        cout << letter;
    }
    fileif.close();
}
void show_list(string name){
    ifstream fileif (name,ios::binary);
    string line = "";
    char letter;
    while(fileif.read((char*)&letter,sizeof (char))){
        if(letter == '\n'){
            TeleProg program(line);
            cout << "the name: " << program.NameOfProgram << "| " << "the length: " << lengthOfProgram(program)/60 << " hours and " << lengthOfProgram(program)%60 << " minutes" << endl;
            line = "";
        }
        line += letter;
    }
    cout << "___________________________________" << endl;
    fileif.close();
}

void newfile(string name) {
    ifstream fileif(name, ios::binary);
    ofstream fileof("out_file.txt",ios::binary);
    vector<TeleProg> base;
    string line;
    char letter;
    while (fileif.read((char *) &letter, sizeof(char))) {
        if (letter == '\n') {
            TeleProg program(line);
            if ((program.h_start >= 9) && ((program.h_end< 18) || (program.h_end == 18 && program.m_end == 0))){
                base.push_back(program);
            }
            line = "";
        }
        line += letter;
    }
    for(int i = 0;i < base.size(); i++){
        fileof.write(base[i].text.c_str(),base[i].text.length());
    }
    fileof.close();
    fileif.close();
}