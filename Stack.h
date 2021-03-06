// Define files
#ifndef STACK_H
#define STACK_H

// Preprocessor directives
#include <iostream>

// Header files
#include "Node.h"

using namespace std;

class Stack{
    public:
        Stack(); // Default constructor
        Stack(Node* origin); // Overloaded constructor (node pointer parameter, assigns head to node passed in)

        friend void deleteList(Node* origin); // Recursive destructor
        ~Stack(); // Destructor (deletes linked list)

        Stack(Stack const &origObject); // Copy constructor

        Node* getHead() const; // Accessor
        void setHead(Node* newHead); // Mutator
        
        friend void operator<<(Stack& inputStack, Node* newHead); // Push
        friend void operator>>(Stack& inputStack, const Node* &holder); // Pop

        friend ostream& operator<<(ostream& os, const Stack& inputStack); // Display
    private:
        Node* head; // Head pointer
};

#endif
