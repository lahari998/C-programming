#include<stdlib.h>
#include<stdio.h>
void main()
{
struct node{
 int data;
 struct node*next;
};
struct node*head,*newnode,*temp;
int a,count;
head = 0;
while(a){
newnode=(struct node*)malloc(sizeof(struct node));
printf("Enter data of the node:");
scanf("%d", &newnode->data);
newnode->next=0;

if(head == 0){
head=temp=newnode;
}
else{
temp->next=newnode;
temp=newnode;
}

printf("enter 1 to continue the list else 0: ");
scanf("%d", &a);

}

temp = head;
while(temp != 0){
printf("%d \n", temp->data);
temp=temp->next;
count++;
}
printf("No of nodes is %d",count);

}
