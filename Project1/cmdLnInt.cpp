#include <iostream>
#include <unistd.h>
#include <bits/stdc++.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <string>
#include <vector>
//#include <filesystem>

using namespace std;
//namespace fs = std::filesystem;

void ls() {
    // using filesystem library
    //for (auto const& dir_entry : fs::directory_iterator(".")) {cout << dir_entry << endl;}

    // using Linux system() function
    char command[50] = "ls";
    system(command);
}
/*
string pwd() {
    // use filesystem library to get current path
    fs::path p = fs::current_path();
    return p.string();  // convert the variable from type path object, to string and return
}
*/
int main() {

    string input;
    string delim = "; ";
    vector<string> commands{};

    while(1) {
        cout << "\n> ";

        getline(cin, input);
        size_t pos = 0;
        
        commands.clear();  // clear command array for new input
        
        // check for ;
        if(input.find_first_of(';') != string::npos) {
            while ((pos = input.find(delim)) != string::npos) {
                commands.push_back(input.substr(0,pos));
                input.erase(0, pos + delim.length());
            }
        }
        // else check for space
        else if(input.find_first_of(' ') != string::npos) {
            // while a blank character exists in the string
            while((pos = input.find_first_of(' ')) != string::npos) {
                commands.push_back(input.substr(0, pos));  // push a substring of input that is the string before the space into the command array
                input.erase(0, pos + 1);  // delete previously pushed substring from input, and delete the space as well
            }
            commands.push_back(input);  // push remaining input string
        }
        // else the command input was a single string
        else {
            commands.push_back(input);
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

            /*if(commands[i] == "pwd") {
                cout << pwd() << endl;
                i += 1;
                continue;
            }*/


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
