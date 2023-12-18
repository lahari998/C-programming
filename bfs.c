#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX_ROWS 50
#define MAX_COLS 50
struct node {
    int vertex;
    struct node* next;
} ;

struct graph {
    int numVertices;
    struct node** list;
};

struct queue {
    int* array;
    int front, rear, size;
    unsigned capacity;
};

struct queue* createQueue(unsigned capacity) {
    struct queue* Queue = (struct queue*)malloc(sizeof(struct queue));
    Queue->capacity = capacity;
    Queue->front = Queue->size = 0;
    Queue->rear = capacity - 1;  
    Queue->array = (int*)malloc(Queue->capacity * sizeof(int));
    return Queue;
}

int isFull(struct queue* Queue) {
    return (Queue->size == Queue->capacity);
}

int isEmpty(struct queue* Queue) {
    return (Queue->size == 0);
}

void enqueue(struct queue* Queue, int item) {
    if (isFull(Queue)) {
      printf("Queue is full");
    }
    Queue->rear = (Queue->rear + 1) % Queue->capacity;
    Queue->array[Queue->rear] = item;
    Queue->size = Queue->size + 1;
}

int dequeue(struct queue* Queue) {
    if (isEmpty(Queue)) {
       printf("queue is empty");
    }
    int item = Queue->array[Queue->front];
    Queue->front = (Queue->front + 1) % Queue->capacity;
    Queue->size = Queue->size - 1;
    return item;
}

struct graph* createGraph(int numVertices) {
    struct graph* Graph = (struct graph*)malloc(sizeof(struct graph));
    Graph->numVertices = numVertices;

    Graph->list = (struct node**)malloc(numVertices * sizeof(struct node*));
    for (int i = 0; i < numVertices; ++i) {
        Graph->list[i] = NULL;
    }
return Graph;
}

void addEdge(struct graph* graph, int x, int y) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->vertex = y;
    newNode->next = graph->list[x];
    graph->list[x] = newNode;
    
}
void printMazeWithPath(char maze[MAX_ROWS][MAX_COLS], int rows, int cols, int* parent, int start, int end) {
    char mazeCopy[MAX_ROWS][MAX_COLS];
    memcpy(mazeCopy, maze, sizeof(char) * MAX_ROWS * MAX_COLS);

    int x = end;
    while (x != start) {
        int row = x / cols;
        int col = x % cols;
        mazeCopy[row][col] = '.';
        x = parent[x];
    }

    mazeCopy[start / cols][start % cols] = 'S';
    mazeCopy[end / cols][end % cols] = 'E';

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            printf("%c", mazeCopy[i][j]);
        }
        printf("\n");}
}


void BFS(struct graph* Graph, int start, int end, char maze[MAX_ROWS][MAX_COLS], int rows, int cols) {
    int* visited = (int*)malloc(Graph->numVertices * sizeof(int));
    int* parent = (int*)malloc(Graph->numVertices * sizeof(int));

    struct queue* queue = createQueue(Graph->numVertices);

    for (int i = 0; i < Graph->numVertices; ++i) {
        visited[i] = 0;
        parent[i] = -1;  
    }

    enqueue(queue, start);
    visited[start] = 1;

    while (!isEmpty(queue)) {
        int currentVertex = dequeue(queue);

        if (currentVertex == end) {
            break;
        }

        struct node* current = Graph->list[currentVertex];
        while (current != NULL) {
            int neighbor = current->vertex;
            if (!visited[neighbor]) {
                enqueue(queue, neighbor);
                visited[neighbor] = 1;
                parent[neighbor] = currentVertex;  
            }
            current = current->next;}}
   printMazeWithPath(maze, rows, cols, parent, start, end);
}
int main() {
    char maze[MAX_ROWS][MAX_COLS];
    int rows, cols;

    FILE *fptr = fopen("/home/lahari/maze1.txt", "r");

    if (fptr == NULL) {
        perror("Error opening file");
    }

    rows = 0;
    cols = 0;
    while (fgets(maze[rows], sizeof(maze[0]), fptr) != NULL) {
        maze[rows][strcspn(maze[rows], "\n")] = '\0';
        if (rows == 0) {
            cols = strlen(maze[0]);
        }
        rows++;
    }

    fclose(fptr);
    int numVertices = rows * cols;
    struct graph* graph = createGraph(numVertices);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (maze[i][j] != '#' ) {
                if (i > 0 && maze[i-1][j] != '#') {
                    addEdge(graph, i * cols + j, (i - 1) * cols + j);
                }
                if (i < rows - 1 && maze[i+1][j] != '#') {
                    addEdge(graph, i * cols + j, (i + 1) * cols + j);
                }
                if (j > 0 && maze[i][j-1] != '#') {
                    addEdge(graph, i * cols + j, i * cols + (j - 1));
                }
                if (j < cols - 1 && maze[i][j+1] != '#') {
                    addEdge(graph, i * cols + j, i * cols + (j + 1));
}}}}

    int startVertex = -1;
    int endVertex = -1;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (maze[i][j] == 'S') {
                startVertex = i * cols + j;
            } else if (maze[i][j] == 'E') {
                endVertex = i * cols + j;}}}
    BFS(graph, startVertex, endVertex, maze, rows, cols);
        return 0;
}

