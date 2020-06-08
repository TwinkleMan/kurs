#include "data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "list.h"

void strDelete(char *string,int num)
{
    int i;

    if (strlen(string) >= 1) {
        if (num > 0) {
            while (num > 0) {
                for (i = 0; string[i] != '\0'; i++) {
                    string[i] = string[i + 1];
                }
                num--;
            }
        }
    }
}

int csvCount(FILE *df)
{
    char symbol = '\0';
    int count = 0;

    while (symbol != EOF) {
        symbol = fgetc(df);
        if (symbol == '\n') {
            count++;
        }
    }
    fseek(df,0,SEEK_SET);
    return count;
}

char *getInput()
{
    char *name = NULL;

    name = (char*)malloc(sizeof(char) * maxlen);
    puts("Enter filename:");
    fgets(name,(maxlen - referenceBuff),stdin);
    name[strlen(name) - 1] = '\0';
    strcat(name, ".csv");
    return name;
}

void strRead(FILE *df, char **dest)
{
    char symbol = '\0';
    int length = 0, multiplier = 1,errCount = 0;

    (*dest) = (char *)malloc(sizeof(char) * (readStep + 1));
    while (symbol != '\n') {
        symbol = fgetc(df);
        if (symbol >= 32) {
            if ((length % readStep == 0) && (length != 0)) {
                multiplier++;
                (*dest) = (char *) realloc((*dest), sizeof(char) * (readStep * multiplier + 1));
                if ((*dest) == NULL) {
                    perror("Ooops, looks like there's an error with memory reassignment...");
                    exit(1);
                }
            }
            (*dest)[length] = symbol;
            length++;
        } else errCount++;
    }
    (*dest)[length] = '\0';
}

void idInp(int count, char **inp, node *node) {
    char *tempStr = NULL;

    tempStr = (char *) malloc(sizeof(char) * (count + 1));
    if (tempStr != NULL) {
        strncpy(tempStr, *inp, count);
        tempStr[count] = '\0';
        node->id = atoi(tempStr);
    } else {
        perror("Ooops, seems like something's wrong with your memory!");
        exit(5);
    }
    free(tempStr);
    tempStr = NULL;
}

void nameInp(int count, int prevLen, char **inp,guitar *guitar)
{
    char *temp = NULL;

    temp = (char*)malloc(sizeof(char) * (count + 1));
    if (temp != NULL) {
        strncpy(temp,*inp,count);
        temp[count] = '\0';
        strDelete(temp, prevLen);
        guitar->name = (char*)malloc(sizeof(char) * (count + 1));
        if (guitar->name != NULL) {
            strcpy(guitar->name, temp);
        } else {
            perror("Can't copy a string, error at memory allocation!");
            exit(2);
        }
        free(temp);
        temp = NULL;
    } else {
        perror("Ooops, seems like something's wrong with your memory!");
        exit(2);
    }
}

void infoInp(int count, int prevLen, char **inp, guitar *guitar)
{
    char *temp = NULL;

    temp = (char*)malloc(sizeof(char) * (count + 1));
    if (temp != NULL) {
        strncpy(temp, *inp, count);
        temp[count] = '\0';
        strDelete(temp, prevLen);
        guitar->info = (char *) malloc(sizeof(char) * (strlen(temp) + 1));
        if (guitar->info != NULL) {
            strcpy(guitar->info, temp);
        } else {
            perror("Can't copy a string, error at memory allocation!");
            exit(3);
        }
    } else {
        perror("Ooops, seems like something's wrong with your memory!");
        exit(3);
    }
    free(temp);
    temp = NULL;
}

void pickupsInp(int count, int prevLen, char **inp, guitar *guitar)
{
    char *tempStr = NULL;

    tempStr = (char*)malloc(sizeof(char) * (count + 1));
    if (tempStr != NULL) {
        strncpy(tempStr, *inp, count);
        tempStr[count] = '\0';
        strDelete(tempStr,prevLen);
        guitar->numOfPickups = atoi(tempStr);
    } else {
        perror("Ooops, seems like something's wrong with your memory!");
        exit(4);
    }
    free(tempStr);
    tempStr = NULL;
}

void fretsInp(int count, int prevLen, char **inp, guitar *guitar)
{
    char *tempStr = NULL;

    tempStr = (char*)malloc(sizeof(char) * (count + 1));
    if (tempStr != NULL) {
        strncpy(tempStr, *inp, count);
        tempStr[count] = '\0';
        strDelete(tempStr,prevLen);
        guitar->numOfFrets = atoi(tempStr);
    } else {
        perror("Ooops, seems like something's wrong with your memory!");
        exit(5);
    }
    free(tempStr);
    tempStr = NULL;
}

void numStringsInp(int count, int prevLen, char **inp, guitar *guitar)
{
    char *tempStr = NULL;

    tempStr = (char*)malloc(sizeof(char) * (count + 1));
    if (tempStr != NULL) {
        strncpy(tempStr, *inp, count);
        tempStr[count] = '\0';
        strDelete(tempStr,prevLen);
        guitar->numOfString = atoi(tempStr);
    } else {
        perror("Ooops, seems like something's wrong with your memory!");
        exit(6);
    }
    free(tempStr);
    tempStr = NULL;
}

void menzureInp(int count, int prevLen, char **inp, guitar *guitar)
{
    char *tempStr = NULL;

    tempStr = (char*)malloc(sizeof(char) * (count + 1));
    if (tempStr != NULL) {
        strncpy(tempStr, *inp, count);
        tempStr[count] = '\0';
        strDelete(tempStr,prevLen);
        guitar->menzureLength = atof(tempStr);
    } else {
        perror("Ooops, seems like something's wrong with your memory!");
        exit(7);
    }
    free(tempStr);
    tempStr = NULL;
}

void radiusInp(int count, int prevLen, char **inp, guitar *guitar)
{
    char *tempStr = NULL;

    tempStr = (char*)malloc(sizeof(char) * (count + 1));
    if (tempStr != NULL) {
        strncpy(tempStr, *inp, count);
        tempStr[count] = '\0';
        strDelete(tempStr, prevLen);
        guitar->neckRadius = atof(tempStr);
    } else {
        perror("Ooops, seems like something's wrong with your memory!");
        exit(8);
    }
    free(tempStr);
    tempStr = NULL;
}

void stringsWidthInp(int count, int prevLen, char **inp, guitar *guitar)
{
    char *tempStr = NULL;
    int i,iteration = 0;

    tempStr = (char *) malloc(sizeof(char) * (strlen(*inp) + 1));
    if (tempStr != NULL) {
        strcpy(tempStr, *inp);
        strDelete(tempStr, prevLen);
        guitar->stringsWidth = (int*)malloc(sizeof(int) * (guitar->numOfString));
        if (guitar->stringsWidth != NULL) {
            for (i = 0; iteration < guitar->numOfString; i++) {
                if (tempStr[i] == sep || tempStr[i + 1] == '\0') {
                    guitar->stringsWidth[iteration] = atoi(tempStr);
                    strDelete(tempStr,i+1);
                    i = 0;
                    iteration++;
                }
            }
        } else {
            perror("Ooops, seems like something's wrong with your memory!");
            exit(9);
        }

    } else {
        perror("Ooops, seems like something's wrong with your memory!");
        exit(10);
    }
    free(tempStr);
    tempStr = NULL;
}

void unitFill(node *node, FILE *df)
{
    int flag = 0,i,prevLen = 0;
    char *inp = NULL;

    strRead(df,&inp);
    node->guitar = (guitar*)malloc(sizeof(guitar));
    for (i = 0;flag <= 8;i++) {
        if (inp[i] == sep || inp[i + 1] == '\0') {
            if (flag == 0) {
                //id
                idInp(i,&inp,node);
                prevLen = i + 1;
                flag++;
            } else if (flag == 1) {
                //name
                nameInp(i,prevLen,&inp,node->guitar);
                prevLen = i + 1;
                flag++;
            } else if (flag == 2) {
                //info
                infoInp(i,prevLen,&inp,node->guitar);
                prevLen = i + 1;
                flag++;
            } else if (flag == 3) {
                //pickups
                pickupsInp(i,prevLen,&inp,node->guitar);
                prevLen = i + 1;
                flag++;
            } else if (flag == 4) {
                //frets
                fretsInp(i,prevLen,&inp,node->guitar);
                prevLen = i + 1;
                flag++;
            } else if (flag == 5) {
                //number of strings
                numStringsInp(i,prevLen,&inp,node->guitar);
                prevLen = i + 1;
                flag++;
            } else if (flag == 6) {
                //menzure length
                menzureInp(i,prevLen,&inp,node->guitar);
                prevLen = i + 1;
                flag++;
            } else if (flag == 7) {
                //neck radius
                radiusInp(i,prevLen,&inp,node->guitar);
                prevLen = i + 1;
                flag++;
            } else if (flag == 8) {
                //strings width
                stringsWidthInp(i,prevLen,&inp,node->guitar);
                flag++;
            }
        }
    }
    if (inp != NULL) {
        free(inp);
        inp = NULL;
    }
}

void wait()
{
    char c;

    do {
        c = getchar();
    } while (c != '\n');
}

void scanField(char **dest,char **source,int *mult,int mod)
{
    char split[] = ";";
    int len;

    strRead(stdin, source);
    if (*dest == NULL) {
        *dest = (char*)malloc(sizeof(char) * (keyboardReadStep + 1));
        strcpy(*dest,*source);
        strcat(*dest, split);
    } else {
        len = strlen(*dest) + strlen(*source);
        if (len / (keyboardReadStep * (*mult)) >= 1) {
            (*mult)++;
            realloc(*dest,sizeof(char) * ((*mult) * keyboardReadStep + 1));
        }
        strcat(*dest, *source);
        if (mod==0) {
            strcat(*dest, split);
        }
    }
    if (source != NULL) {
        free(*source);
        *source = NULL;
    }
}

char *dataScan()
{
    char *inp = NULL,*temp = NULL,split[] = ";";
    int count = 0,numOfStrings,mult = 1;

    puts("Enter unit's ID:");
    scanField(&inp,&temp,&mult,0);

    puts("Enter unit name:");
    scanField(&inp,&temp,&mult,0);

    puts("Enter description or special info:");
    scanField(&inp,&temp,&mult,0);

    puts("Enter number of pickups:");
    scanField(&inp,&temp,&mult,0);

    puts("Enter number of frets:");
    scanField(&inp,&temp,&mult,0);

    puts("Enter number of strings:");
    strRead(stdin,&temp);
    if ((strlen(inp) + strlen(temp)) / (keyboardReadStep * mult) >= 1) {
        mult++;
        realloc(inp,sizeof(char) * (mult * keyboardReadStep + 1));
    }
    strcat(inp,temp);
    strcat(inp,split);
    numOfStrings = atoi(temp);

    puts("Enter menzure length:");
    scanField(&inp,&temp,&mult,0);

    puts("Enter neck radius:");
    scanField(&inp,&temp,&mult,0);

    puts("Enter strings width");
    while (count < numOfStrings) {
        if (count == numOfStrings - 1) {
            scanField(&inp,&temp,&mult,1);
        } else {
            scanField(&inp,&temp,&mult,0);
        }
        count++;
    }

    return inp;
}

FILE *tempfileOpen(char **fileName)
{
    FILE *pointer;
    char *tempName = (char*)malloc(sizeof(char) * (tempFileNameLength + referenceBuff));
    int i;

    do {
        for (i = 0; i < tempFileNameLength; i++) {
            tempName[i] = rand() % 26 + 97;
        }
        tempName[i] = '\0';
        strcat(tempName,".txt\0");
        if ((pointer = fopen(tempName, "r")) == NULL) {
            pointer = fopen(tempName, "wb+");
        } else {
            fclose(pointer);
            if (pointer != NULL) {
                pointer = NULL;
            }
        }
    } while (pointer == NULL);

    *fileName = tempName;
    return pointer;
}

void tempFileClose(FILE *pointer,char *fileName)
{
    int check;

    if (pointer != NULL) {
        fclose(pointer);
        pointer = NULL;
        check = remove(fileName);
        if (check != 0) {
            perror("Shit happens");
        }
    }
}

int enterCheck()
/*Function that checks that user entered number
 * border - the lowest possible value in the string*/
{
    char *temp = NULL;
    int mem = 0,flag = 1;

    do {
        if (temp != NULL) {
            free(temp);
            temp = NULL;
        }
        strRead(stdin, &temp);
        if ((mem = atoi(temp)) == 0) {
            if (temp[0] == '0') flag = 0;
            else puts("Incorrect number input!\n Please try again!");
        }
        else if (mem != 0) flag = 0;
    } while (flag);

    return mem;
}

float floatEnterCheck()
{
    char *temp = NULL;
    int flag = 1;
    float mem;

    do {
        if (temp != NULL) {
            free(temp);
            temp = NULL;
        }
        strRead(stdin, &temp);
        if ((mem = atof(temp)) == 0) {
            if (temp[0] == '0') flag = 0;
            else puts("Incorrect number input!\n Please try again!");
        }
        else if (mem != 0) flag = 0;
    } while (flag);

    return mem;
}

void reverse(char* str, int len)
{
    int i = 0, j = len - 1, temp;
    while (i < j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}

int intToStr(int x, char str[], int d)
{
    int i = 0;
    while (x) {
        str[i++] = (x % 10) + '0';
        x = x / 10;
    }
    while (i < d) str[i++] = '0';
    reverse(str, i);
    str[i] = '\0';
    return i;
}

void ftoa(float n, char *res, int afterpoint)
{
    int ipart = (int)n;
    float fpart = n - (float)ipart;
    int i = intToStr(ipart, res, 0);

    if (afterpoint != 0) {
        res[i] = '.';
        fpart = fpart * pow(10, afterpoint);
        intToStr((int)fpart, res + i + 1, afterpoint);
    }
}

int val_id(node *node)
{
    return node->id;
}

char *val_name(node *node)
{
    return node->guitar->name;
}

char *val_info(node *node)
{
    return node->guitar->info;
}

int val_numOfPickups(node *node)
{
    return node->guitar->numOfPickups;
}

int val_frets(node *node)
{
    return node->guitar->numOfFrets;
}

int val_numOfStrings(node *node)
{
    return node->guitar->numOfString;
}

float val_menzure(node *node)
{
    return node->guitar->menzureLength;
}

float val_radius(node *node)
{
    return node->guitar->neckRadius;
}

int *val_width(node *node)
{
    return node->guitar->stringsWidth;
}

node *copy_node(node *current)
{
    node *copied = NULL;
    int i;

    copied = (node*)malloc(sizeof(node) * 1);
    copied->guitar = (guitar*)malloc((sizeof(guitar)));
    if (copied && copied->guitar)
    {
        copied->guitar->name = (char*)malloc((strlen(current->guitar->name) + 1) * sizeof(char));
        copied->guitar->info = (char*)malloc((strlen(current->guitar->info) + 1) * sizeof(char));
        copied->guitar->stringsWidth = (int*)malloc(current->guitar->numOfString * sizeof(int));
        if (copied->guitar->name && copied->guitar->info && copied->guitar->stringsWidth)
        {
            memcpy(copied->guitar->name, current->guitar->name, strlen(current->guitar->name) + 1);
            memcpy(copied->guitar->info, current->guitar->info, strlen(current->guitar->info) + 1);
            copied->id = current->id;
            copied->guitar->numOfPickups = current->guitar->numOfPickups;
            copied->guitar->numOfFrets = current->guitar->numOfFrets;
            copied->guitar->numOfString = current->guitar->numOfString;
            copied->guitar->menzureLength = current->guitar->menzureLength;
            copied->guitar->neckRadius = current->guitar->neckRadius;
            for (i = 0;i < current->guitar->numOfString;i++) {
                copied->guitar->stringsWidth[i] = current->guitar->stringsWidth[i];
            }
            copied->next=NULL;
            copied->prev=NULL;
        }
        else {
            perror("Something wrong with memory allocation!");
            exit(33);
        }
    }
    return copied;
}

head *filter_char(head *info, char *string, char* (*val)(node*))
{
    head *result;
    node *current, *coppied, *temp;

    result = NULL;
    current = info->first;
    result = makeHead();
    while(current)
    {
        if(strstr((*val)(current),string))
        {
            coppied = copy_node(current);
            if(!result->first) result->first = coppied;
            else
            {
                temp=result->last;
                temp->next = coppied;
            }
            coppied->prev = result->last;
            result->last = coppied;
            result->length++;
        }
        current = current->next;
    }
    return result;
}

head *filter_float(head *head, float lower_bound, float upper_bound, float (*val)(node*))
{
    struct LData *result = NULL;
    //head * result;
    node *current, *coppied, *temp;
    
    result = NULL;
    current = head->first;
    result = makeHead();
    while(current)
    {
        if(lower_bound <= (*val)(current) && (*val)(current)<=upper_bound)
        {
            coppied = copy_node(current);
            if(!result->first) result->first = coppied;
            else
            {
                temp=result->last;
                temp->next = coppied;
            }
            coppied->prev = result->last;
            result->last = coppied;
            result->length++;
        }
        current = current->next;
    }
    return result;
}

head *filter_int(head *head, int lower_bound, int upper_bound, int (*val)(node*))
{
    struct LData *result = NULL;
    //head * result;
    node *current, *coppied, *temp;

    result = NULL;
    current = head->first;
    result = makeHead();
    while(current)
    {
        if(lower_bound <= (*val)(current) && (*val)(current)<=upper_bound)
        {
            coppied = copy_node(current);
            if(!result->first) result->first = coppied;
            else
            {
                temp=result->last;
                temp->next = coppied;
            }
            coppied->prev = result->last;
            result->last = coppied;
            result->length++;
        }
        current = current->next;
    }
    return result;
}

int check (int choice, int lower_bound)
{
    int sort;
    int n;

    if (choice == 1)
    {
        do
        {
            sort = enterCheck();
            if (sort <= 0) puts("You cannot enter values smaller than 0 (or 0)");
        } while (sort <= 0);
    }
    else
    {
        do
        {
            sort = enterCheck();
            if (sort <= 0) puts("You cannot enter values smaller than 0 (or 0)");
            if (sort < lower_bound) puts ("This can not be your upper bound. Please, try again");
        } while (sort <= 0 || sort < lower_bound);
    }
    return sort;
}

float floatEnterSort(int choice, float lower_bound)
{
    float sort;
    enum MAXLEN{max = 20};
    int n;
    char *str=NULL;
    if (choice==1)
    {
        do
        {
            strRead(stdin,&str);
            if (atof(str)>0) sort=atof(str);
            else
            {
                puts("");
                puts ("This is not decimal. Please, enter decimal");
                wait();
            }
        } while (atof(str)<=0);
    }
    else
    {
        do
        {
            strRead(stdin,&str);
            if (atof(str)>0 && atof(str)>=lower_bound) sort=atof(str);
            else
            {
                puts("");
                puts ("This can not be your upper bound. Please, try again");
                wait();
            }
        } while (atof(str)<=0 || atof(str)<lower_bound);
    }
    return sort;
}

int compare_bigger_float(float a, float b)
{
    return (a > b);
}

int compare_smaller_float(float a, float b)
{
    return (b > a);
}

int compare_bigger_int(int a,int b)
{
    return (a > b);
}

int compare_smaller_int(int a,int b)
{
    return (b > a);
}

head *sort_float (head *head, float (*val)(node*), int (*comp)(float, float))
{
    int i,j;
    struct LData *result;
    node *current, *temp;

    result = makeHead();
    if (head != NULL) {
        current = head->first;
        result->first = current;
        result->last = current;
        result->length = 1;
    }
    for (i = 1; i < head->length; i++)
    {
        for (j = 1; j < head->length; j++)
        {
            if (comp(val(current), val(current->next)))
            {
                /*if (result->first == current) result->first=current->next;
                else current->prev->next=current->next;
                if (current->next == result->last) result->last=current;
                current->next->prev=current->prev;
                current->prev=current->next;
                temp=(current->next);
                current->next=current->next->next;
                temp->next=current;*/


            }
            else current=current->next;
        }
    }
    return result;
}

head *sort_int (head *head, int (*val)(node*), int (*comp)(int, int))
{
    int i,j;
    struct LData *result;
    node *current, *temp;

    result = makeHead();
    for (i=1; i < head->length; i++)
    {
        current = head->first;
        for (j=1; j < head->length - i; j++)
        {
            if (comp(val(current), val(current->next)))
            {
                if (result->first == current) result->first=current->next;
                else current->prev->next=current->next;
                if (current->next == result->last) result->last=current;
                current->next->prev=current->prev;
                current->prev=current->next;
                temp=(current->next);
                current->next=current->next->next;
                temp->next=current;
            }
            else current = current->next;
        }
    }
    return result;
}
