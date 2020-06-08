#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "data.h"

head *makeHead()
{
    head *temp = NULL;

    temp = (head*)malloc(sizeof(head));
    if (temp != NULL) {
        temp->first = NULL;
        temp->last = NULL;
        temp->length = 0;
    } else {
        perror("NULL head exception!");
        exit(1);
    }
    return temp;
}

void addFirst(head *head, FILE *df)
{
    node *temp = NULL,*p;
    char *num = NULL;

    temp = (node*)malloc(sizeof(node));
    temp->guitar = (guitar*)malloc(sizeof(guitar));
    if (temp != NULL && temp->guitar != NULL) {
        unitFill(temp,df);
        temp->next = head->first;
        if (head->first != NULL) head->first->prev = temp;
        temp->prev = NULL;
        head->first = temp;
        if (head->length == 0) head->last = temp;
        head->length++;
    }
}

void addLast(head *head,FILE *df)
{
    node *temp = NULL;
    char *data = NULL;

    temp = (node*)malloc(sizeof(node));
    temp->guitar = (guitar*)malloc(sizeof(guitar));
    if (temp != NULL && temp->guitar != NULL) {
        unitFill(temp,df);
        head->length++;
        temp->next = NULL;
        temp->prev = head->last;
        head->last->next = temp;
        head->last = temp;
    }
}

void insert(head *head,FILE *df,int index)  //set the unit on the position with number 'index'
{
    node *p,*temp = NULL;
    char *data = NULL;
    int i = 1;

    if (index < 1) {
        puts("You can't create node at this place!");
    } else {
        if (index == 1) {
            addFirst(head,df);
        } else if (index > 1) {
            if ((temp = (node *) malloc(sizeof(node))) != NULL) {
                p = head->first;
                while (i < (index - 1) && p != NULL) {
                    p = p->next;
                    i++;
                }
                if (p == NULL) {
                    puts("No such node!");
                } else {
                    unitFill(temp, df);
                    temp->prev = p;
                    temp->next = p->next;
                    p->next = temp;
                    head->length++;
                }
            }
        }
    }
}

void print_from_head(head *head)
{
    node *p;
    int i,j = 0;

    p = head->first;
    if (p == NULL) {
        puts("There's nothing to print");
    } else do {
        printf("ID: %d\n",p->id);
        printf("Name: %s\n", p->guitar->name);
        printf("Description/info: %s\n",p->guitar->info);
        printf("Number of Pickups: %d\n", p->guitar->numOfPickups);
        printf("Number of frets: %d\n",p->guitar->numOfFrets);
        printf("Number of strings: %d\n",p->guitar->numOfString);
        printf("Menzure length: %.2f\n",p->guitar->menzureLength);
        printf("Neck radius: %.2f\n",p->guitar->neckRadius);
        printf("Strings width: ");
        for (i = 0;i < (p->guitar->numOfString);i++) {
            printf("%d ",p->guitar->stringsWidth[i]);
        }
        p = p->next;
        printf("\n\n");
        j++;
    } while (j < head->length);
}

void print_from_tail(head *head)
{
    node *p;
    int i;

    p = head->last;
    if (p == NULL) {
        puts("There's nothing to print");
    }
    do {
        printf("ID: %d\n",p->id);
        printf("Name: %s\n", p->guitar->name);
        printf("Description/info: %s\n",p->guitar->info);
        printf("Number of Pickups: %d\n", p->guitar->numOfPickups);
        printf("Number of frets: %d\n",p->guitar->numOfFrets);
        printf("Number of strings: %d\n",p->guitar->numOfString);
        printf("Menzure length: %.2f\n",p->guitar->menzureLength);
        printf("Neck radius: %.2f\n",p->guitar->neckRadius);
        printf("Strings width: ");
        for (i = 0;i < (p->guitar->numOfString);i++) {
            printf("%d ",p->guitar->stringsWidth[i]);
        }
        p = p->prev;
        printf("\n\n");
    } while (p != NULL);
}

void delete(node **unit)
{
    if ((*unit)->guitar->name != NULL) {
        free((*unit)->guitar->name);
        (*unit)->guitar->name = NULL;
    }
    if ((*unit)->guitar->info != NULL) {
        free((*unit)->guitar->info);
        (*unit)->guitar->info = NULL;
    }
    if ((*unit)->guitar->stringsWidth != NULL) {
        free((*unit)->guitar->stringsWidth);
        (*unit)->guitar->stringsWidth = NULL;
    }
    free((*unit)->guitar);
    (*unit)->guitar = NULL;
    free((*unit));
    unit = NULL;
}

void pop(head *head)
{
    node *temp = NULL;

    if (head->first != NULL) {
        temp = head->first;
        head->first = head->first->next;
        head->first->prev = NULL;
        head->length--;
        delete(&temp);
        puts("Success!");
    } else puts("There's nothing to delete!");
}

void removeNode(head *head,int i) //deletes the 'i' unit of the list
{
    node *temp = NULL;
    int j = 1;

    if (i > 0) {
        temp = head->first;
        if (i == 1) {
            pop(head);
        } else {
            do {
                temp = temp->next;
                j++;
            } while (j != i && temp != NULL);
            if (temp == NULL) {
                puts("No such node!");
            } else {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                delete(&temp);
                head->length--;
                puts("Deleted successfully!");
            }
        }
    } else {
        puts("You cannot delete the node before head! (node does not exist!)");
    }
    if (temp != NULL) {
        temp = NULL;
    }
}

void clearList(head *head)
{
    int i;
    node *temp = NULL;

    temp = head->first;
    for(i = 0;i < head->length;i++) {
        if (temp->guitar->name != NULL) {
            free(temp->guitar->name);
            temp->guitar->name = NULL;
        }
        if (temp->guitar->info != NULL) {
            free(temp->guitar->info);
            temp->guitar->info = NULL;
        }
        if (temp->guitar->stringsWidth != NULL) {
            free(temp->guitar->stringsWidth);
            temp->guitar->stringsWidth = NULL;
        }
        free(temp->guitar);
        temp->guitar = NULL;
        if (temp->prev !=NULL) {
            temp->prev = NULL;
        }
        temp = temp->next;
    }
    if (head->first->next != NULL) {
        free(head->first->next);
        head->first->next = NULL;
    }
}

int *maxFieldLen(head *head)
//search for the field with the max length
{
    int *lengths,i,key = 0;
    char *temp = NULL;
    node *p;

    p = head->first;
    lengths = (int*)calloc(fields,sizeof(int));
    temp = (char*)malloc(sizeof(char) * lenBuff);
    if (p != NULL && lengths != NULL) {
        for (i = 0; i < head->length; i++) {
            if (strlen(p->guitar->name) > lengths[key]) lengths[key] = strlen(p->guitar->name);
            key++;
            if (strlen(p->guitar->info) > lengths[key]) lengths[key] = strlen(p->guitar->info);
            key++;
            if (strlen(itoa(p->guitar->numOfPickups,temp,10)) > lengths[key]) lengths[key] = strlen(itoa(p->guitar->numOfPickups,temp,10));
            if (temp != NULL) {
                free(temp);
            }
            key++;
            if (strlen(itoa(p->guitar->numOfFrets,temp,10)) > lengths[key]) lengths[key] = strlen(itoa(p->guitar->numOfFrets,temp,10));
            if (temp != NULL) {
                free(temp);
            }
            key++;
            if (strlen(itoa(p->guitar->numOfString,temp,10)) > lengths[key]) lengths[key] = strlen(itoa(p->guitar->numOfString,temp,10));
            if (temp != NULL) {
                free(temp);
            }
            key++;
            ftoa(p->guitar->menzureLength,temp,2);
            if (strlen(temp) > lengths[key]) lengths[key] = strlen(temp);
            if (temp != NULL) {
                free(temp);
            }
            key++;
            ftoa(p->guitar->neckRadius,temp,2);
            if (strlen(temp) > lengths[key]) lengths[key] = strlen(temp);
            if (temp != NULL) {
                free(temp);
            }
            key++;
            //перевод численных значений в строку и оценка их длины
        }
    }
}
