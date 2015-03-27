#ifndef AKINATOR_H_INCLUDED
#define AKINATOR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

typedef enum Type_ {animal, noanimal} Type;

typedef struct Data_
{
    Type type;
    char *str;
    int sizestr;
} Data;

typedef struct Node_
{
    Data data;
    struct Node_ *parent, *yeslink, *nolink;
} Node;

typedef struct NodeForStack_
{
    Node *node;
    struct NodeForStack_ *link;
} NodeForStack;

typedef NodeForStack * Stack;

typedef NodeForStack NodeForQueue;

typedef struct Queue_
{
    NodeForQueue *head, *tail;
} Queue;

void addNewFork(Node *oldAnimal, Node *newAnimal, Node *question, bool answer);
void hangFork(Node **root, Node *parent, Node *fork, bool wayToChild);
bool determineWayToChild(Node *node);
bool addNewKnowledge(Node **root, Node *destination, char *question, char *newAnimal, bool rightAnswer);
bool createNewNode(Node **node, char *str, Type type);

Node *playGame(Node *root);

bool pushToStack(Node *pointer, Stack *stack);
void popFromStack(Stack *stack);
bool isStackEmpty(Stack stack);
bool onTopOfStack(Node **pointer, Stack stack);
void clearStack(Stack *stack);

void initializeQueue(Queue *queue);
bool pushToQueue(Node *pointer, Queue *queue);
void popFromQueue(Queue *queue);
bool isQueueEmpty(Queue queue);
bool onTopOfQueue(Node **pointer, Queue queue);
void clearQueue(Queue *queue);

bool addNode(Node **root, Node **node, int way, char *str, Type type);
bool readFromFile(FILE *filepointer, Node **root);
void writeToFile(FILE *filepointer, Node *root);
void addNewInformation(Node **root, Node *destination);
void cleanTree(Node **root);

#endif // AKINATOR_H_INCLUDED
