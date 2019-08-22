#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define nullCheck( ptr ); if( ptr == NULL ) { printf("\n\nFailed allocating memory! Check line %d! Terminating Program!\n", __LINE__); exit(EXIT_FAILURE); }

struct node{
    int data;
    struct node* next;
};

void markEven (struct node *head); //mark nodes with an even value by inserting a node containing -1 after them
void printList(struct node *head);

struct node* buildList(struct node *head);
struct node* destroyList(struct node *head);

int menu();

int main()
{
	srand((int)time(0)); //used to generate the random values we'll populate our list with 
	
	struct node* head = NULL;	//head is the front of our currently empty list
	
	int userInput = 0;
	userInput = menu();
	
	while(userInput != -1){
		
		if(userInput == 1){
			
			head = buildList(head);
			printf("Successfully built the linked list.\n");
			
		} else if (userInput == 2){
			
			printList(head);
			
		} else if (userInput == 3){
			
			markEven(head);
			
		} else if (userInput == 4){
			
			destroyList(head);
			
		} else {
			
			printf("Invalid selection.\n");
		}

		userInput = menu();
	}
	
    return 0;
}

struct node* buildList(struct node *head){
	
	int ans = 0;
	printf("How many values would you like the linked list to contain?\n");
	scanf(" %d", &ans);
	
	if(ans == 0){ return 0;}
	
	if(head == NULL){
		head = (struct node*)malloc(sizeof(struct node));
		nullCheck(head);	
		
		head->data = rand() % 101; //assign value to head
		head->next = NULL; 
	}
	
	struct node* temp = head; 	//helper node to walk the list 
	nullCheck(temp);
	
	for(int i = 0; i < ans - 1 ; i++){ 
		
		int val = rand() % 101;
		
		struct node* newnode = NULL; 	//new node to be added to the list 
		newnode = (struct node*)malloc(sizeof(struct node));
		nullCheck(newnode);
		
		newnode->data = val;
		newnode->next = NULL;

		temp->next = newnode;
		temp = temp->next;

	}	
	
	return head;
	
}

void markEven (struct node *head){

    struct node* temp = head; //helper node to walk the list 

        while(temp != NULL){

            if(temp != NULL && temp->data % 2 == 0){
				
                struct node* newnode = NULL;
                newnode = (struct node*)malloc(sizeof(struct node));
				nullCheck(newnode);
				
                newnode->data = -1;
                newnode->next = temp->next;
				
                temp->next = newnode;
                temp = newnode->next;

            }
			else {
				temp = temp->next;
			}
        }

}

void printList(struct node *head){

  if(head == NULL){
    printf("List is empty!!\n");

  } else {
	  struct node* temp; //helper node to walk the list 
	  temp = (struct node*)malloc(sizeof(struct node));

	  temp = head;

	  while(temp != NULL){
		printf(" %d\n", temp->data); 
		temp = temp->next; //advance the pointer to the next member's value
	  }	
	  
	  free(temp);
  }
}

struct node* destroyList(struct node *head){

  if(head == NULL){ return 0;} //list is empty
  
  if(head->next == NULL){free(head);} //list only has 1 member
  
  struct node *current = head;
  struct node *temp;
   
  while (current != NULL){
	  temp = current->next;
	  free(current);
	  current = temp;
  }

}

int menu() {
	
	int userInput;
	
	printf("\nWelcome to the menu! Select an operation.\n\n"
			"\tEnter 1 build the linked list.\n"
			"\tEnter 2 to print the list.\n"
			"\tEnter 3 to insert -1 after nodes with containing an even value\n"
			"\tEnter 4 to destroy the list.\n"
			"\tEnter -1 to quit.\n");
	
	scanf(" %d", &userInput);

	return userInput;
}
