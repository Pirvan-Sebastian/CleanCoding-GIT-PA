/*Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf*/

#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int data;
    struct Node *next;
}
/// pentru simplitate, folosim int uri pt a numi restaurantel/locatiile
/// ex: 1 - restaurantul 1 si tot asa

Node;

typedef struct Graph
{
    int vertexCount;
    int *visited;
    struct Node **adjacencyList;
} Graph;

typedef struct Stack
{
    int top;
    int capacity;
    int *array;
} Stack;

Node *createNode(int vertex)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = vertex;
    newNode->next = NULL;
    return newNode;
}

void addEdge(Graph *graph, int source, int destination)
{
    Node *newNode = createNode(destination);
    newNode->next = graph->adjacencyList[source];
    graph->adjacencyList[source] = newNode;
    newNode = createNode(source);
    newNode->next = graph->adjacencyList[destination];
    graph->adjacencyList[destination] = newNode;
}

Graph *createGraph(int vertexCount)
{
    int i;
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->vertexCount = vertexCount;
    graph->adjacencyList = (Node **)malloc(sizeof(Node *));
    graph->visited = (int *)malloc(sizeof(int) * vertexCount);

    for (int i = 0; i < vertexCount; i++)
    {
        graph->adjacencyList[i] = NULL;
        graph->visited[i] = 0;
    } 
    return graph;
}

Stack *createStack(int capacity)
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->array = (int*)malloc(capacity * sizeof(int));
    stack->top = -1;
    stack->capacity = capacity;

    return stack;
}

void push(int pushedElement, Stack *stack)
{
    stack->top = stack->top + 1;
    stack->array[stack->top] = pushedElement;
}

void DFS(Graph *graph, Stack *stack, int vertexNumber)
{
    Node *adjacencyList = graph->adjacencyList[vertexNumber];
    Node *temp = adjacencyList;
    graph->visited[vertexNumber] = 1;
    printf("%d ", vertexNumber);
    push(vertexNumber, stack);
    while (temp != NULL)
    {
        int connectedVertex = temp->data;
        if (graph->visited[connectedVertex] == 0)
            DFS(graph, stack, connectedVertex);
        temp = temp->next;
    }
}

void insertEdges(Graph *graph, int edgeCount, int vertexCount)
{
    int source, destination, i;
    printf("adauga %d munchii (de la 1 la %d). In formatul a->b\n", edgeCount, vertexCount);
    for (i = 0; i < edgeCount; i++)
    {
        scanf("%d%d", &source, &destination);
        addEdge(graph, source, destination);
    }
}

void resetVisited(Graph *graph, int vertexCount)
{
    for (int i = 0; i < vertexCount; i++)
    {
        graph->visited[i] = 0;
    }
} 


// rezultat de tip boolean- 0=false 1=true   
void checkReachability(Graph *graph, int vertexCount, Stack *stack1, Stack *stack2) 
{
    //int *isReachable = (int *)calloc(5, sizeof(int));
    int isReachable = 0;
    //i reprezinta numarul restaurantului cum am stabilit mai sus
    for (int i = 0; i < vertexCount; i++) 
     for (int j = 0; j < 5; j++)
    {
        DFS(graph, stack1, i);
        resetVisited(graph, vertexCount);
        DFS(graph, stack2, j);
        int foundPath;
        for (int j = 0; j < vertexCount && !foundPath; j++)
            for (int i = 0; i < vertexCount && !foundPath; i++)
                if ((stack1->array[i] == j) && (stack2->array[j] == i))
                    isReachable = 1;
    }
}

int main()
{

    int vertexCount;
    int edgeCount;
    int source, destination;
    int i;
    int vortex_1;
    int virtex_2;
    int foundPath;

    printf("Cate Noduri are Graful?");
    scanf("%d", &vertexCount);

    printf("Cate Muchii are Graful?");
    scanf("%d", &edgeCount);

    Graph *graph = createGraph(vertexCount);

        Stack *stack1 = createStack(2 * vertexCount);
        
        insertEdges(graph, edgeCount, vertexCount);
        Stack *stack2 = createStack(edgeCount);
      return 0;   
}