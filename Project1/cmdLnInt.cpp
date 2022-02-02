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

        cin >> input;
        size_t pos = 0;
        
        while ((pos = input.find(delim)) != string::npos) {
            commands.push_back(input.substr(0,pos));
            input.erase(0, pos + delim.length());
        }
        
        for (const auto &w : commands) {
            cout << w << endl;
        }
        
        break;

        if(input == "x") break;  // exit program if user enters exit shell command

        // insert string parsing stuff

        

        // check to see if multiple commands were entered
        if(input.find_first_of(';') >= 0) {
            // chop into substring?? this might need to be recursive idk

            // create array of input substrings??
        }

        if(input == "ls") {
            // process will be created to execute ls()
            ls();
            continue;  // prob not a good idea bc piping
        }

        if(input == "mkdir")
        /*
        if(input begins with "sort") {
            // process created to execute sort()
            sort();
            continue;
        }
        */

    
    }
    return 0;
}
