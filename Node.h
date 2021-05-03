// Define files
#ifndef NODE_H
#define NODE_H

// Preprocessor directives
#include <iostream>

class Node{
    public:
        Node(); // Default constructor
        Node(double operandTo, char operatorTo); // Overloaded constructor

        double getOperand() const; // Accessor
        char getOperator() const; // Accessor
        Node* getNext() const; // Accessor

        void setOperand(double operandTo); // Mutator
        void setOperator(char operatorTo); // Mutator
        void setNext(Node* nextTo); // Mutator
    private:
        double operandValue; // Operand value (#)
        char operatorValue; // Operator value (+/-/*)
        Node* next; // Next node for linked list
};

#endif
