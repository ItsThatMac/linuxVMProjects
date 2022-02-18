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
    vector<vector<string>> commands{};

    while(1) {
        
        // display user input prompt
        cout << "\n> ";

        commands.clear();  // clear command vector for new input

        getline(cin, input);  // get entire input entered by user (including spaces) and store in string variable called input
        size_t pos1, pos2, pos3 = 0;
        
        vector<string> temp{};
        while((pos1 = input.find("; ")) != string::npos) {
            temp.push_back(input.substr(0, pos1));
            input.erase(0, pos1 + 2); 
        }
        temp.push_back(input);

        vector<string> cmd{};
        for(int i = 0; i < temp.size(); i++) {
            cmd.clear();
            while((pos2 = temp[i].find_first_of(' ')) != string::npos) {
                cmd.push_back(temp[i].substr(0, pos2));
                temp[i].erase(0, pos2 + 1);
            }
            cmd.push_back(temp[i]);
            commands.push_back(cmd);
        }

        cout << "size of commands vector: " << commands.size() << endl;
/*
        vector<string>::iterator it;
        for(int i = 0; i < commands.size(); i++) {
            //cout << "commands[" << i << "] (" << commands[i].size() << ") = ";
            for(int j = 0; j < commands[i].size(); j++) {
                //cout << "|" << commands[i][j] << "|" << " (" << commands[i][j].size() << ")" << " ";
                if(commands[i][j].size() == 0) {
                    it = commands[i].begin() + j;
                    commands[i].erase(it);
                }
            }
            //cout << endl;
        }
*/     
        // print commands vector (for debugging purposes)
        for(int i = 0; i < commands.size(); i++) {
            cout << "commands[" << i << "] (" << commands[i].size() << ") = ";
            for(int j = 0; j < commands[i].size(); j++) {
                cout << "|" << commands[i][j] << "|" << " (" << commands[i][j].size() << ")" << " ";
            }
            cout << endl;
        }
        
        //break;

        //int i = 0;  // used for iteration through commands vector
        
        
        for(int i = 0; i < commands.size(); i++) {

            // exit command line interpreter program
            if(commands[i][0] == "quit") {
                return 0;
            }

            // print path of current directory
            if(commands[i][0] == "pwd") {
                cout << pwd() << endl;
                //i += 1;
                continue;
            }

            // display list of the current directory's contents
            if(commands[i][0] == "ls") {
                system(commands[i][0].c_str());  // convert command from string to char array, then use system() to execute command
                //i += 1;
                continue;
            }

            // create a new emtpy directory within current directory, name of new directory is specified by user
            if(commands[i][0] == "mkdir") {
                mkdir(commands[i][1].c_str(), 0777);  // convert user's desired directory name to char array
                //i += 2;
                continue;
            }

            // remove an empty directory specified by user
            if(commands[i][0] == "rmdir") {
                // construct path string of directory to delete by adding directory name to the end of the current path
                string dirPath = pwd().append("/");
                dirPath.append(commands[i][1]);

                // convert path from string to char array, if rmdir() returns 0, then removal was successful
                if(rmdir(dirPath.c_str()) == 0) {
                    //i += 2;
                    continue;
                }
                else {
                    cout << "rmdir: failed to remove \'" << commands[i][1] << "\'" << endl;  // notify user if unsuccessful
                    //i += 2;
                    continue;
                }
            }

            // ignore any spaces before or after a command/prompt again if no input is entered
            //if(commands[i][j] == " " || "") {
                //i += 1;
                //continue;
            //}
        }
    
    }
    return 0;
}
