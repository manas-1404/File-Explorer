#include <iostream>                                         //Include the I/O stream library
#include <stdexcept>                                        //Include the exception library
#include <vector>                                           //Include the vector library
#include <string>                                           //Include the string library
#include <string.h>                                         //Include the string.h library

/*
Name: Manas Srinivas Gowda
ASU ID: 1225612596
Date: 19 February 2024
Description: This class is the implementation of File and FileManager Classes and contains all the required methods
*/ 

//include FileSystem Header File
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

        //storing the available index with the front Queue method
        index = blocksAvailable.getFront();

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

        //storing the index of the current character
        index = temp->getData();

        //enqueue the index so that it is free for future use
        blocksAvailable.enqueue(index);

        //pointing temp to temp.next, because we need to iterate through the LinkedList
        temp = temp->getNext();
    }

    //remove the File object from the FIleManager Linkedlist
    files->remove(fileToDelete);
}

//Method that looks up a file and return the contents of that file
string FileManager::readFile(string name){
    
    string text = "";                        //initializing text to read
    int index;                               //initializing index of HardDrive

    //Finding the file object which needs to be read
    File fileToRead = findFileByName(name);

    //retrieving the LinkedList containing the indexes which points to the characters that make up the file contents
    LinkedList<int>* fileIndexes = fileToRead.getFileBlocks();

    //Accessing the head of the linkedlist
    Node<int>* temp = fileIndexes->getHead();

    //Iterating through the Linkedlist till we find the file to be read 
    while(temp != nullptr){

        //storing the index of the current character
        index = temp->getData();

        //concatenating the text character by character
        text = text + hardDrive[index];

        //pointing temp to temp.next, because we need to iterate through the LinkedList
        temp = temp->getNext();
    }

    //return the file contents back to the calling function
    return text;
}

//Method that gets all the file names out as a vector
vector<string> FileManager::getFileNames(){

    vector<string> vectorNames;                            //initializing a vector of type string which will store all the file names as a vector

    //Accessing the head of the linkedlist
    Node<File>* temp = files->getHead();

    //Iterating through the Linkedlist till we find the file to be read
    while (temp != nullptr){

        //appending the names to the vector 
        vectorNames.push_back(temp->getData().getFileName());

        //pointing temp to temp.next, because we need to iterate through the LinkedList
        temp = temp->getNext();
    }

    //return the names in the form of a vector
    return vectorNames;
}

//Method that returns the size of a file
int FileManager::getfileSizes(string name){

    //Finding the file object which needs to be found
    File searchFile = findFileByName(name);

    //Storing the file size by using the fileSize() method
    int index = searchFile.fileSize();

    //return the index back
    return index;
}

//Method to search for a File object and return it
File FileManager::findFileByName(string name) {

    int flag = -1;                                      //initializing the flag tp -1
    File searchFile;                                    //initializing searchFile
    Node<File>* temp = files->getHead();                //Accessing the head of the linkedlist

    //Iterating through the Linkedlist till we find the file to be read
    while (temp != nullptr){

        //checking the name of the current file is actually what we are looking for
        if (temp->getData().getFileName() == name){

            //storing file object in searchFile
            searchFile = temp->getData();
            flag = 1;                                   //setting flag to 1
            break;                                      //break the while loop
        }

        //pointing temp to temp.next, because we need to iterate through the LinkedList
        temp = temp->getNext();
    }

    //File is not found if flag remains -1
    if(flag == -1){
        throw std::runtime_error("File Not Found");
    }

    //returning the found file
    return searchFile;
}
