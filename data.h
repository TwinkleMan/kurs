#ifndef GUITARCATALOG_DATA_H
#define GUITARCATALOG_DATA_H
#include <stdio.h>
#include "list.h"

enum values {
    nameLength = 35,
    inputLength = 31,
    readStep = 15,
    maxlen = 45,
    referenceBuff = 5,
    keyboardReadStep = 70,
    sep = ';',
    tempFileNameLength = 4,
    intArrMax = 5
};

void strDelete(char *string,int num);   //delete 'num' symbols from the beginnging of the string
int csvCount(FILE *df);
char *getInput();   //reads name of the file
void strRead(FILE *df,char **dest); //reads data from df and saves it in dest
void wait();    //waits for user to press enter
void reverse(char* str, int len);
int intToStr(int x, char str[], int d);
void ftoa(float n, char *res, int afterpoint);

void unitFill(node *node, FILE *df); //fills the guitar field with data from df

void idInp(int count, char **inp, node *node);
void nameInp(int count, int prevLen, char **inp, guitar *guitar);   //enters name in the unit
void infoInp(int count, int prevLen, char **inp, guitar *guitar);   //enters info in the unit
void pickupsInp(int count, int prevLen, char **inp, guitar *guitar);
void fretsInp(int count, int prevLen, char **inp, guitar *guitar);
void numStringsInp(int count, int prevLen, char **inp, guitar *guitar);
void menzureInp(int count, int prevLen, char **inp, struct unit *guitar);
void radiusInp(int count, int prevLen, char **inp, struct unit *guitar);
void stringsWidthInp(int count, int prevLen, char **inp, guitar *guitar);
void scanField(char **dest,char **source,int *mult,int mod);
char *dataScan();
FILE *tempfileOpen(char **fileName);
void tempFileClose(FILE *pointer,char *fileName);
int enterCheck();
int check (int choice, int lower_bound);
float floatEnterSort(int choice, float lower_bound);
float floatEnterCheck();
int compare_bigger_float(float a, float b);
int compare_smaller_float(float a, float b);
int compare_bigger_int(int a,int b);
int compare_smaller_int(int a,int b);

int val_id(node *node);
char *val_name(node *node);
char *val_info(node *node);
int val_numOfPickups(node *node);
int val_frets(node *node);
int val_numOfStrings(node *node);
float val_menzure(node *node);
float val_radius(node *node);
int *val_width(node *node);

node *copy_node (node *current);
head *filter_char (head *info, char *string, char* (*val)(node*));
head *filter_float(head *head, float lower_bound, float upper_bound, float (*val)(node*));
head *filter_int(head *head, int lower_bound, int upper_bound, int (*val)(node*));
head *sort_float (head *head, float (*val)(node*), int (*comp)(float, float));
head *sort_int (head *head, int (*val)(node*), int (*comp)(int, int));

#endif //GUITARCATALOG_DATA_H
