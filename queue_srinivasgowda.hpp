#ifndef QUEUE_SRINIVASGOWDA_HPP
#define QUEUE_SRINIVASGOWDA_HPP

#include <iostream>                     // Include the I/O stream library
#include <stdexcept>                    // Include the exception library

using namespace std;                    // Correct syntax to use the std namespace

//Declaring a templated Class Node
template<typename T> class Node {

//properties of Node class are made private
private:
    T item;                                     //declared item of type T
    Node<T>* next;                              //declared next of type node

//methods of Node class are made public
public:
    //Overloaded constructor for creating the Node
    Node(T newItem){
        item = newItem;                         //storing item of this to newItem
        next = nullptr;                         //pointing next to null
    }
    
    //Getter method for item
    T getItem() {
        return item;                            //return item back
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

//Declaring a templated Class Queue
template<typename T> class Queue{

//properties of Queue class are made private
private:
    int count;                                  //declared count of type int which stores the count of the number of items in Queue
    Node<T>* front;                             //declared front of type Node<T> which is the head of the Queue

//methods of Queue class are made public
public:

    //Default constructor for creating the Queue
    Queue(){
        count = 0;                                              //initializing count to 0
        front = nullptr;                                        //initializing front to null
    }

    //Destructor for memory management
    ~Queue() {
        empty();                                                //call the empty() method of Queue
    }   

    //Method which will add new items to the Queue
    void enqueue(T item){
        Node<T>* newNode = new Node<T>(item);             //Creating a new Node Object
        
        //if front = null, then the Queue is empty initially 
        if(front == nullptr){
            newNode->setNext(front);                            //pointing newNode.next to front
            front = newNode;                                    //pointing front to newNode
            count++;                                            //increasing count by 1, because we just added an item
        }

        //Queue not empty, so add the next Item to the end
        else{
            Node<T>* temp = front;                           //initializing temp (temporary node) by pointing to the front              
            
            //keep iterating till temp.next is not pointing to null
            while(temp->getNext() != nullptr){
                temp = temp->getNext();                         //pointing temp to temp.next, because we need to iterate through the Singly LinkedList Queue
            }
            
            temp->setNext(newNode);                             //pointing temp.next to newNode
            newNode->setNext(nullptr);                          //pointing newNode.next to null
            count++;                                            //increasing count by 1, because we just added an item
        }
    }

    //Method which will pick a random node and remove it and return the contents of that node. Basically, getting an item out of the Queue
    void dequeue(){
        //checking if the Queue is empty. 
        if (count == 0){
            //Queue is empty so we can't remove any item. Throw a runtime error with a message for User
            throw std::runtime_error("Queue is empty. Cannot remove from an empty Queue.");
        }

        //Queue not empty, so remove some item

        Node<T> *removedNode = nullptr;                      //initializing and pointing removedNode to null
        removedNode = front;                                //pointing removedNode to front
        front = front->getNext();                           //pointing front to front.next
        
        delete removedNode;                                     //deleting removedNode to free the memory back to system
        count--;                                                //decreasing count by 1 because we removed a Node
    }

    T getFront(){
        return front->getItem();
    }

    //Method which will return count of number of items in Queue
    int size(){
        return count;                                           //return the count of number of items in Queue
    }

    //Method wihch is used to empty the Queue and free up the memoey to the system
    void empty(){
        count = 0;                                              //resetting count to 0, since everything will be removed
        
        //keep iterating till front is not pointing to null
        while (front != nullptr){
            Node<T>* temp = front;                           //initializing a temp node and pointing it to front, this temp will be used to delete the node after moving the front forward in the doubly-linkedlist
            front = front->getNext();                           //pointing front to next node by getting next node. basically, moving forward in the doubly-linkedlist
            temp->setNext(nullptr);                             //pointing temp.next to null
            delete temp;                                        //deleting the temp node. basically the former front node
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