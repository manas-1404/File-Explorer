#ifndef QUEUE_SRINIVASGOWDA_HPP
#define QUEUE_SRINIVASGOWDA_HPP

/*
Name: Manas Srinivas Gowda
ASU ID: 1225612596
Date: 19 February 2024
Description: This class is the implementation of Queue Class and contains all the required methods
*/ 

#include <iostream>                     //Include the I/O stream library
#include <stdexcept>                    //Include the exception library
#include <string>                       //Include the string library

using namespace std;                    // Correct syntax to use the std namespace

//Declaring a templated Class QueueNode
template<typename T> class QueueNode {

//properties of QueueNode class are made private
private:
    T item;                                             //declared item of type T
    QueueNode<T>* next;                                 //declared next of type node

//methods of QueueNode class are made public
public:
    //Overloaded constructor for creating the QueueNode
    QueueNode(T newItem){
        item = newItem;                                 //storing item of this to newItem
        next = nullptr;                                 //pointing next to null
    }
    
    //Getter method for item
    T getItem() {
        return item;                                    //return item back
    }

    //Getter method for get Next
    QueueNode<T>* getNext() {
        return next;                                    //return next QueueNode in the Queue
    }

    //Setter method which sets the next of the QueueNode
    void setNext(QueueNode<T>* newQueueNode) {
        next = newQueueNode;                            //storing the pointer of next QueueNode
    }
};

//Declaring a templated Class Queue
template<typename T> class Queue{

//properties of Queue class are made private
private:
    int count;                                          //declared count of type int which stores the count of the number of items in Queue
    QueueNode<T>* front;                                //declared front of type QueueNode<T> which is the head of the Queue
    QueueNode<T>* tail;                                 //declared tail of type QueueNode<T> which is the tail of the Queue. Used tail to make the code more efficient. 

//methods of Queue class are made public
public:

    //Default constructor for creating the Queue
    Queue(){
        count = 0;                                              //initializing count to 0
        front = nullptr;                                        //initializing front to null
        tail = nullptr;                                         //initializing tail to null
    }

    //Destructor for memory management
    ~Queue() {
        empty();                                                //call the empty() method of Queue
    }   

    //Method which will add new items to the end of the Queue
    void enqueue(T item){
        QueueNode<T>* newQueueNode = new QueueNode<T>(item);             //Creating a new QueueNode Object
        
        //if front = null, then the Queue is empty initially 
        if(front == nullptr){
            front = newQueueNode;                                       //pointing front to newQueueNode
            tail = newQueueNode;                                        //pointing tail to newQueueNode
            count++;                                                    //increasing count by 1, because we just added an item
        }

        //Queue not empty, so add the next Item to the end
        else{
            tail->setNext(newQueueNode);                                //pointing tail.next to newQueueNode
            tail = newQueueNode;                                        //pointing tail to newQueueNode
            tail->setNext(nullptr);                                     //pointing tail.next to null
            count++;                                                    //increasing count by 1, because we just added an item
        }
    }

    //Method which will remove the first QueueNode and return the contents of that node. Basically, getting an item out of the Queue
    void dequeue(){
        //checking if the Queue is empty. 
        if (count == 0){
            //Queue is empty so we can't remove any item. Throw a runtime error with a message for User
            throw std::runtime_error("Queue is empty. Cannot remove from an empty Queue.");
        }

        //Queue not empty, so remove some item

        QueueNode<T> *removedQueueNode = front;                 //initializing and pointing removedQueueNode to front
        front = front->getNext();                               //pointing front to front.next

        //If the queue is now empty, update the tail pointer as well
        if (front == nullptr) {                                 
            tail = nullptr;
        }
        
        delete removedQueueNode;                                        //deleting removedQueueNode to free the memory back to system
        count--;                                                        //decreasing count by 1 because we removed a QueueNode
    }

    //Method which will return the first element of the Queue
    T getFront(){
        return front->getItem();                                        //return the data of the first element of the queue
    }

    //Method which will return count of number of items in Queue
    int size(){
        return count;                                                   //return the count of number of items in Queue
    }

    //Method wihch is used to empty the Queue and free up the memoey to the system
    void empty(){
        count = 0;                                                      //resetting count to 0, since everything will be removed
        
        //keep iterating till front is not pointing to null
        while (front != nullptr){
            QueueNode<T>* temp = front;                                 //initializing a temp node and pointing it to front, this temp will be used to delete the QueueNode after moving the front forward in the Queue
            front = front->getNext();                                   //pointing front to next node by getting next node. basically, moving forward in the Queue
            temp->setNext(nullptr);                                     //pointing temp.next to null
            delete temp;                                                //deleting the temp node. basically the former front node
        }

        //after the Queue is empty, pointing front to null to ensure no lose pointers are remaining
        front = nullptr;                                        
    }

    //Method which will return true or false based on the number of items in the Queue
    bool isEmpty(){
        //No items in Queue. Empty Queue.
        if(count == 0){
            return true;                        //return true because it's empty
        }
        //Some items are there in the Queue
        else{
            return false;                       //return false because it's not empty
        }
    }
};

#endif
