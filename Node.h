#ifndef NODE_H
#define NODE_H

#include <iostream>
using namespace std;

class Node{
    public:
        Node();
        Node(double operandTo, char operatorTo);

        double getOperand() const; // Accessor
        char getOperator() const; // Accessor
        Node* getNext() const; // Accessor

        void setOperand(double operandTo); // Mutator
        void setOperator(char operatorTo); // Mutator
        void setNext(Node* nextTo); // Mutator
    private:
        double operandValue;
        char operatorValue;
        Node* next;
};

#endif
