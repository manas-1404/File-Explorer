#include <iostream>                                         //Include the I/O stream library
#include <stdexcept>                                        //Include the exception library
#include <vector>                                           //Include the vector library
#include <string>                                           //Include the string library
#include <string.h>                                         //Include the string.h library

// include FileSystem Header File
#include "FileSystem_srinivasgowda.h"


using namespace std;                                        //Correct syntax to use the std namespace

//Default constructor for FIle Class
File::File(){
    Filename = "";                                          //initializing Filename to ""               
    indexList = new LinkedList<int>();                      //initializing new LinkedList containing integer
}

//Overloaded Constructor
File::File(string newFileName){
    Filename = newFileName;                                 //initializing Filename to newFileName while creating a object
    indexList = new LinkedList<int>();                      //initializing new LinkedList containing integer
}

//Getter for FileName
string File::getFileName(){
    return Filename;                                        //return Filename
}

//Method adds an index to the linked list
void File::addBlock(int index){
    
    //Call the add method of the linkedlist to add the index
    indexList->add(index);
}

//Method returns how big the file is (linkedlist size)
int File::fileSize(){

    //return the size of the linkedlist
    return indexList->getCurrentSize();
}

//Method returns the indexes that make up the file
LinkedList<int>* File::getFileBlocks(){

    //return the entire linkedlist
    return indexList;
}

//Method to check if 2 objects are equal
bool File::operator==(const File& other) const {

    //returning the result of the comparison of 2 objects
    return this->Filename == other.Filename;
}

//Overloaded constructor for FIleManager Class
FileManager::FileManager(int size){

    //Allocating memory for the hard drive with the size
    hardDrive = new char[size];

    //Initializing the queue to store available index using a for loop
    for (int i = 0; i < size; ++i){
        blocksAvailable.enqueue(i);
    }

    //initializing new LinkedList containing File object
    files = new LinkedList<File>();
}

//Method that builds a new file, puts the contents on the hard drive and in the files linkedlist
void FileManager::addFile(string name, string contents){
    File newFile(name);                         //Creating a new File Object with the name

    int index;                                  //initializing index of HardDrive

    //for loop to traverse through each and every character in the string contents
    for (int i = 0; i < static_cast<int>(contents.length()); i++){

        //storing the available index with the peek Queue method
        index = blocksAvailable.peek();

        //storing the character in the hardDrive at index position 
        hardDrive[index] = contents[i];

        //Adding the current hardDrive index containing the current character to the File Linkedlist
        newFile.addBlock(index);

        //Dequeue to remove the used up memory block from queue
        blocksAvailable.dequeue();
    }

    //Adding the File object to the FileManager linkedlist
    files->add(newFile);
}

//Method that deletes a file and put the chunks that file used to occupy back into the blocksAvailable queue
void FileManager::deleteFile(string name){

    //Storing the file to delete File Object
    File fileToDelete = findFileByName(name);

    //Storing the linkedlist of the characters which make up the file. the character index linkedlist is returned with getFileBlocks method
    LinkedList<int>* fileIndexes = fileToDelete.getFileBlocks();

    //initializing a temp node and pointing it to head of File characters Linkedlist
    Node<int>* temp = fileIndexes->getHead();

    int index;                              //initializing index of HardDrive

    //Iterating through the Linkedlist  till we find the last element
    while(temp != nullptr){

        //storing the index of the 
        index = temp->getData();
        blocksAvailable.enqueue(index);
        temp = temp->getNext();
    }

    files->remove(fileToDelete);
}

string FileManager::readFile(string name)
{
    string text = "";
    int index;

    File fileToRead = findFileByName(name);

    LinkedList<int>* fileIndexes = fileToRead.getFileBlocks();

    Node<int>* temp = fileIndexes->getHead();

    while(temp != nullptr){
        index = temp->getData();
        text = text + hardDrive[index];
        temp = temp->getNext();
    }

    return text;
}

vector<string> FileManager::getFileNames()
{
    vector<string> vectorNames;

    Node<File>* temp = files->getHead();

    while (temp != nullptr){
        vectorNames.push_back(temp->getData().getFileName());
        temp = temp->getNext();
    }

    return vectorNames;
}

int FileManager::getfileSizes(string name){
    File searchFile = findFileByName(name);

    int index = searchFile.fileSize();

    return index;
}

// vector<int> FileManager::getFileSizes()
// {
//     vector<int> vectorSizes;

//     Node<File>* temp = files->getHead();

//     while (temp != nullptr){
//         vectorSizes.push_back(temp->getData().fileSize());
//         temp = temp->getNext();
//     }

//     return vectorSizes;
// }

File FileManager::findFileByName(string name)
{
    int flag = -1;
    File searchFile;
    Node<File>* temp = files->getHead();

    while (temp != nullptr)
    {
        if (temp->getData().getFileName() == name)
        {
            searchFile = temp->getData();
            flag = 1;
            break;
        }

        temp = temp->getNext();
    }

    if(flag == -1){
        throw std::runtime_error("File Not Found");
    }

    return searchFile;
    
}
