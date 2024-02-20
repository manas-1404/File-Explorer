#ifndef FILESYSTEM_SRINIVASGOWDA_H
#define FILESYSTEM_SRINIVASGOWDA_H

/*
Name: Manas Srinivas Gowda
ASU ID: 1225612596
Date: 19 February 2024
Description: This header file is the class declaration of File and FileManager Classes
*/ 

#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>

#include "LinkedList_srinivasgowda.hpp"
#include "Queue_srinivasgowda.hpp"

class File {
private:
    string Filename;                   
    LinkedList<int>* indexList;              

public:
    File();
    File(string newFileName); 
    string getFileName(); 
    void addBlock(int index);
    int fileSize(); 
    LinkedList<int>* getFileBlocks();
    bool operator==(const File &other) const;
};

class FileManager{
private:
    char* hardDrive;
    Queue<int> blocksAvailable;
    LinkedList<File> *files;

public:
    FileManager(int size);
    void addFile(string name, string contents);
    void deleteFile(string name);
    string readFile(string name);
    int getfileSizes(string name);
    vector<string> getFileNames();

protected:
    File findFileByName(string name);

};

#endif