# Project 1: Improved UNIX/Linux Command Line Interpreter

## Install and Run
1. Install g++ by entering ```sudo apt install g++``` into your Linux terminal.
2. Download zip file of code, then unzip and save to the desired location.
3. In your Linux terminal, navigate to the chosen directory using the cd command: ```cd filepath```. If you have not yet mounted the file system where the directory resides, use ```cd /mnt/filepath```.
4. Compile the program by entering ```g++ -o start cmdLnInt.cpp -lstdc++fs```.
5. Enter ```./start``` to run the program.

## Commands Implemented
1. quit: exit command line interpreter
2. ls: display a list of the current directory's contents
3. pwd: print path of current directory
4. mkdir: create a new empty directory within current directory
5. rmdir: remove an empty directory within current directory
6. df: display how much space is available on your system
7. free: display how much RAM is available on your system

### How to input
Here are a few examples on how to input commands that require additional input
- mkdir  
takes in a name for the new directory
```
mkdir newdir
```
this will create a new directory named newdir
