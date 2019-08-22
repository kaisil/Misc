#include <stdio.h>
#include <stdlib.h>

//a stack implemented using a linked list
//doesnt need a "top" in constructor like array version because top is always the first node
//doesnt need a defined size since LL exists in heap memory

struct stack {
  struct stack *next;
  int data;
};

void init(struct stack **front);
int empty(struct stack *front);
int push(struct stack **front, int num);
struct stack* pop(struct stack **front);
int top(struct stack *front);

int main(){

  int num = 0;
  struct stack *front = (struct stack*)malloc(sizeof(struct stack));
  struct stack *temp;

  init(&front);

  //push some hard coded values onto the stack
  if(!push(&front, 3)){
    printf("push failed.\n");
  }
    if(!push(&front, 5)){;
    printf("push failed.\n");
  }
    if(!push(&front, 7)){;
    printf("push failed.\n");
  }

  temp = pop(&front);
  if(temp!=NULL){
    printf("pop stack = %d\n", temp->data);
  }

  if(empty(front)){
    printf("empty stack\n");
  } else {
    printf("contains elements\n");
  }

  num = top(front);
  if(num != -1){
    printf("top of stack = %d\n", temp->data);
  }

  //3 pops empties the stack
  temp = pop(&front);
  temp = pop(&front);
  temp = pop(&front);
  
  if(temp != NULL){
    printf("top of stack = %d\n", temp->data);
  } else {
    printf("tried to pop an empty stack\n");
  }


  return 0;
}

//initialize function sets head pointer of the list to NULL aka list is empty at this point
void init(struct stack **front){
  *front = NULL;
}
//checks if stack is empty or  not by checking head pointer
int empty(struct stack *front){
  if(front == NULL){
    return 1; //list is empty
  }
  else {
    return 0; //list is not empty
  }
}
//push new node onto the top of the stack
int push(struct stack **front, int num){
  //new node to save data
  struct stack *temp = (struct stack*)malloc(sizeof(struct stack));

  if(temp != NULL){
    temp->data = num; //save value passed in to new node
    temp->next = *front; //save address of current front node into next pointer of new node
    *front = temp;
    return 1; //push was successful
  }
  else {
    return 0; //push failed
  }
}

//pop a node off the top of the stack
struct stack* pop(struct stack **front){
  //helper node
  struct stack *temp = (struct stack*)malloc(sizeof(struct stack));
  temp = NULL;

  if(*front != NULL){ //needs to be atleast one node to pop
    temp = (*front); //temp points to front node, which we will pop
    *front = (*front)->next; //2nd node is now the first node
    temp->next = NULL;
  }
  return temp;
}

//return the data value of top node
int top(struct stack *front){

  if(front != NULL){
    return front->data; //return value of this node
  } else {
    return -1; //list is empty
  }
}
