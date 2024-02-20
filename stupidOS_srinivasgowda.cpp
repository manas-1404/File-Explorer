#include <iostream>                                     //Include the I/O stream library
#include <iomanip>                                      //Include the I/O manip library
#include <stdexcept>                                    //Include the exception library
#include <cstdlib>                                      //Include the cstdlib library
#include <string>                                       //Include the string library
#include <fstream>                                      //Incude the fstream library

/*
Name: Manas Srinivas Gowda
ASU ID: 1225612596
Date: 19 February 2024
Description: This class is the implementation of Main Method and contains all the required methods
*/ 

//include FileSystem Header File
#include "FileSystem_srinivasgowda.h"

using namespace std;                                    //Correct syntax to use the std namespace

//Method which will print the Menu for the program
void printMenu(){
    cout << "Menu:" << endl;
    cout << "1 - Show files on hard drive" << endl;
    cout << "2 - Add a file" << endl;
    cout << "3 - Delete a file" << endl;
    cout << "4 - Output a file" << endl;
    cout << "0 - Exit simulation" << endl;
}

//Main Driver Method
int main(int argc, char *argv[]){
    
    int sizeHardDrive;                                  //initializing hardDrive Size

    string file;                                        //initializing file of type string which will read the file through command line
    string fileDetail;                                  //initializing fileDetail of type string which will read all the contents of the file
    string FileName = " ";                              //initializing FileName of type string which will store the name of the file
    string FileContents = " ";                          //initializing FileContents of type string which will store all the contents of the file
    
    int colonIndex;                                     //initializing colonIndex of type int which will contain the index of the colon in the file

    //checking if the command line arguments just contain 3 arguments and the 2nd argument is -s tag    
    if(argc == 3 && string(argv[1]) == "-s"){
        
        sizeHardDrive = atoi(argv[2]);                  //storing sizeHardDrive from the 3rd argument 
    }

    //checking if the command line arguments just contain 5 arguments and the 2nd argument is -s tag and 4th argument is -f tag
    else if(argc == 5 && string(argv[1]) == "-s" && string(argv[3]) == "-f"){
        
        sizeHardDrive = atoi(argv[2]);                  //storing sizeHardDrive from the 3rd argument 

        file = argv[4];                                 //storing file from the 5th argument 
    }

    //user entered the command line arguments wrong
    else{

        //throw error to the user that the command line doesnt match
        throw std::runtime_error("Command Line Argument Specs not met!!");
    }

    //initializing FileManager stupid containing sizeHardDrive
    FileManager stupid(sizeHardDrive);
    
    //checking if the number of command line arguments are 5
    if(argc == 5){

        //Opening the file using the file provided through command line argument
        ifstream inputFile(file);

        //checking if file can be opened
        if (inputFile.is_open()){

            //trying to use while loop to read each and every line
            while (getline(inputFile, fileDetail)) {

                //finding the colon in the line just read
                colonIndex = fileDetail.find(":");

                //checking if the colon is actually present in the line
                if (colonIndex != static_cast<int>(string::npos)){

                    //colon is present in the line

                    //extracting the FileName using substr
                    FileName = fileDetail.substr(0, colonIndex);   

                    //extracting the FileContent using substr             
                    FileContents = fileDetail.substr(colonIndex + 1);

                    //using addFile to create and add files to stupid (stupidOS lol)
                    stupid.addFile(FileName, FileContents);
                }

                //colon is not present in the current line of the file
                else{
                    cerr << "Invalid line format in file: " << fileDetail << endl;
                }
            }

            inputFile.close();              //closing the opened file
        }

        //file couldn't be opened
        else{
            throw std::runtime_error("Failed to open file: " + file);
        }
    }

    int option = -1;                        //initializing option to -1

    //using while loop to run the menu driven program. the loop should run atleast once so options = -1
    while (option != 0){

        //print the Menu using a function
        printMenu();

        cin >> option;                      //input the option from the user

        //user entered option = 1, show files
        if(option == 1){
            
            //intializing fileNames as a vector because we are gonna store the file names in it 
            vector<string> fileNames = stupid.getFileNames();

            int size;                      //initializing size of the file

            //printing the Filename and the Size with the required size
            cout << left << setw(40) << "Filename";
            cout << right << setw(14) << "size" << endl;

            //traversing through the vector to access the filename
            for(int i = 0; i < static_cast<int>(fileNames.size()); i++){

                //printing filename 
                cout << left << setw(40) << fileNames[i];

                //storing the size of the file using the getfileSizes method 
                size = stupid.getfileSizes(fileNames[i]);

                //printing file size
                cout << right << setw(10) << size << " blk" << endl;
            }
        }

        //user entered option = 2, add file
        else if(option == 2){
            string name;                                    //initializing name 
            string content;                                 //initializing content

            //Asking user to input filename using cin
            cout << "Enter filename: ";
            cin >> name;

            //Asking user to input content using cin
            cout << "Enter content string: ";
            cin >> content;

            //call addFile method to create and add the file using name and contents
            stupid.addFile(name, content);
        }

        //user entered option = 3, delete file
        else if(option == 3){
            string name;                                    //initializing name

            //Asking user to input filename using cin
            cout << "Enter filename: ";
            cin >> name;

            //call deleteFile method to delete the file using name
            stupid.deleteFile(name);
        }

        //user entered option = 4, read file
        else if(option == 4){
            string name;                                    //initializing name

            //Asking user to input filename using cin
            cout << "Enter filename: ";
            cin >> name;

            //printing the Filename and the Contents
            cout << left << setw(30) << "Filename";
            cout << left <<setw(0) << "Contents" << endl;

            //call readFile method to read the file
            string content = stupid.readFile(name);

            //printing file name
            cout << left << setw(30) << name;

            //printing file content
            cout << right << content << endl;
        }

        //any other option, exit the loop
        else{
            break;
        }
    }

    return -1;
};