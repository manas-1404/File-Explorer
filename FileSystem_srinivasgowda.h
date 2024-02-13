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

#endif // FILE_H
