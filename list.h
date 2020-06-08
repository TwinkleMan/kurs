#ifndef GUITARCATALOG_LIST_H
#define GUITARCATALOG_LIST_H
#include <stdio.h>

enum fields {
    fields = 7,
    lenBuff = 10
};

typedef struct unit {   //main data structure
    char *name;
    char *info;
    int numOfPickups;
    int numOfFrets;
    int numOfString;
    float menzureLength;
    float neckRadius;
    int *stringsWidth;
} guitar;

typedef struct list_unit {  //list structure with prev and next list units pointers
    int id;
    guitar *guitar;
    struct list_unit *next;
    struct list_unit *prev;
} node;

typedef struct LData {  //structure that keeps all the main list data
    int length;
    node *first;
    node *last;
} head;

head *makeHead();    //create structure for all main list info
void addFirst(head *head,FILE *df);
void addLast(head *head,FILE *df);
void insert(head *head,FILE *df,int index);  //set the unit on the position with number 'index'
void print_from_head(head *head);
void print_from_tail(head *head);
void delete(node **unit);
void pop(head *head);
void removeNode(head *head,int i); //deletes the 'i' unit of the list
void clearList(head *head);

#endif //GUITARCATALOG_LIST_H
