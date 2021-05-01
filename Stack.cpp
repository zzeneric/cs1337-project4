#include <iostream>
#include "Stack.h"
#include "Node.h"
using namespace std;

Stack::Stack(){ // Default constructor
    head = nullptr;
}

Stack::Stack(Node* origin){ // Overloaded constructor
    head = origin;
}

Stack::~Stack(){ // Delete
    //cout << "DELETING: " << endl;
    Node* current = head;
    Node* next;

    while (current != nullptr) {
        //cout << "Destroyed: " << current->getOperand() << endl;
        next = current->getNext();
        delete current;
        current = next;
    }
}

Stack::Stack(Stack const &origObject){ // Copy constructor
    Node* origHead = origObject.getHead();
    
    Node* newHead = new Node();
    newHead->setOperand(origHead->getOperand());
    newHead->setOperator(origHead->getOperator());

    Node* current = origHead->getNext();
    Node* lastNode = newHead;

    while (current != nullptr) {
        Node* newNode = new Node();
        newNode->setOperand(current->getOperand());
        newNode->setOperator(current->getOperator());
        lastNode->setNext(newNode);

        lastNode = newNode;
        current = current->getNext();
    }
    
    head = newHead;
}

Node* Stack::getHead() const{ // Get head
    return head;
}

void Stack::setHead(Node* newHead){ // Set head
    head = newHead;
}

void operator<<(Stack& inputStack, Node* newHead){ // Push
    if(inputStack.getHead() != nullptr){
        Node* head = inputStack.getHead();

        Node* temp = new Node();

        temp->setOperand(newHead->getOperand());
        temp->setOperator(newHead->getOperator());

        newHead->setOperand(head->getOperand());
        newHead->setOperator(head->getOperator());

        head->setOperand(temp->getOperand());
        head->setOperator(temp->getOperator());

        delete temp;
 
        newHead->setNext(head->getNext());
        head->setNext(newHead);
    }else{
        inputStack.setHead(newHead);
    }

    
}

void operator>>(Stack& inputStack, const Node* &holder){ // Pop
    Node* toPop = inputStack.getHead();
    inputStack.setHead(toPop->getNext());  

    holder = toPop;
    cout << "POPPED2: " << &holder << " " << holder->getOperand() << holder->getOperator() << endl;
    cout << &holder << endl;
}

ostream& operator<<(ostream& os, const Stack& inputStack){ // Display
    Node* head = inputStack.getHead();
    Node* temp;

    if (head == nullptr){
        os << "No items left in stack!";
    }else{
        temp = head;
        while (temp != nullptr){
            if(temp->getOperator() != '0'){
                os << temp->getOperator();
            }else if(temp->getOperand() != 0){
                os << temp->getOperand();
            }
            

            temp = temp->getNext();
            if(temp != nullptr){
                os << ", ";
            }
        }
    }
    return os;
}
