#ifndef FILESYSTEM_SRINIVASGOWDA_H
#define FILESYSTEM_SRINIVASGOWDA_H

#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include "LinkedList_srinivasgowda.hpp"


class File {
private:
    string Filename;                   
    LinkedList<int> indexList;              

public:
    File(string newFileName); 
    string getFileName(); 
    void addBlock(int index);
    int fileSize(); 
    vector<int> getFileBlocks(); 
};

class FileManager{
private:
    char* hardDrive;
    Queue<int> blocksAvailable;
    LinkedList<File*> files;

public:
    FileManager(int size);
    void addFile(string name, string contents);
    void deleteFile(string name);
    string readFile(string name);
    vector<string> getFileNames();

protected:
    File* findFileByName(string name);

}

#endif // FILE_H
