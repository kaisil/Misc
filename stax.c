#include <stdio.h>
#include <stdlib.h>

#define SIZE 10
#define EMPTY -1

//a stack implemented using an array

struct stack {
  int items[SIZE];
  int top;
};

void initialize(struct stack* stackPtr);
int push(struct stack* stackPtr, int value);
int pop(struct stack* stackPtr);
int top (struct stack* stackPtr);
int empty(struct stack* stackPtr);
int full(struct stack* stackPtr);

int main(){

int i = 0;
struct stack myStack;

//set up the stack
initialize(&myStack);

//populate the stack
for(i = 0; i < 10; i++){
  push(&myStack, i);
}

printf("top of stack value = %d\n", top(&myStack));

for(i = 0; i < 10; i++){
  printf("popping value = %d\n", pop(&myStack));
}

if(empty(&myStack)){
  printf("The stack is empty.\n");
}

if(full(&myStack)){
  printf("The stack is full.\n");
}

return 0;
}

//sets "top" equal to -1 since first elements will be at index 0
void initialize(struct stack* stackPtr){
  stackPtr->top = -1;
}

//push onto the stack if there's enough room to do so
int push(struct stack* stackPtr, int value){
  //check if there's space to push, return 0 if stack is full
  if(full(stackPtr)){
    return 0;
  }
  //if there's room, copy the value into the next location for the top of the stack
  stackPtr->items[stackPtr->top+1] = value;
  (stackPtr->top)++;
  //return 1 if push was successful
  return 1;
}

//pop off the stack as long as it's not empty
int pop(struct stack* stackPtr){
  //check if stack is empty
  if(empty(stackPtr)){
    return -1;
  }

  //temporary variable saves the original value at top of stack
  int retVal;
  retVal = stackPtr->items[stackPtr->top];
  //change the top value to reflect the change
  (stackPtr->top)--;

  return retVal;
}

//check the top value of the stack
int top (struct stack* stackPtr){
  //check if stack is empty
  if(empty(stackPtr)){
    return -1;
  }
  //return the top item in the stack
  return stackPtr->items[stackPtr->top];
}

//checks if the stack has no elements
int empty(struct stack* stackPtr){
  return(stackPtr->top == -1);
}

//checks if the stack is full
int full(struct stack* stackPtr){
  return(stackPtr->top == SIZE - 1);
}
