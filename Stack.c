#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 5

typedef struct Node {
    int data;
    struct Node* next;
}Node;

/**
* This method adds a new node to the top of the stack.
* @param    top     referance to the top node of the stack
* @param    data    the data that will be added to stack
*/
void push(Node** top, int data) {
    // if stack is full print to stdout and return
    if (stackIsFull(*top)) {
        printf("Stack is full, can't add -> %d\n", data);
        return;
    }
    // if stack is empty create a new node, assign the data and make next pointer NULL
    if (isEmpty(*top)) {
        *top = (Node *)malloc(sizeof(Node));
        (*top)->next = NULL;
        (*top)->data = data;
    } else {
        /* Create a new node, assign the data, make next pointer last node
        and make this node the new top node of the stack */ 
        Node* newNode = (Node *)malloc(sizeof(Node));
        newNode->data = data;
        newNode->next = (*top);
        (*top) = newNode;
    }   

}

/**
* This method prints the elements of stack.
* @param    top     top node of the stack
*/
void printStack(Node* top) {
    // if the stack is empty, print to stdout and return
    if (isEmpty(top)) {
        printf("Stack is empty\n");
        return;
    }
    while (top != NULL) {
        printf("%d ", top->data);
        top = top->next;
    }
    printf("\n");
}

/**
* This method checks the stack if it is empty or not
*
* @param    top     top node of the stack
* @return   1 if stack is empty, otherwise 0
*/
int isEmpty(Node *top) {
    if (!top) {
        return 1;
    }
    return 0;
}

/**
* This method removes the top node of stack
* @param    top     referance to the top node of the stack
* @return   -1 if stack is empty otherwise the data of removed node
*/
int pop(Node** top) {
    // if the stack is empty return -1
    if (isEmpty(*top)) {
        return -1;
    }
    Node* temp = (*top);
    int value = (*top)->data;
    (*top) = (*top)->next;
    free(temp);
    return value;
}

/**
* This method gets the size of the stack
*
* @param    top     top node of the stack
* @return   size of the stack
*/
int getStackSize(Node* top) {
    if (isEmpty(top)) return 0;
    int size = 0;
    while (top != NULL) {
        size++;
        top = top->next;
    }
    return size;
}

/**
* This method checks the stack if full
*
* @param    top     top node of the stack
* @return   1 if stack is full otherwise 0.
*/
int stackIsFull(Node* top) {
    return getStackSize(top) == MAX_STACK_SIZE;
}

/**
* This method reverses the stack.
* @param    top     referance to the top node of the stack
*/
void reverseStack(Node** top) {
    Node* current = *top;
    Node* prev = NULL;
    Node* next = NULL;

    while (current != NULL) {
        // storing the next node
        next = current->next;

        // point to previous node with next pointer of current (reversing next pointer)
        current->next = prev;

        // prepare prev pointer for the next loop
        prev = current;

        // point current to saved next pointer
        current = next;
    }
    // make last element top element of stack
    *top = prev;
}

/**
* This method checks the data of the top node.
* @param    top     top node of the stack
* @return   INT_MIN if stack is empty otherwise data of the top node
*/
int peek(Node* top) {
    if (isEmpty(top)) return INT_MIN;

    return top->data;
}

int main() {
    Node* top = NULL;
    printf("is empty = %d\n",isEmpty(top));
    printf("size = %d\n",getStackSize(top));

    printStack(top);
    push(&top,5);
    push(&top,45);
    push(&top,3);
    push(&top,123);
    printStack(top);
    printf("peeked = %d\n",peek(top));
    printf("size = %d\n",getStackSize(top));
    printf("popped = %d\n",pop(&top));
    printStack(top);
    printf("peeked = %d\n",peek(top));
    printStack(top);
}