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
8. date: print current date
9. cat: create a new file and write to it or print a single file
10. cd: change current working directory

## Additional Notes on Inputting Commands
### Running multiple commands
This command line interpreter allows the user to run multiple commands in a single line by placing a ';' between commands. Commands will be run in the order they were entered. Spaces before or after the semicolon do not affect output.
```
> pwd; mkdir myDir; ls
```
*This will print the path of the current directory, create a new empty directory named 'myDir', then display a list of the current directory's contents*.
### cat
The 'cat' command can be used to print the contents of a single file.
```
> cat myFile.txt
```
*This will display the contents of myFile.txt*.  

It can also be used to create a new file and write to it using the '>' operator. The text entered beneath the command will be written to the file until **CTRL + C** is entered *on a new line*. If the file name passed in already exists in the current directory, that file will be overwritten.
```
> cat > newFile.txt
this is a new file
created with the cat command
^C
```
*This will create a file called 'newFile.txt' which will contain the two lines under the command*.
