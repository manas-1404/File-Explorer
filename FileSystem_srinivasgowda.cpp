#include <iostream>  // Include the I/O stream library
#include <stdexcept> // Include the exception library
#include <vector>
#include <string>
#include <string.h>

#include "FileSystem_srinivasgowda.h"

// #include "LinkedList_srinivasgowda.hpp"
// #include "Queue_srinivasgowda.hpp"

using namespace std; // Correct syntax to use the std namespace

File::File(){
    Filename = "";
    indexList = new LinkedList<int>();
}

File::File(string newFileName)
{
    Filename = newFileName;
    indexList = new LinkedList<int>();
}

string File::getFileName()
{
    return Filename;
}

void File::addBlock(int index)
{
    indexList->add(index);
}

void File::removeBlock(int index)
{
    indexList->remove(index);
}

int File::fileSize()
{
    return indexList->getCurrentSize();
}

// vector<int> File::getFileBlocks()
// {
//     vector<int> indexes;
//     Node<int>* temp = indexList.getHead();
//     while (temp != nullptr){
//         indexes.push_back(temp->getData());
//         temp = temp->getNext();
//     }

//     return indexes;
// }

LinkedList<int>* File::getFileBlocks(){
    return indexList;
}

bool File::operator==(const File& other) const {
    // Compare the filenames or any other property that you deem makes files "equal"
    return this->Filename == other.Filename;
}

FileManager::FileManager(int size)
{
    // Allocate memory for the hard drive
    hardDrive = new char[size];
    // memset(hardDrive, 0, size);

    // Initialize the hard drive to zeros using a loop
    for (int i = 0; i < size; ++i){
        // hardDrive[i] = 0;
        blocksAvailable.enqueue(i);
    }

    files = new LinkedList<File>();
}

void FileManager::addFile(string name, string contents)
{
    File newFile(name);

    int index;

    for (int i = 0; i < static_cast<int>(contents.length()); i++)
    {
        index = blocksAvailable.getFront();
        hardDrive[index] = contents[i];
        newFile.addBlock(index);
        blocksAvailable.dequeue();
    }

    // Source of big error
    files->add(newFile);
}

void FileManager::deleteFile(string name)
{
    File fileToDelete = findFileByName(name);

    LinkedList<int>* fileIndexes = fileToDelete.getFileBlocks();

    Node<int>* temp = fileIndexes->getHead();

    int index;

    while(temp != nullptr){
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
