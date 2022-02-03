#include <iostream>
#include <unistd.h>
#include <bits/stdc++.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <string>
#include <vector>

using namespace std;

// functions may need to have return value in order to pipe command

void ls() {
    cout << "*lists all files in current directory*" << endl;
    // probably some sort of built in function to use?
}

void sort(string file) {
    cout << "*alphabetically sorts strings in file*" << endl;
    // get file passed in (ifstream?)
    // while loop inserts each string of file into array
    // array is sorted then displayed
}


int main() {

    string input;
    string delim = "; ";
    vector<string> commands{};

    while(1) {
        cout << "\n> ";

        //cin >> input;
        getline(cin, input);
        cout << input << endl;
        size_t pos = 0;
        
        commands.clear();
        while ((pos = input.find(delim)) != string::npos) {
            commands.push_back(input.substr(0,pos));
            input.erase(0, pos + delim.length());
        }
        
        for (const auto &w : commands) {
            //cout << w << endl;
        }
        
        //break;

        // if no input was entered, display prompt again by returning to top of loop
        if(commands.size() == 0) {
            continue;
        }

        int i = 0;  // used for iteration through commands vector

        while(i < commands.size()) {

            if(commands[i] == "quit") {
                return 0;
            }

            if(commands[i] == "ls") {
                ls();
                i += 1;
                continue;
            }

            if(commands[i] == "mkdir") {
                int n = commands[i + 1].length();  // variable to hold length of directory name char array
                char dirName[n + 1];  // declare char array
                strcpy(dirName, commands[i + 1].c_str());  // copy string to char array

                mkdir(dirName, 0777);  // make directory using name specified by user
                i += 2;
                continue;
            }
        }
    
    }
    return 0;
}
