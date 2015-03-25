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
    Node *root = NULL;
    FILE *filepointer = NULL;
    filepointer = fopen("Example.txt", "r");
    if(!filepointer)
    {
        fprintf(stderr, "Cannot open the file.\n");
        exit(1);
    }
// -----
    char *str = NULL;
    int lengthOfString;
    fscanf(filepointer, "%d ", &lengthOfString);
    str = (char *)malloc(lengthOfString * sizeof(char));
    if(!str)
    {
        fclose(filepointer);
        fprintf(stderr, "No free memory.\n");
        exit(1);
    }
    fgets(str, lengthOfString, filepointer);
    puts(str);
    int indicator;
    fscanf(filepointer, "%d", &indicator);
    printf("%d", indicator);
// -----
    free(str);
    str = NULL;
    fclose(filepointer);
    return 0;
}


