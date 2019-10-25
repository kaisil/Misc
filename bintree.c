#include <stdio.h>
#include <stdlib.h>

struct tree_node {
  int data;
  struct tree_node *left_child;
  struct tree_node *right_child;
};

void preorder(struct tree_node *p);
void inorder(struct tree_node *p);
void postorder(struct tree_node *p);

int find(struct tree_node *current_ptr, int val);
int add(struct tree_node *current_ptr);

struct tree_node* create_node(int val);
struct tree_node* insert(struct tree_node *root, struct tree_node *element);
struct tree_node* findNode(struct tree_node *current_ptr, int val);
struct tree_node* parent(struct tree_node *root, struct tree_node *node);
struct tree_node* minVal(struct tree_node *root);
struct tree_node* maxVal(struct tree_node *root);
int isLeaf(struct tree_node *node);
int hasOnlyLeftChild(struct tree_node *node);
int hasOnlyRightChild(struct tree_node *node);
struct tree_node* delete(struct tree_node *current_ptr, int val);

void printBig(struct tree_node *current_ptr, int val);

int menu();

int main()
{

  struct tree_node *my_root = NULL; //root of the bintree
  struct tree_node *temp_node;

  int done = 0;
  int ans = 1;
  int val;

  ans = menu();
  while (ans < 6){
    if(ans == 1){
      //get value to insert
      printf("what value would you like to insert? \n");
      scanf("%d", &val);
      temp_node = create_node(val); //create the node

      my_root = insert(my_root, temp_node);
    }

    if(ans == 2){
      printf("what value would you like to delete? \n");
      scanf("%d", &val);
      if(!find(my_root, val)){
        printf("sorry that value isn't in the tree.\n");
      } else {
        my_root = delete(my_root, val);
      }
    }

    if(ans == 3){
      printf("what value would you like to search for?\n");
      scanf("%d", &val);
      if(find(my_root, val)){
        printf("found %d in the tree.\n", val);
      } else {
        printf("didn't find the value.\n");
      }
    }

    if(ans == 4){
      printf("the sum of the nodes in your tree is %d.\n", add(my_root));
    }

    if(ans == 5){
      printf("here is an inorder traversal of your tree.\n");
      inorder(my_root);
      printf("\n");
    }
    ans = menu();
  }
  return 0;
}

//preorder traversal: A - >B -> C
//root is visited before left and right subtrees
void preorder(struct tree_node *p){
  if(p != NULL){
    printf("%d\n", p->data);
    preorder(p->left_child);
    preorder(p->right_child);
  }
}

//inorder traversal: B -> A -> C
//root is visited between the subtrees
void inorder(struct tree_node *p){
  if(p != NULL){
    inorder(p->left_child);
    printf("%d\n", p->data);
    inorder(p->right_child);
  }
}

//postorder traversal: B -> C -> A
//root is visted after both subtrees
void postorder(struct tree_node *p){
  if(p != NULL){
    postorder(p->left_child);
    postorder(p->right_child);
    printf("%d\n", p->data);
  }
}

//creating a node
struct tree_node* create_node(int val){
  //make space
  struct tree_node* temp;
  temp = (struct tree_node*)malloc(sizeof(struct tree_node));

  //initialize the fields
  temp->data = val;
  temp->left_child = NULL;
  temp->right_child = NULL;

  //return a pointer to the created node
  return temp;
}

//insert a node
struct tree_node* insert(struct tree_node *root, struct tree_node *element){
  //inserting into empty tree
  if(root == NULL){
    return element;
  } else {
    //element should be inserted to the right
    if(element->data > root->data){
      root->right_child = insert(root->right_child, element);
    } else {
      root->left_child = insert(root->left_child, element);
    }
    return root;
  }
}

//searching for a node
int find(struct tree_node *current_ptr, int val){
  //null check
  if(current_ptr != NULL){
    //check the root
    if(current_ptr->data == val){
      return 1;
    }
    //check the left
    if(val < current_ptr->data){
      return find(current_ptr->left_child, val);
    }
    else {
      return find(current_ptr->right_child, val);
    }
  } else {
    return 0;
  }
}

struct tree_node* findNode(struct tree_node *current_ptr, int val){
  if(current_ptr != NULL){
    if(current_ptr->data == val){
      return current_ptr;
    }
    if(val < current_ptr->data){
      return findNode(current_ptr->left_child, val);
    } else {
      return findNode(current_ptr->right_child, val);
    }
  } else {
    return NULL; //didn't find the node
  }
}

struct tree_node* parent(struct tree_node *root, struct tree_node *node){
  //null case
  if(root == NULL || root == node){
    return NULL;
  }

  //root is the direct parent of the node
  if(root->left_child == node || root->right_child == node){
    return root;
  }

  if(node->data < root->data){ //search left
    return parent(root->left_child,  node);
  }
  else if(node->data > root->data){ //search right
    return parent(root->right_child, node);
  }
  return NULL;
}

struct tree_node* minVal(struct tree_node *root){
  if(root->left_child == NULL){ //root contains the min val
    return root;
  } else {
    return minVal(root->left_child);
  }
}

struct tree_node* maxVal(struct tree_node *root){
  if(root->right_child == NULL){
    return root;
  } else {
    return maxVal(root->right_child);
  }
}

//node is a leaf if both children are NULL
int isLeaf(struct tree_node *root){
  return(root->left_child == NULL && root->right_child == NULL);
}

//node only has a left child
int hasOnlyLeftChild(struct tree_node *node){
  return(node->left_child != NULL && node->right_child == NULL);
}

//node only has a right child
int hasOnlyRightChild(struct tree_node *node){
  return(node->left_child == NULL && node->right_child != NULL);
}

//will delete the node storing value in the tree rooted at root
//wont work if value is not present
//returns a pointer to the root of the resulting tree
struct tree_node* delete(struct tree_node *current_ptr, int val){
  struct tree_node *delNode, *new_delNode, *saveNode;
  struct tree_node *par;
  int save_val;

  delNode = findNode(current_ptr, val); //get a pointer to the node to delete

  par = parent(current_ptr, delNode); //get the parent of this node

  if(isLeaf(delNode)){ //if node to delete is a leaf

    if(par == NULL){ //deleting the only node in the tree
     free(current_ptr);
     return NULL;
    }

    if(val < par->data){ //delete left child
      free(par->left_child);
      par->left_child = NULL;
    } else {
      free(par->right_child); //delete right  child
      par->right_child = NULL;
    }
    return current_ptr; //return root of new tree
 }

 //if node to be deleted only has a left child
 if(hasOnlyLeftChild(delNode)){
   if(par == NULL){
     saveNode = delNode->left_child;
     free(delNode);
     return saveNode;
   }

   if(val < par->data){
     saveNode = par->left_child;
     par->left_child = par->left_child->left_child;
     free(saveNode);
   } else {
     saveNode = par->right_child;
     par->right_child = par->right_child->left_child;
     free(saveNode);
   }
   return current_ptr;
 }

 //if node to be deleted only has a right child
 if(hasOnlyRightChild(delNode)){
   if(par == NULL){
     saveNode = delNode->right_child;
     free(delNode);
     return saveNode;
   }

   if(val < par->data){
     saveNode = par->left_child;
     par->left_child = par->left_child->right_child;
     free(saveNode);
   } else {
     saveNode = par->right_child;
     par->right_child = par->right_child->right_child;
     free(saveNode);
   }
   return current_ptr;
 }

//find the new physical node to delete
 new_delNode = minVal(delNode->right_child);
 save_val = new_delNode->data;

 delete(current_ptr, save_val);  //delete the proper value

 delNode->data = save_val; //restore the data to the original node to be deleted

 return current_ptr;
}

int add(struct tree_node *current_ptr){
  if(current_ptr != NULL){
    return current_ptr->data + add(current_ptr->left_child) + add(current_ptr->right_child);
  } else {
    return 0;
  }
}

void printBig(struct tree_node *current_ptr, int val){
  if(current_ptr != NULL){
    if(current_ptr->data >= val){
      printf("%d\n", current_ptr->data);
    } else {
     printBig(current_ptr->left_child, val);
    }
    printBig(current_ptr->right_child, val);
  }
}

int menu() {

  int ans;
  printf("Here are your choices.\n");
  printf("1. Insert an item into your tree.\n");
  printf("2. Delete an item from your tree.\n");
  printf("3. Search for an item in your tree.\n");
  printf("4. Print the sum of the nodes in your tree.\n");
  printf("5. Print out an inorder traversal of your tree.\n");
  printf("6. Quit.\n");
  scanf("%d", &ans);
  return ans;
}
