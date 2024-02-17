#include <iostream>                     // Include the I/O stream library
#include <iomanip>
#include <stdexcept>                    // Include the exception library
#include <cstdlib>
#include <string>
#include <fstream>

#include "FileSystem_srinivasgowda.h"
// #include "LinkedList_srinivasgowda.hpp";
// #include "Queue_srinivasgowda.hpp";


using namespace std;                    // Correct syntax to use the std namespace

void printMenu(){

    cout << "Menu:" << endl;
    cout << "1 - Show files on hard drive" << endl;
    cout << "2 - Add a file" << endl;
    cout << "3 - Delete a file" << endl;
    cout << "4 - Output a file" << endl;
    cout << "0 - Exit simulation" << endl;
}

int main(int argc, char *argv[]){
    
    int sizeHardDrive;

    string file;
    string fileDetail;
    string FileName = " ";
    string FileContents = " ";
    
    int colonIndex;

    if(argc == 3 && string(argv[1]) == "-s"){
        sizeHardDrive = atoi(argv[2]);
    }

    else if(argc == 5 && string(argv[1]) == "-s" && string(argv[3]) == "-f"){
        sizeHardDrive = atoi(argv[2]);

        file = argv[4];
    }

    else{
        throw std::runtime_error("Command Line Argument Specs not met!!");
    }

    FileManager stupid(sizeHardDrive);
    
    if(argc == 5){

        // Open the file using the name provided as command line argument
        ifstream inputFile(file);

        if (inputFile.is_open()){
            while (getline(inputFile, fileDetail)) {
                colonIndex = fileDetail.find(":");
                if (colonIndex != static_cast<int>(string::npos)){
                    FileName = fileDetail.substr(0, colonIndex);
                    FileContents = fileDetail.substr(colonIndex + 1);
                    stupid.addFile(FileName, FileContents);
                }
                else{
                    cerr << "Invalid line format in file: " << fileDetail << endl;
                }
            }

            inputFile.close();
        }
        else{
            cerr << "Failed to open file: " << file << endl;
            return 1;
        }
    }
    
    // cout << "Hello World. Arguments taken successfully" << endl;

    int option = -1;

    // cout << "\nwhile(option) loop starting now\n" << endl;

    while (option != 0){
        printMenu();
        // cout << "Enter your option: ";
        cin >> option;

        if(option == 1){

            vector<string> fileNames = stupid.getFileNames();
            // vector<int> fileSizes = stupid.getFileSizes();

            int index;

            cout << left << setw(40) << "Filename";
            cout << right << setw(14) << "size" << endl;

            for(int i = 0; i < static_cast<int>(fileNames.size()); i++){
                cout << left << setw(40) << fileNames[i];

                index = stupid.getfileSizes(fileNames[i]);

                cout << right << setw(10) << index << " blk" << endl;
            }
            
        }

        else if(option == 2){
            string name;
            string content;

            cout << "Enter filename: ";
            cin >> name;

            cout << "Enter content string: ";
            cin >> content;

            stupid.addFile(name, content);
        }

        else if(option == 3){
            string name;

            cout << "Enter filename: ";
            cin >> name;

            stupid.deleteFile(name);
        }

        else if(option == 4){
            string name;

            cout << "Enter filename: ";
            cin >> name;

            cout << left << setw(30) << "Filename";
            cout << left <<setw(0) << "Contents" << endl;

            string content = stupid.readFile(name);

            cout << left << setw(30) << name;

            cout << right << content << endl;
        }

        else if(option == 0) {
            
        }
    }
    
    // cout << "Ended the program with errors" << endl;

    return -1;
};