#include <iostream>                     // Include the I/O stream library
#include <stdexcept>                    // Include the exception library
#include <vector>

#include "FileSystem_srinivasgowda.h"
#include "LinkedList_srinivasgowda.hpp"
#include "queue_srinivasgowda.hpp"


using namespace std;                    // Correct syntax to use the std namespace

class File{

private:
    string Filename;
    LinkedList<int> indexList;

public:
    File(string newFileName){
        Filename = newFileName;
    }

    string getFileName(){
        return Filename;
    }

    void addBlock(int index){
        indexList.add(index);
    }

    int fileSize(){
        return indexList.getCurrentSize();
    }

    vector<int> getFileBlocks(){
        vector<int> indexes;
        Node<int>* temp = indexList.getHead();
        while(temp != nullptr){
            indexes.push_back(temp->getData());
            temp = temp->getNext();
        }

        return indexes;
    }
 
};

class FileManager{

private:
    char* hardDrive;
    Queue<int> blocksAvailable;
    LinkedList<File*> files;

public:
    FileManager(int size){
        char hardDrive[size] = {};

        // files = nullptr;

        for(int i = 0; i < size; i++){
            blocksAvailable.enqueue(i);
        }
        
    }

    void addFile(string name, string contents){
        File* newFile = new File(name);

        int index;
        
        for(int i = 0; i < contents.length(); i++){
            index = blocksAvailable.getFront();
            hardDrive[index] = contents[i];
            newFile->addBlock(index);
            blocksAvailable.dequeue();
        }

        // Source of big error
        files.add(newFile);
    }

    void deleteFile(string name){
        Node<File*>* temp = files.getHead();
        while(temp != nullptr){
            if(temp->getData()->getFileName() == name){
                vector<int> indexToDelete = temp->getData()->getFileBlocks();

                for(int i = 0; i < indexToDelete.size(); i++){
                    
                }

                files.remove(temp->getData());
            }
        }
    }

};