#ifndef FILESYSTEM_SRINIVASGOWDA_H
#define FILESYSTEM_SRINIVASGOWDA_H

#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>

#include "LinkedList_srinivasgowda.hpp"
#include "Queue_srinivasgowda.hpp"
// #include "FileSystem_srinivasgowda.cpp"


class File {
private:
    string Filename;                   
    LinkedList<int>* indexList;              

public:
    File();
    File(string newFileName); 
    string getFileName(); 
    void addBlock(int index);
    void removeBlock(int index);
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
    // vector<int> getFileSizes();

protected:
    File findFileByName(string name);

};

#endif