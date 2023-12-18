#include<stdio.h>
#include<stdlib.h>

#define SIZE 1000

struct node{
  int key;
  struct node* left;
  struct node* right;
  int height;
  };
  
struct Hashtable{
  struct node* table[SIZE];
  };
int hashfunctn(int key, int size){
  return key%size;
}
int max(int a, int b) {
  if(a>b){
     return a;}
  else {
    return b;}
}
int height_of_AVL(struct node* n) {
 if(n == NULL){
    return -1;
 }
  return n->height;
}
int getBalance(struct node* n) {
 if(n == NULL){
    return 0;
    }
    return height_of_AVL(n->left) - height_of_AVL(n->right);
}
struct node* create(int a) {
 struct node* newnode = (struct node*)malloc(sizeof(struct node));
 newnode->key = a;
 newnode->left = NULL;
 newnode->right = NULL;
 newnode->height = 0;
    return newnode;
}
struct node* rightRotate(struct node* y) {
  struct node* x = y->left;
  struct node* z = x->right;

  x->right = y;
  y->left = z;

  y->height = max(height_of_AVL(y->left), height_of_AVL(y->right)) + 1;
  x->height = max(height_of_AVL(x->left), height_of_AVL(x->right)) + 1;

  return x;
}

struct node* rotateLeft(struct node* x) {
    struct node* y = x->right;
    struct node* z = y->left;
    y->left = x;
    x->right = z;
    x->height = max(height_of_AVL(x->left), height_of_AVL(x->right)) + 1;
    y->height = max(height_of_AVL(y->left), height_of_AVL(y->right)) + 1;
   return y;
}
struct node* insert(struct node* root, int a) {
    if (root == NULL) {
        return create(a);
    }
 if (a < root->key) {
        root->left = insert(root->left, a);
    } else if (a > root->key) {
        root->right = insert(root->right, a);
    }

    root->height = 1 + max(height_of_AVL(root->left), height_of_AVL(root->right));

    int balance = getBalance(root);

if(balance > 1) {
if(a < root->left->key){
   return rightRotate(root);}
if(a > root->left->key){
   root->left = rotateLeft(root->left);
   return rightRotate(root);}
}
if(balance < -1) {
if(a > root->right->key){
   return rotateLeft(root);}
if(a < root->right->key){
   root->right = rightRotate(root->right);
   return rotateLeft(root);}
}
 return root;
}

struct node* create_AVL(int keys[], int num_of_keys) {
    struct node* root = NULL;
    for (int i = 0; i < num_of_keys; i++) {
        root = insert(root, keys[i]);
    }
    return root;
}

struct node* minValueNode(struct node* node) {
    struct node* current = node;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

struct node* deleteNode(struct node* root, int key) {
    if (root == NULL) {
    return root;
    }
     if (key < root->key) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    } else {
        if (root->left == NULL) {
            struct node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct node* temp = root->left;
            free(root);
            return temp;
        }

        struct node* temp = minValueNode(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }
    root->height = 1 + max(height_of_AVL(root->left), height_of_AVL(root->right));

    int balance = getBalance(root);

if(balance > 1) {
if(key < root->left->key){
   return rightRotate(root);}
if(key > root->left->key){
   root->left = rotateLeft(root->left);
   return rightRotate(root);}
}
if(balance < -1) {
if(key > root->right->key){
   return rotateLeft(root);}
if(key < root->right->key){
   root->right = rightRotate(root->right);
   return rotateLeft(root);}
}
   return root;
}
struct node *search(struct node *root, int key) {
    if (root == NULL || root->key == key) {
        return root;
    }
 if (key < root->key) {
return search(root->left, key);}
 else {
return search(root->right, key);}
}

void insert_HashTable(struct node** hashTable, int key, int size) {
    int index = hashfunctn(key, size);
    hashTable[index] = insert(hashTable[index], key);
}
struct node* search_hash(struct node** hashTable, int key, int size) {
    int index = hashfunctn(key, size);
    struct node* data = NULL;
    if (hashTable[index] != NULL) {
        data = search(hashTable[index], key);
    }
    return data;
}
void deleteFromHashTable(struct node** hashTable, int key, int size) {
    int index = hashfunctn(key, size);
    if (hashTable[index] != NULL) {
        hashTable[index] = deleteNode(hashTable[index], key);
    }
}
int main() {
    FILE* fptr = fopen("input.txt", "r");
    if (fptr == NULL) {
        perror("file not found");
    }
    int size=1000;
    struct node** hashTable = (struct node**) malloc(size * sizeof(struct node*));
for (int i = 0; i < SIZE; i++) {
        hashTable[i] = NULL;
    }
   
int keys[1000];
        for (int i = 0; i < SIZE; i++) {
            if (fscanf(fptr, "%d", &keys[i]) == EOF) {
                break;
            }
            insert_HashTable(hashTable,keys[i],size);
        }
        int searchKey;
        printf("enter the aadhar you want to search:\n ");
        scanf("%d",&searchKey);
        struct node* search = search_hash(hashTable, searchKey, size);
if (search!= NULL) {
        printf("%d is in hash table\n", searchKey);
    } else {
        printf("%d not in hash table\n", searchKey);
    }        
int deleteKey;
printf("enter the aadhar you want to delete:\n ");
        scanf("%d",&deleteKey);
struct node* delete = search_hash(hashTable, deleteKey, size);  
if(delete==NULL){printf("key is not in hashtable\n");}
else{printf("key is deleted\n");}
    deleteFromHashTable(hashTable, deleteKey, size);
    fclose(fptr);
    return 0;
}




