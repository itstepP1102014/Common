#include "Akinator.h"

int main()
{
    /*Node *root = NULL;
    createNewNode(&root, "кот", animal);
    addNewKnowledge(&root, root, "Оно живёт в воде?", "кит", true);
    Node *p = playGame(root);
    printf("Это %s. Я угадала?\n", p->data.str);
    char answer;
    scanf(" %c", &answer);
    if(answer == 'y')
        printf("Я победила!\n");
    else
        printf("Я проиграла!\n");*/
// -----
    FILE *filepointer = NULL;
    filepointer = fopen("Example.txt", "r");
    if(!filepointer)
    {
        fprintf(stderr, "Cannot open the file.\n");
        exit(1);
    }
// -----
    Node *root = NULL;
    Data temp;
    fscanf(filepointer, "%d ", &temp.sizestr);
    temp.str = (char *)malloc(temp.sizestr * sizeof(char));
    if(!temp.str)
    {
        fclose(filepointer);
        fprintf(stderr, "No free memory.\n");
        exit(1);
    }
    fgets(temp.str, temp.sizestr, filepointer);
    int indicator;
    fscanf(filepointer, "%d\n", &indicator);
    if(indicator)
        temp.type = noanimal;
    else
        temp.type = animal;
    addNode(&root, &root, temp, true);

    Node *tempPointer = root;
    Stack pointers = NULL;

    while(!feof(filepointer))
    {
        int way;
        fscanf(filepointer, "%d ", &way);
        fscanf(filepointer, "%d ", &temp.sizestr);
        temp.str = (char *)malloc(temp.sizestr * sizeof(char));
        if(!temp.str)
        {
            fclose(filepointer);
            fprintf(stderr, "No free memory.\n");
            exit(1);
        }
        fgets(temp.str, temp.sizestr, filepointer);
        int indicator;
        fscanf(filepointer, "%d\n", &indicator);
        if(indicator)
            temp.type = noanimal;
        else
            temp.type = animal;

        if(way)
        {
            push(tempPointer, &pointers);
            addNode(&root, &tempPointer, temp, false);
        }
        else
        {
            onTop(&tempPointer, pointers);
            pop(&pointers);
            addNode(&root, &tempPointer, temp, true);
        }
    }
// -----
    Node *p = playGame(root);
    printf("Это %s. Я угадала?\n", p->data.str);
    char answer;
    scanf(" %c", &answer);
    if(answer == 'y')
        printf("Я победила!\n");
    else
        printf("Я проиграла!\n");
// -----
    fclose(filepointer);
    return 0;
}


