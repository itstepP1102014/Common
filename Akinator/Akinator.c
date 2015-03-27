#include "Akinator.h"

void addNewFork(Node *oldAnimal, Node *newAnimal, Node *question, bool answer)
{
    if(answer)
    {
        question->yeslink = newAnimal;
        question->nolink = oldAnimal;
    }
    else
    {
        question->yeslink = oldAnimal;
        question->nolink = newAnimal;
    }
    oldAnimal->parent = question;
    newAnimal->parent = question;
}

void hangFork(Node **root, Node *parent, Node *fork, bool wayToChild)
{
    if(!parent)
        *root = fork;
    else
    {
        if(wayToChild)
            parent->yeslink = fork;
        else
            parent->nolink = fork;
        fork->parent = parent;
    }
}

bool determineWayToChild(Node *node)
{
    if(!node || !node->parent)
        return false;
    else
        return node->parent->yeslink == node;
}

bool addNewKnowledge(Node **root, Node *destination, char *question, char *newAnimal, bool rightAnswer)
{
    assert(destination);
    Node *questionNode = NULL, *newAnimalNode = NULL;
    if(!createNewNode(&questionNode, question, noanimal))
        return false;
    if(!createNewNode(&newAnimalNode, newAnimal, animal))
    {
        free(questionNode);
        questionNode = NULL;
        return false;
    }
    Node *parent = destination->parent;
    bool wayToChild = determineWayToChild(destination);
    addNewFork(destination, newAnimalNode, questionNode, rightAnswer);
    hangFork(root, parent, questionNode, wayToChild);
    return true;
}

bool createNewNode(Node **node, char *str, Type type)
{
    char *p = NULL;
    p = (char *)malloc((strlen(str) + 1) * sizeof(char));
    if(!p)
        return false;
    Node *q = NULL;
    q = (Node *)malloc(sizeof(Node));
    if(!q)
    {
        free(p);
        p = NULL;
        return false;
    }
    strcpy(p, str);
    q->data.str = p;
    q->data.sizestr = strlen(p) + 1;
    q->data.type = type;
    q->parent = NULL;
    q->yeslink = NULL;
    q->nolink = NULL;
    *node = q;
    p = NULL;
    q = NULL;
    return true;
}

Node *playGame(Node *root)
{
    Node *p = root;
    while(p->data.type == noanimal)
    {
        printf("%s\n", p->data.str);
        printf("Нажми y/n: ");
        char answer;
        scanf(" %c", &answer);
        if(answer == 'y')
            p = p->yeslink;
        else
            p = p->nolink;
    }
    return p;
}

// -----

bool pushToStack(Node *pointer, Stack *stack)
{
    NodeForStack *temp = NULL;
    temp = (NodeForStack *)malloc(sizeof(NodeForStack));
    if(!temp)
        return false;
    temp->node = pointer;
    temp->link = *stack;

    *stack = temp;
    temp = NULL;
    return true;
}

void popFromStack(Stack *stack)
{
    if(*stack)
    {
        NodeForStack *temp = *stack;
        *stack = (*stack)->link;
        temp->node = NULL;
        temp->link = NULL;
        free(temp);
        temp = NULL;
    }
}

bool isStackEmpty(Stack stack)
{
    return !stack;
}

bool onTopOfStack(Node **pointer, Stack stack)
{
    if(!isStackEmpty(stack))
    {
        *pointer = stack->node;
        return true;
    }
    return false;
}

void clearStack(Stack *stack)
{
    while(!isStackEmpty(*stack))
        popFromStack(stack);
}

// -----

bool addNode(Node **root, Node **node, int way, char *str, Type type)
{
    char *p = NULL;
    p = (char *)malloc((strlen(str) + 1) * sizeof(char));
    if(!p)
        return false;
    Node *q = NULL;
    q = (Node *)malloc(sizeof(Node));
    if(!q)
    {
        free(p);
        p = NULL;
        return false;
    }
    strcpy(p, str);
    q->data.str = p;
    q->data.sizestr = strlen(p) + 1;
    q->data.type = type;
    q->yeslink = NULL;
    q->nolink = NULL;
    q->parent = NULL;
    if(!*root)
        *root = q;
    else
    {
        if(way)
            (*node)->nolink = q;
        else
            (*node)->yeslink = q;
        q->parent = *node;
        *node = q;
    }
    p = NULL;
    q = NULL;
    return true;
}

bool readFromFile(FILE *filepointer, Node **root)
{
    Node *tempPointer = NULL;
    char *str;
    int way, temp, lengthOfStr;
    Type type;
    fscanf(filepointer, "%d ", &lengthOfStr);
    str = (char *)malloc(lengthOfStr * sizeof(char));
    if(!str)
        return false;
    fgets(str, lengthOfStr, filepointer);
    fscanf(filepointer, "%d\n", &temp);
    if(temp)
        type = noanimal;
    else
        type = animal;
    addNode(root, root, 0, str, type);
    free(str);
    str = NULL;

    tempPointer = *root;

    Stack pointers = NULL;

    while(!feof(filepointer))
    {
        fscanf(filepointer, "%d %d ", &way, &lengthOfStr);
        str = (char *)malloc(lengthOfStr * sizeof(char));
        if(!str)
        {
            clearStack(&pointers);
            return false;
        }
        fgets(str, lengthOfStr, filepointer);
        fscanf(filepointer, "%d\n", &temp);
        if(temp)
            type = noanimal;
        else
            type = animal;

        if(way)
            pushToStack(tempPointer, &pointers);
        else
        {
            onTopOfStack(&tempPointer, pointers);
            popFromStack(&pointers);
        }
        addNode(root, &tempPointer, way, str, type);
        free(str);
        str = NULL;
    }

    clearStack(&pointers);

    return true;
}

void writeToFile(FILE *filepointer, Node *root)
{
    Node *tempPointer = root;
    Stack pointers = NULL;
    pushToStack(tempPointer, &pointers);
    int way;
    while(!isStackEmpty(pointers))
    {
        onTopOfStack(&tempPointer, pointers);
        popFromStack(&pointers);
        if(tempPointer == root)
            fprintf(filepointer, "%d %s %d\n", tempPointer->data.sizestr, tempPointer->data.str, tempPointer->data.type);
        else
        {
            if(tempPointer->parent->yeslink == tempPointer)
                way = 0;
            else
                way = 1;
            fprintf(filepointer, "%d %d %s %d\n", way, tempPointer->data.sizestr, tempPointer->data.str, tempPointer->data.type);
        }

        if(tempPointer->yeslink && tempPointer->nolink)
        {
            pushToStack(tempPointer->yeslink, &pointers);
            pushToStack(tempPointer->nolink, &pointers);
        }
    }
}

void addNewInformation(Node **root, Node *destination)
{
    char question[200], animal[50], answer;
    bool reply;
    printf("Какое животное вы загадали? ");
    getchar();
    gets(animal);
    printf("Какой вопрос характеризует это животное? ");
    gets(question);
    printf("Какой правильный ответ на этот вопрос для этого животного? y/n ");
    scanf(" %c", &answer);
    if(answer == 'y')
        reply = true;
    else
        reply = false;
    printf("Спасибо за введенные данные! В следующий раз я точно выиграю!\n");
    addNewKnowledge(root, destination, question, animal, reply);
}

void clearTree(Node **root)
{
    if(*root)
    {
        Node *temp1 = (*root)->yeslink, *temp2 = (*root)->nolink;
        (*root)->data.sizestr = 0;
        (*root)->data.str = NULL;
        ++((*root)->data.type);
        (*root)->yeslink = NULL;
        (*root)->nolink = NULL;
        (*root)->parent = NULL;
        free((*root));
        *root = NULL;
        clearTree(&temp1);
        clearTree(&temp2);
    }
}
