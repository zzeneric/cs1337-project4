// Preprocessor directives
#include <iostream>

// Header files
#include "Stack.h"
#include "Node.h"

using namespace std;

Stack::Stack(){ // Default constructor
    head = nullptr; // Set the head to nothing
}

Stack::Stack(Node* origin){ // Overloaded constructor, input of the origin node for head
    head = origin; // Set the head to the inputted object
}


void deleteList(Node* origin){ // Recursive function to delete nodes, input header
    if (origin == nullptr){ // If there's no more nodes, then return end
        return;
    }
    deleteList(origin->getNext()); // Keep recursively deleting if there's more nodes
}

Stack::~Stack(){ // Delete
    deleteList(head); // Call function to recursively delete nodes from stack
}

Stack::Stack(Stack const &origObject){ // Copy constructor
    Node* origHead = origObject.getHead(); // Get first head
    
    // Get the new head node
    Node* newHead = new Node();
    newHead->setOperand(origHead->getOperand());
    newHead->setOperator(origHead->getOperator());

    // Set the current node to the 2nd node on the list
    Node* current = origHead->getNext();
    Node* lastNode = newHead;

    while (current != nullptr) { // While the node is valid, copy values and move to next node
        Node* newNode = new Node();
        newNode->setOperand(current->getOperand());
        newNode->setOperator(current->getOperator());
        lastNode->setNext(newNode);

        lastNode = newNode;
        current = current->getNext();
    }
    
    head = newHead; // Set the head to the new head
}

Node* Stack::getHead() const{ // Get head
    return head;
}

void Stack::setHead(Node* newHead){ // Set head
    head = newHead;
}

void operator<<(Stack& inputStack, Node* newHead){ // Push
    if(inputStack.getHead() != nullptr){ // If the head isn't null, then set the old head to the 2nd value in the stack
        Node* head = inputStack.getHead();
        Node* temp = new Node();

        // Switch data values
        temp->setOperand(newHead->getOperand());
        temp->setOperator(newHead->getOperator());

        newHead->setOperand(head->getOperand());
        newHead->setOperator(head->getOperator());

        head->setOperand(temp->getOperand());
        head->setOperator(temp->getOperator());

        delete temp; // Delete the temporary node
 
        newHead->setNext(head->getNext());
        head->setNext(newHead);
    }else{ // If the head doesn't exist, make the pushed node the head
        inputStack.setHead(newHead);
    }
}

void operator>>(Stack& inputStack, const Node* &holder){ // Pop
    Node* toPop = inputStack.getHead(); // Get the head of the stack
    inputStack.setHead(toPop->getNext()); // Set the head to the next node, removing the popped node
    holder = toPop; // Set the inputted node to the popped node
}

ostream& operator<<(ostream& os, const Stack& inputStack){ // Display, input outputstream and the stack to display
    Node* head = inputStack.getHead(); // head of stack
    Node* temp; // temporary node

    if (head == nullptr){ // If there's nothing left
        //os << "No items left in stack!";
    }else{
        temp = head; // Set the temporary node to the head
        while (temp != nullptr){ // loop while the temporary node is valid 
            if(temp->getOperator() != '0'){ // If the operator is empty (holder node)
                os << temp->getOperator();
            }else if(temp->getOperand() != 0){
                os << temp->getOperand();
            }
            
            temp = temp->getNext(); // Set the value to the next mode
            if(temp != nullptr){ // If there's a next value, output a comma
                os << ", ";
            }
        }
    }
    return os; // Return the outputstream to display
}
