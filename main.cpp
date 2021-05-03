// Raghav Pillai, RSP180007 -- Project 4 (Physics Calculator)

// Preprocessor directives
#include <iostream> // Input and output management
#include <iomanip> // Output formatting
#include <fstream> // File streams
#include <sstream> // String streams
#include <cctype> // is[DIGIT/ALPHA] functions
#include <cmath> // Power/exponent

// Class headers
#include "Node.h"
#include "Stack.h"

using namespace std;

            // VANITY FUNCTIONS

bool isOperator(char op) { // Input char, returns if the char is a math operator or not
    switch (op) { // Switch cases for each operator
        case '+':
        case '-':
        case '/':
        case '*':
        case '(': 
        case ')': 
        case '^':
            return true; // Return true if an operator
    }

    return false; // Return false if not an operator
}

bool isGreaterPrecedence(char op, char newOp){ // Input currnet operator and operator to judge, returns if the operator has greater precedence
    if( op == '+' || op == '-'  ){ // Addition and subtraction
        if( newOp == '('){ // Right
            return true;
        }
    
    }else if( op == '/' || op == '*' ){ // Mult and Div
        if( newOp == '+' || newOp == '-' ){ // Add and sub
            return true;
        }
        if( newOp == '('){ // Right
            return true;
        }
    }else if( op == '^'){ // Exponent
        if( newOp == '+' || newOp == '-' ){ // Add and sub
            return true;
        }
        if( newOp == '/' || newOp == '*' ){ // Division and mult
            return true;
        }
        if( newOp == '('){ // Right
            return true;
        }
    }

    return false; // Returns true if greater precedence, returns false if not greater
}

bool isEqualPrecedence(char op, char newOp){ // Input currnet operator and operator to judge, returns if the operator has equal precedence
    if( op == '+' || op == '-'  ){ // Addition and subtraction
        if( newOp == '+' || newOp == '-'){
            return true;
        }
    
    }else if( op == '/' || op == '*' ){ // Div and Mult
        if( newOp == '/' || newOp == '*' ){
            return true;
        }
    }else if( op == '^'){ // Exponent
        if( newOp == '^'){
            return true;
        }
    }

    return false;// Returns true if equal precedence, returns false if not equal
}

            // LOGIC FUNCTIONS

void interpretInput(string word, Stack* stack, string &notation){ // Interprets an individual string input, inputs are the word from stringstream, pointer to stack and notation by reference
    if(isOperator(word[0]) ){ // If operator -- When operator encountered, pop the stack until an operator of lower precedence is on top of the stack or the stack is empty
        char ourOperator = word[0]; // String to char
        char firstOperator = (stack->getHead())->getOperator(); // Gets the head operator

        if(firstOperator == '0'){ // If stack is empty
            Node *temp = new Node(0, ourOperator);
            *stack << temp;
        
        }else if(ourOperator == '('){ // Open bracket
            Node *temp = new Node(0, ourOperator);
            *stack << temp;
        
        }else if(ourOperator == ')'){ // Close bracket
            while(firstOperator != '(' && firstOperator != '0'){ // While the head operator isn't a paranthesis or the temporary node
                const Node* holder = new Node();
                *stack >> holder;
                notation = notation + holder->getOperator() + " ";

                firstOperator = (stack->getHead())->getOperator();
                delete holder;
            }

            if (firstOperator == '('){ // If the next operator is the initial paranthesis
                const Node* holder = new Node();
                *stack >> holder;
                delete holder;
            }
            
        }else if( isGreaterPrecedence(ourOperator, firstOperator) ){ // If operator of greater precedence
            Node *temp = new Node(0, ourOperator);
            *stack << temp; // Push node with operator onto stack

        }else if(isEqualPrecedence(ourOperator, firstOperator)){ // If operator is equal
            // Pop from stack
            const Node* holder = new Node();
            *stack >> holder;

            notation = notation + holder->getOperator() + " "; // Get popped's value and put on notation

            delete holder;

            // Push new op
            Node *temp = new Node(0, ourOperator);
            *stack << temp;
            
        }else{ // If operator is of lower precedence
            // Pop from stack
            const Node* holder = new Node();
            *stack >> holder;

            if(firstOperator != '('){ // If the operator at the head of the stack is opening paranthesis
                notation = notation + holder->getOperator() + " "; // Append to notation
            }

            delete holder;

            // Push new op
            if( (stack->getHead())->getOperator() == ourOperator){ // If the operator is the equivalent to the head of stack
                notation = notation + ourOperator + " ";
            }else{ // If not equivalent then push to stack
                Node *temp = new Node(0, ourOperator);
                *stack << temp;
            }

        }

    }else{ // If operand, push right to string
        notation = notation + word + " ";
    }
}

void solvePostFix(string expression, Stack* stack){ // Solve the inputted postfix, inputs are the postfix expression and pointer to stack
    stringstream stream(expression); // Convert to an expression for easy loop
    string word;
    
    while(stream >> word){ // Stringstream loop
        char query = word[0]; // Get first char to see if it's an operator

        if( !isOperator(query) ){ // If not operator then push to stack
            Node *temp = new Node(stod(word), '0');
            *stack << temp;
        }else if ( isOperator(query) ){ // If an operator
            // Pop the 2 values off the stack
            const Node *header2 = new Node(); // first value in becomes value 2
            *stack >> header2;

            const Node *header1 = new Node(); // second value in becomes value 1
            *stack >> header1;
            
            // Setup values to be switched so last out is second operand
            double operand1 = header1->getOperand();
            double operand2 = header2->getOperand();
            double toAdd = 0;

            delete header1;
            delete header2;

            // Perform operation from operator
            if(query == '+'){
                toAdd = operand1 + operand2;
            }else if(query == '-'){
                toAdd = operand1 - operand2;
            }else if(query == '*'){
                toAdd = operand1 * operand2;
            }else if(query == '/'){
                toAdd = operand1 / operand2;
            }else if(query == '^'){
                toAdd = pow(operand1, operand2);
            }
            
            // Pop the outputted value back on top of the stack
            Node *temp = new Node(toAdd, '0');
            *stack << temp;
        }
    }
    
    // Get top stack value
    const Node *temp = new Node();
    *stack >> temp;
    double total = temp->getOperand(); // Get the operand

    delete temp;

    // Display finished
    cout << expression << "\t" << fixed << setprecision(3) << total << endl;
}

            // INPUT FUNCTIONS

string inputToConverted(string input){ // Input string, returns formatted string for stringstream 
    string output = "";

    for(size_t i = 0 ; i < input.length(); ++i) { // Loop to put spaces for easy stringstream operation
        if( isOperator(input[i]) ){ // If operator
            output += input.substr(i, 1) + " ";

        }else if (isdigit(input[i]) && isOperator(input[i+1]) ) { // if the char is a digit and the next is an operator
            output += input.substr(i, 1) + " ";

        }else{
            output += input.substr(i, 1);
        }
    }

    return output;
}

void readLine(string line){ // Read the individual line, input is the string line from file input
    // Setup head and stack with the head input
    Node *head = new Node();
    Stack *stackA = new Stack(head);

    string input = inputToConverted(line); // Convert the line to line with spaces for stringstream
    stringstream stream(input); // Setup stringstream with formatted line
    string word;
    string notation = ""; // Notation to pass by reference

    // Pop stack if precedence is higher or equal
    while(stream >> word){
        interpretInput(word, stackA, notation); // Interpret each word from the stringstream
    }

    // Empty stack
    while( (*stackA->getHead()).getOperator() != '0' ){ // Loop through stack until defined blank header node
        const Node* holder = new Node();
        *stackA >> holder;
        notation = notation + holder->getOperator() + " ";
    }

    solvePostFix(notation, stackA); // Solve the postfix converted line

    delete stackA; // Delete stack
}

void getInput(){
    fstream inFile; // Setup input file
    
    string fileName; // String to hold filename
    cin >> fileName; // Ask user for filename
    //fileName = "test.txt"; // Debug
    
    inFile.open(fileName); // Open from filename

    string line; // Temporary line
    
    if (inFile.is_open()){
        while(getline(inFile, line)){ // Get each line of the inputted file
            readLine(line); // Interpret the line
        }
    }
    
    inFile.close(); // Close file
}

int main(){
    getInput(); // Get the input
    
    return 0;
}
