/***********************************************
Project 1: UNIX/Linux Command Line Interpreter
Ethan Macalaguim and Kayla Zantello
CST-315: Operating Systems
February 6, 2022

Commands implemented:
quit
ls
pwd
mkdir
rmdir
***********************************************/
#include <iostream>
#include <string>
#include <vector>
#include <experimental/filesystem>
#include <unistd.h>
#include <sys/stat.h>

using namespace std;
namespace fs = std::experimental::filesystem;

// returns path of current directory as a string
string pwd() {
    fs::path p = fs::current_path();   // use filesystem library to get current path
    return p.string();  // convert the variable from type path object to string and return
}

int main() {

    string input;
    vector<string> commands{};

    while(1) {

        // display user input prompt
        cout << "\n> ";

        getline(cin, input);  // get entire input entered by user (including spaces) and store in string variable called input
        size_t pos = 0;
        
        commands.clear();  // clear command vector for new input
        
        // while a blank character exists in the string
        while((pos = input.find_first_of(' ')) != string::npos) {
            commands.push_back(input.substr(0, pos));  // push a substring of input that is the string before the space into the command vector
            input.erase(0, pos + 1);  // delete substring from above line from input, and delete the space as well
        }
        commands.push_back(input);  // push remaining input string
        
        // print commands vector (for debugging purposes)
        for (const auto &w : commands) {
            //cout << w << endl;
        }

        int i = 0;  // used for iteration through commands vector

        while(i < commands.size()) {

            // exit command line interpreter program
            if(commands[i] == "quit") {
                return 0;
            }

            // print path of current directory
            if(commands[i] == "pwd") {
                cout << pwd() << endl;
                i += 1;
                continue;
            }

            // display list of the current directory's contents
            if(commands[i] == "ls") {
                system(commands[i].c_str());  // convert command from string to char array, then use system() to execute command
                i += 1;
                continue;
            }

            // create a new emtpy directory within current directory, name of new directory is specified by user
            if(commands[i] == "mkdir") {
                mkdir(commands[i + 1].c_str(), 0777);  // convert user's desired directory name to char array
                i += 2;
                continue;
            }

            // remove an empty directory specified by user
            if(commands[i] == "rmdir") {
                // construct path string of directory to delete by adding directory name to the end of the current path
                string dirPath = pwd().append("/");
                dirPath.append(commands[i + 1]);

                // convert path from string to char array, if rmdir() returns 0, then removal was successful
                if(rmdir(dirPath.c_str()) == 0) {
                    i += 2;
                    continue;
                }
                else {
                    cout << "rmdir: failed to remove \'" << commands[i + 1] << "\'" << endl;  // notify user if unsuccessful
                    i += 2;
                    continue;
                }
            }

            // ignore any spaces before or after a command/prompt again if no input is entered
            if(commands[i] == " " || "") {
                i += 1;
                continue;
            }
        }
    
    }
    return 0;
}
