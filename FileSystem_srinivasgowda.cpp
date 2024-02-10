#include <iostream>                     // Include the I/O stream library
#include <stdexcept>                    // Include the exception library
#include <vector>
#include "LinkedList_srinivasgowda.hpp"

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