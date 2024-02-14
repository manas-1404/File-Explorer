#include <iostream>                     // Include the I/O stream library
#include <stdexcept>                    // Include the exception library
#include <cstdlib>

#include "FileSystem_srinivasgowda.h";


using namespace std;                    // Correct syntax to use the std namespace

void printMenu(){
    int option;

    while (option != 0){
        cout << "Menu:" << endl;
        cout << "1 – Show files on hard drive" << endl;
        cout << "2 – Add a file" << endl;
        cout << "3 – Delete a file" << endl;
        cout << "4 – Output a file" << endl;
        cout << "0 – Exit simulation" << endl;
        cout << "Enter your option: ";
        cin >> option;

        if(option == 1){
            
        }
    }
}

int main(int argc, char *argv[]){
    
    int sizeHardDrive;

    if(argc == 3 && argv[1] == "-s"){
        sizeHardDrive = atoi(argv[2]);
    }

    else if(argc == 5 && argv[1] == "-s" && argv[3] == "-f"){
        sizeHardDrive = atoi(argv[2]);
        string fileDetail = argv[4];

        int colonIndex = fileDetail.find(":");

        string name = fileDetail.substr(0,colonIndex);
        string contents = fileDetail.substr(colonIndex + 1);

        cout << "Hello" << endl;

    }

    else{
        throw std::runtime_error("Command Line Argument Specs not met!!");
    }

    FileManager stupid(sizeHardDrive);

    

};