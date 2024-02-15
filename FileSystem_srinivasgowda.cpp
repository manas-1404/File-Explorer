#include <iostream>                     // Include the I/O stream library
#include <stdexcept>                    // Include the exception library
#include <vector>
#include <string>
#include <string.h>

#include "FileSystem_srinivasgowda.h"

// #include "LinkedList_srinivasgowda.hpp"
// #include "Queue_srinivasgowda.hpp"


using namespace std;                    // Correct syntax to use the std namespace


    File::File(string newFileName){
        Filename = newFileName;
    }

    string File::getFileName(){
        return Filename;
    }

    void File::addBlock(int index){
        indexList.add(index);
    }

    void File::removeBlock(int index){
        indexList.remove(index);
    }

    int File::fileSize(){
        return indexList.getCurrentSize();
    }

    vector<int> File::getFileBlocks(){
        vector<int> indexes;
        Node<int>* temp = indexList.getHead();
        while(temp != nullptr){
            indexes.push_back(temp->getData());
            temp = temp->getNext();
        }

        return indexes;
    }
 


    FileManager::FileManager(int size){
        // hardDrive[size] = {};

        hardDrive = new char[size];
        memset(hardDrive, 0, size);

        LinkedList<File*> files;

        for(int i = 0; i < size; i++){
            blocksAvailable.enqueue(i);
        }
        
    }

    void FileManager::addFile(string name, string contents){
        File* newFile = new File(name);

        int index;
        
        for(int i = 0; i < static_cast<int>(contents.length()); i++){
            index = blocksAvailable.getFront();
            hardDrive[index] = contents[i];
            newFile->addBlock(index);
            blocksAvailable.dequeue();
        }

        // Source of big error
        files.add(newFile);
    }

    void FileManager::deleteFile(string name){
        Node<File*>* temp = files.getHead();
        while(temp != nullptr){
            if(temp->getData()->getFileName() == name){
                vector<int> indexesToDelete = temp->getData()->getFileBlocks();

                int indexHardDrive;

                //For loop to access each and every index in the LinkedList
                for(int i = 0; i < static_cast<int>(indexesToDelete.size()); i++){
                    indexHardDrive = indexesToDelete[i];
                    
                    hardDrive[indexHardDrive] = ' ';

                    blocksAvailable.enqueue(indexHardDrive);

                    //deleting the indexList (LinkedList stored in the File Object)
                    temp->getData()->removeBlock(indexHardDrive);
                }

                //deletes the file object
                files.remove(temp->getData());
            }

            temp = temp->getNext();
        }
    }

    string FileManager::readFile(string name){
        Node<File*>* temp = files.getHead();

        string text = "";

        int indexHardDrive;
        while(temp != nullptr){
            if(temp->getData()->getFileName() == name){
                vector<int> indexesToRead = temp->getData()->getFileBlocks();

                for(int i = 0; i < static_cast<int>(indexesToRead.size()); i++){
                    indexHardDrive = indexesToRead[i];
                    text = text + hardDrive[indexHardDrive];
                }

            }

            temp = temp->getNext();
        }

        return text;
    }

    vector<string> FileManager::getFileNames(){
        vector<string> vectorNames;

        Node<File*>* temp = files.getHead();

        while(temp != nullptr){
            vectorNames.push_back(temp->getData()->getFileName());
            temp = temp->getNext();
        }

        return vectorNames;
    }

    vector<int> FileManager::getFileSizes(){
        vector<int> vectorSizes;

        Node<File*>* temp = files.getHead();

        while(temp != nullptr){
            vectorSizes.push_back(temp->getData()->fileSize());
            temp = temp->getNext();
        }

        return vectorSizes;
    }

    File* FileManager::findFileByName(string name){
        File* searchFile;
        Node<File*>* temp = files.getHead();

        while( temp != nullptr ){
            if(temp->getData()->getFileName() == name){
                searchFile = temp->getData();
            }

            temp = temp->getNext();
        }

        return searchFile;
    }
