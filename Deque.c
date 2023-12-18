#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

struct deque {
    int A[MAX_SIZE];
    int n;  //n is the maximum size of deque
    int front;
    int rear;  //indexes of front and rear elements
    int no_of_elements;  //no of elements present in deque
};

struct deque Create_Deque(int i);  //constructor function of deque and i is index
void isEmpty(struct deque a);
void isFull(struct deque a);
void get_front(struct deque a);
void get_rear(struct deque a);
void add_first(struct deque *a, int x);
void remove_first(struct deque *a);
void add_last(struct deque *a, int x);
void remove_last(struct deque *a);
void display(struct deque a);

int main() {
    struct deque Deque = Create_Deque(10);
        printf("1.isEmpty \n");
        printf("2.isFull \n");
        printf("3.get front \n");
        printf("4.get rear \n");
        printf("5.add first \n");
        printf("6.delete first \n");
        printf("7.add last \n");
        printf("8.delete last \n");
        printf("0.exit\n");
    int ch, value; //choice
    do {
        printf("enter the operation need to be performed : \n");
        
        scanf("%d", &ch);
        switch (ch) {
            case 1:
                isEmpty(Deque);
                break;
            case 2:
                isFull(Deque);
                break;
            case 3:
                get_front(Deque);
                break;
            case 4:
                get_rear(Deque);
                break;
            case 5:
                printf("enter the value to be added: ");
                scanf("%d", &value);
                add_first(&Deque, value);
                break;
            case 6:
                remove_first(&Deque);
                break;
            case 7:
                printf("enter the value to be added: ");
                scanf("%d", &value);
                add_last(&Deque, value);
                break;
            case 8:
                remove_last(&Deque);
                break;
            case 0:
                break;
            default:
                printf("Invalid choice, choose again\n");
                break;
        }
    }
    while(ch != 0);

    display(Deque);
    return 0;
}

struct deque Create_Deque(int i) {
    struct deque a;
    if (i > MAX_SIZE) {
        i = MAX_SIZE;
    }
    a.n = i;
    a.front = 0;
    a.rear = 0;
    a.no_of_elements = 0;
    return a;
}

void isEmpty(struct deque a) {
    if (a.front == 0 && a.rear == 0) {
        printf("Deque is empty\n");
    }
}

void isFull(struct deque a) {
    if ((a.front == 1 && a.rear == a.n) || (a.front == a.rear + 1)) {
        printf("Deque is full\n");
    }else{printf("not full");}
}

void get_front(struct deque a) {
    if (a.front == 0 && a.rear == 0) {
        printf("Deque is empty\n");
    } else {
        printf("First element is %d\n", a.A[a.front]);
    }
}

void get_rear(struct deque a) {
    if (a.front == 0 && a.rear == 0) {
        printf("Deque is empty\n");
    } else {
        printf("Last element is %d\n", a.A[a.rear]);
    }
}

void add_first(struct deque *a, int x) {
    if ((a->front == 0 && a->rear == a->n) || (a->front == a->rear + 1)) {
        printf("Deque is full\n");
    } else if (a->front == 0 && a->rear == 0) {
        a->front = a->rear = 1;
        a->A[a->front] = x;
    } else if (a->front == 1) {
        a->front = a->n;
        a->A[a->front] = x;
    } else {
        a->front--;
        a->A[a->front] = x;
    }
}

void remove_first(struct deque *a) {
    if (a->front == 0 && a->rear == 0) {
        printf("Deque is empty\n");
    } else if (a->front == a->rear) {
        a->front = a->rear = 0;
    } else if (a->front == a->n) {
        a->front = 1;
    } else {
        a->front++;
    }
}

void add_last(struct deque *a, int x) {
    if ((a->front == 0 && a->rear == a->n) || (a->front == a->rear + 1)) {
        printf("Deque is full\n");
    } else if (a->front == 0 && a->rear == 0) {
        a->front = a->rear = 1;
        a->A[a->rear] = x;
    } else if (a->rear == a->n) {
        a->rear = 1;
        a->A[a->rear] = x;
    } else {
        a->rear++;
        a->A[a->rear] = x;
    }
}

void remove_last(struct deque *a) {
    if (a->front == 0 && a->rear == 0) {
        printf("Deque is empty\n");
    } else if (a->front == a->rear) {
        a->front = a->rear = 0;
    } else if (a->rear == 0) {
        a->rear = a->n;
    } else {
        a->rear--;
    }
}

void display(struct deque a) {int i= a.front;
    if (a.front == 0 && a.rear == 0) {
        printf("Deque is empty\n");
        return;
    }
    else{
   while(i!=a.rear){
  if(i!=0){ printf("%d ",a.A[i]);}
   i=(i+1)%(a.n+1);
   }
   printf("%d ",a.A[a.rear]);
 }  
}
