#include<stdio.h>
#include<stdlib.h>

#define SIZE1 1010

struct Hashtable{
int table[SIZE1];
};

int hashfunctn1(int key){
  return 2*key+1;
}

int hashfunctn2(int key){
  return 5*key+2;
}

struct Hashtable* createHashTable(int size) {
    struct Hashtable* hashTable = (struct Hashtable*)malloc(sizeof(struct Hashtable));
    for (int i = 0; i < size; i++){
    
        hashTable->table[i] = 0;
        }
            return hashTable;
}

void insert(struct Hashtable* Table,int S,int size){
int index1=hashfunctn1(S);
int index2=hashfunctn2(S);
createHashTable(size);
for(int i=0;i<size;i++){
int index = (index1 + index2*i)%size;
if(Table->table[index]==0){
Table->table[index]=S;
return;}}
printf("%d not inserted \n", S);
}

int search(struct Hashtable* Table,int S,int size){
int index1=hashfunctn1(S);
int index2=hashfunctn2(S);
int probe=0;
for(int i=0;i<size;i++){
int index = (index1 + index2*i)%size;
if(Table->table[index]!=S){probe++;}
else if(Table->table[index]==S){
printf("key is thr\n");
printf("no of probes are %d\n", probe+1);
return 1;
}
}
printf("key is not thr\n");
printf("no of probes are %d\n", probe);
return 0;}

struct Hashtable* delete(struct Hashtable* Table,int key,int size){
if(search(Table,key,size)){
for(int i=0;i<size;i++){
if(Table->table[i]==key){
Table->table[i]=0;
break;
}}
}
}


int main(){

FILE* fptr = fopen("input.txt", "r");
    if (fptr == NULL) {
        perror("file not found");
    }
    int size=SIZE1;
      
int keys[SIZE1];
struct Hashtable hashTable;
    for (int i = 0; i < SIZE1; i++) {
        hashTable.table[i] = 0;
    }
        for (int i = 0; i < SIZE1; i++) {
            if (fscanf(fptr, "%d", &keys[i]) == EOF) {
                break;
            }
            insert(&hashTable,keys[i],SIZE1);
            }
            FILE* fptr1 = fopen("unsuccessfulsearchs.txt", "r");
    if (fptr1 == NULL) {
        perror("file not found");
    }
            int unsuccessful_searches[100];
            for (int i = 0; i < 100; i++) {
            if (fscanf(fptr1, "%d", &unsuccessful_searches[i]) == EOF) {
                break;
            }
            }
            printf("part d\n");
    for (int i = 0; i < 100; i++) {
        search(&hashTable,unsuccessful_searches[i],size);
    }
        
            int selected_keys[200];
            int selected_count=0;
         while (selected_count < 200) {
        int index = rand() % 1000;  
        if (keys[index] != -1) {
            selected_keys[selected_count] = keys[index];
            keys[index] = -1;  
            selected_count++;
        }
    }
        for (int i = 0; i < 100; i++) {
        printf("%d ", selected_keys[i]);
    }
    printf("\n");
    printf("part a\n");
    for (int i = 0; i < 100; i++) {
        search(&hashTable,selected_keys[i],size);
    }
    printf("\n");
    for (int i = 0; i < 100; i++) {
        delete(&hashTable,selected_keys[i],size);
    }
    printf("part c\n");
    for (int i = 100; i < 200; i++) {
        search(&hashTable,selected_keys[i],size);
    }
    
    fclose(fptr);
    fclose(fptr1);
    return 0;
}



