#include "Node.h"
#include <iostream>
using namespace std;

Node::Node(){ // Default constructor
    operandValue = 0;
    operatorValue = '0';
    next = nullptr;
}

Node::Node(double operandTo, char operatorTo){ // Overloaded constructor
    operandValue = operandTo;
    operatorValue = operatorTo;
}

double Node::getOperand() const{ // Accessor for operand
    return operandValue;
}

char Node::getOperator() const{ // Accessor for operator
    return operatorValue;
}

Node* Node::getNext() const{ // Accessor for next
    return next;
}

void Node::setOperand(double operandTo){ // Mutator for operand
    operandValue = operandTo;
}

void Node::setOperator(char operatorTo){ // Mutator for operator
    operatorValue = operatorTo;
}

void Node::setNext(Node* nextTo){ // Mutator for next
    if(nextTo == NULL)
        next = NULL;
    else
        next = nextTo;
}
