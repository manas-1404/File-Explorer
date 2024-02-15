#ifndef LINKEDLIST_SRINIVASGOWDA_HPP
#define LINKEDLIST_SRINIVASGOWDA_HPP

#include <string>
#include <iostream>                     // Include the I/O stream library
#include <stdexcept>                    // Include the exception library

#include "FileSystem_srinivasgowda.h"

using namespace std;                    // Correct syntax to use the std namespace

//Declaring a templated Class Node
template<typename T> class Node {

//properties of Node class are made private
private:
    T data;                                     //declared data of type T
    Node<T>* next;                              //declared next of type node

//methods of Node class are made public
public:
    //Overloaded constructor for creating the Node
    Node(T newData){
        data = newData;                         //storing data of this to newData
        next = nullptr;                         //pointing next to null
    }
    
    //Getter method for data
    T getData() {
        return data;                            //return data back
    }

    //Getter method for get Next
    Node<T>* getNext() {
        return next;                            //return next Node in the Queue
    }

    //Setter method which sets the next of the Node
    void setNext(Node<T>* newNode) {
        next = newNode;                         //storing the pointer of next Node
    }
};

template<typename T> class LinkedList{

private:
    int count;
    Node<T>* head;
    // Node<T>* tail;

public:
    LinkedList(){
        int count = 0;
        head = nullptr;
        // tail = nullptr;
    }

    //Method which will return the head of the linkedlist. const because we don't want to change any data structure of the returned pointer
    Node<T>* getHead() const{
        return head;
    }

    // string getFileNameData(){

    // }


    //Method which will add new data to the Node
    void add(T data){
        Node<T>* newNode = new Node<T>(data);                   //Creating a new Node Object
        
        //if head = null, then the Node is empty initially 
        if(head == nullptr){
            newNode->setNext(head);                            //pointing newNode.next to head
            head = newNode;                                    //pointing head to newNode
            // tail = head;
            count++;                                            //increasing count by 1, because we just added an data
        }

        //Node not empty, so add the next data to the end
        else{
            Node<T>* temp = head;                              //initializing temp (temporary node) by pointing to the head              
            
            //keep iterating till temp.next is not pointing to null
            while(temp->getNext() != nullptr){
                temp = temp->getNext();                         //pointing temp to temp.next, because we need to iterate through the Singly LinkedList Node
            }
            
            temp->setNext(newNode);                             //pointing temp.next to newNode
            newNode->setNext(nullptr);                          //pointing newNode.next to null
            count++;                                            //increasing count by 1, because we just added an data
        }
    }


    //Method which will pick a random node and remove it and return the contents of that node. Basically, getting an data out of the Node
    void remove(T data){
        //checking if the Node is empty. 
        if (count == 0){
            //Node is empty so we can't remove any data. Throw a runtime error with a message for User
            throw std::runtime_error("Node is empty. Cannot remove from an empty Node.");
        }

        //LinkedList not empty, so remove some data

        //initializing index which gives the index of the node where the data is present
        int index = getIndexOf(data);

        if(index == -1){
            throw std::runtime_error("FIle not found.");
        }

        //File is found
        Node<T> *removedNode = nullptr;                         //initializing and pointing removedNode to null

        //If index = 0, then we technically removing the first data
        if (index == 0){ 
            removedNode = head;                                 //pointing removedNode to head
            head = head->getNext();                             //pointing head to head.next
        }

        //Basically removing a middle or last data
        else{ 
            Node<T> *temp = head;                               //initializing temp by pointing to the head
            
            //Trying to find the node just before the one to remove
            //SKipping 0th iteration with i = 1, because temp is already pointing to head and we don't need to consider that iteration
            for (int i = 1; i < index; i++){ 
                temp = temp->getNext();                         //pointing temp to temp.next, because we need to iterate through the Singly LinkedList
            }

            removedNode = temp->getNext();                      //pointing removedNode to temp.next
            temp->setNext(removedNode->getNext());              //pointing temp.next to removedNode.next, basically disconnecting the removedNode link and linking the next next node of temp
        }

        delete removedNode;                                     //deleting removedNode to free the memory back to system
        count--;                                                //decreasing count by 1 because we removed a Node
    }

    //Method which will return count of number of data in LinkedList
    int getCurrentSize(){
        return count;                                           //return the count of number of data in Node
    }

    //Method which will return true or false based on the number of data in the Node
    bool isEmpty(){
        //No data in Node. Empty Node.
        if(count == 0){
            return true;                                        //return true because it's empty
        }
        //Some data are there in the Node
        else{
            return false;                                       //return false because it's not empty
        }
    }

    //Method wihch is used to empty the LinkedList and free up the memory to the system
    void empty(){
        count = 0;                                              //resetting count to 0, since everything will be removed
        
        //keep iterating till head is not pointing to null
        while (head != nullptr){
            Node<T>* temp = head;                              //initializing a temp node and pointing it to head, this temp will be used to delete the node after moving the head forward in the linkedlist
            head = head->getNext();                           //pointing head to next node by getting next node. basically, moving forward in the linkedlist
            temp->setNext(nullptr);                             //pointing temp.next to null
            delete temp;                                        //deleting the temp node. basically the former head node
        }

        //after the LinkedList is empty, pointing head to null to ensure no lose pointers are remaining
        head = nullptr;                                        
    }

    int getIndexOf(T data){
        int i = 0;
        
        Node<T>* temp = head;

        while(temp != nullptr){
            if(temp->getData() == data){
                return i;
            }

            temp = temp->getNext();
            i++;
        }

        return -1;
    }


};



#endif