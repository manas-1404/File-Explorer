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

    void removeBlock(int index){
        indexList.remove(index);
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
                vector<int> indexesToDelete = temp->getData()->getFileBlocks();

                int indexHardDrive;

                //For loop to access each and every index in the LinkedList
                for(int i = 0; i < indexesToDelete.size(); i++){
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

    string readFile(string name){
        Node<File*>* temp = files.getHead();

        string text = "";

        int indexHardDrive;
        while(temp != nullptr){
            if(temp->getData()->getFileName() == name){
                vector<int> indexesToRead = temp->getData()->getFileBlocks();

                for(int i = 0; i < indexesToRead.size(); i++){
                    indexHardDrive = indexesToRead[i];
                    text = text + hardDrive[indexHardDrive];
                }

            }

            temp = temp->getNext();
        }

        return text;
    }

    vector<string> getFileNames(){
        vector<string> vectorNames;

        Node<File*>* temp = files.getHead();

        while(temp != nullptr){
            vectorNames.push_back(temp->getData()->getFileName());
            temp = temp->getNext();
        }

        return vectorNames;
    }

protected:
    File* findFileByName(string name){
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

};