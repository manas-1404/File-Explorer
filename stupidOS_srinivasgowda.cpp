#include <iostream>                     // Include the I/O stream library
#include <iomanip>
#include <stdexcept>                    // Include the exception library
#include <cstdlib>
#include <string>

#include "FileSystem_srinivasgowda.h"
// #include "LinkedList_srinivasgowda.hpp";
// #include "Queue_srinivasgowda.hpp";


using namespace std;                    // Correct syntax to use the std namespace

void printMenu(){

    cout << "Menu:" << endl;
    cout << "1 - Show files on hard drive" << endl;
    cout << "2 – Add a file" << endl;
    cout << "3 – Delete a file" << endl;
    cout << "4 – Output a file" << endl;
    cout << "0 – Exit simulation" << endl;
}

int main(int argc, char *argv[]){
    
    int sizeHardDrive;

    string FileName = " ";
    string FileContents = " ";

    if(argc == 3 && string(argv[1]) == "-s"){
        sizeHardDrive = atoi(argv[2]);
    }

    else if(argc == 5 && string(argv[1]) == "-s" && string(argv[3]) == "-f"){
        sizeHardDrive = atoi(argv[2]);
        string fileDetail = argv[4];

        int colonIndex = fileDetail.find(":");

        FileName = fileDetail.substr(0,colonIndex);
        FileContents = fileDetail.substr(colonIndex + 1); 

    }

    else{
        throw std::runtime_error("Command Line Argument Specs not met!!");
    }

    FileManager stupid(sizeHardDrive);

    if(argc == 5){
        stupid.addFile(FileName, FileContents);
    }
    

    int option = -1;

    while (option != 0){
        printMenu();
        cout << "Enter your option: ";
        cin >> option;

        if(option == 1){

            vector<string> fileNames = stupid.getFileNames();
            vector<int> fileSizes = stupid.getFileSizes();

            cout << left << setw(40) << "Filename";
            cout << left << setw(40) << "size";

            for(int i = 0; i < static_cast<int>(fileNames.size()); i++){
                cout << left << setw(40) << fileNames[i];

                cout << right << setw(10) << fileSizes[i] << " blk" << endl;
            }
            
        }

        else if(option == 2){
            string name;
            string content;

            cout << "Enter filename: ";
            cin >> name;

            cout << "\nEnter content string: ";
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

            string content = stupid.readFile(name);

            cout << left << setw(30) << name;

            cout << right << content << endl;
        }

        else{
            break;
        }
    }
    

};