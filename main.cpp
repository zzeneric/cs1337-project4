#include <iostream>
#include "Stack.h"
#include "Node.h"

using namespace std;

int main()
{
    Node *head = new Node(1, 'A');
    Stack *stackA = new Stack(head);

    Node *node1 = new Node(2, 'B');
    Node *node2 = new Node(3, 'C');
    Node *node3 = new Node(4, 'D');
    
    *stackA << node1;
    *stackA << node2;
    *stackA << node3;

    cout << *stackA << endl;
    cout << endl;

    const Node* holder = new Node();
    *stackA >> holder;
    
    cout << "POPPED1: " << &holder << " " << holder->getOperand() << holder->getOperator() << endl;

    //Stack *stackB = new Stack();
    //*stackB << node1;

    //cout << *stackB << endl;
    delete holder;

    return 0;
}
