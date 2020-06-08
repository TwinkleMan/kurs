#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "menu.h"
#include "data.h"
#include "list.h"

int main()
{
    char flag,trash,*filename = NULL,*keyboardInp = NULL,*filter = NULL,*tempName = NULL;
    int i = 0,j,fileCount = 0,isRead = 0,insertPos = 0,deleteNum = 0,editNum = 0;
    int lowerB,upperB;
    float lowerFlB,upperFlB;
    head *info = NULL;
    head *sorted = NULL;
    node *p;
    FILE *df = NULL;
    FILE *temp = NULL;
    srand(time(NULL));

    do {
        //general menu
        system("cls");
        mainMenu();
        flag = getchar();
        if (flag != '\n') while ((trash = getchar()) != '\n') i++;
        if (i) flag ='-';
        switch (flag) {
            case '1':
                //file input
                info = makeHead();
                while (df == NULL) {
                    system("cls");
                    filename = getInput();
                    df = fopen(filename,"r");
                    if (df == NULL) {
                        puts("File not found! Please enter another name!\nPress ENTER to continue...");
                        wait();
                    }
                }
                puts("File opened successfully!");
                fileCount = csvCount(df);
                if (fileCount >= 1) {
                    addFirst(info,df);
                    info->last = info->first;
                    info->first->next = info->last;
                    for (j = 1;j < fileCount;j++) {
                        addLast(info,df);
                    }
                    puts("File read successfully!");
                } else puts("The file is empty!");
                puts("Press ENTER to continue!");
                wait();
                fclose(df);
                system("cls");
                do {
                    system("cls");
                    if (sorted != NULL) print_from_head(sorted);
                    else print_from_head(info);
                    tableMenu();
                    flag = getchar();
                    if (flag != '\n') while ((trash = getchar()) != '\n') i++;
                    if (i) flag ='-';
                    switch (flag) {
                        case '1':
                            //add unit
                            do {
                                system("cls");
                                if (info->first != NULL) print_from_head(info);
                                addMenu();
                                flag = getchar();
                                if (flag != '\n') while ((trash = getchar()) != '\n') i++;
                                if (i) flag = '-';
                                switch (flag) {
                                    case '1':
                                        //add last
                                        system("cls");
                                        if (filename != NULL) {
                                            free(filename);
                                            filename = NULL;
                                        }
                                        temp = tempfileOpen(&filename);
                                        if (temp == NULL) {
                                            perror("Cannot create/open temp file!");
                                            wait();
                                            exit(777);
                                        } else {
                                            system("cls");
                                            fprintf(temp, "%s\n", dataScan());
                                        }
                                        system("cls");
                                        insert(info,temp,info->length);
                                        puts("Success! Press ENTER to continue");
                                        wait();
                                        break;
                                    case '2':
                                        //add first
                                        system("cls");
                                        if (filename != NULL) {
                                            free(filename);
                                            filename = NULL;
                                        }
                                        temp = tempfileOpen(&filename);
                                        if (temp == NULL) {
                                            perror("Cannot create/open temp file!");
                                            wait();
                                            exit(777);
                                        } else {
                                            system("cls");
                                            fprintf(temp, "%s\n", dataScan());
                                        }
                                        system("cls");
                                        insert(info,temp,1);
                                        puts("Success! Press ENTER to continue");
                                        wait();
                                        break;
                                    case '3':
                                        //add at the selectes position
                                        system("cls");
                                        if (filename != NULL) {
                                            free(filename);
                                            filename = NULL;
                                        }
                                        temp = tempfileOpen(&filename);
                                        if (temp == NULL) {
                                            perror("Cannot create/open temp file!");
                                            wait();
                                            exit(777);
                                        } else {
                                            system("cls");
                                            fprintf(temp, "%s\n", dataScan());
                                        }
                                        fseek(temp,0,SEEK_SET);
                                        puts("Enter the position number");
                                        scanf("%d",&insertPos);
                                        system("cls");
                                        insert(info,temp,insertPos);
                                        puts("Success! Press ENTER to continue");
                                        getchar();
                                        wait();
                                        break;
                                    case '4':
                                        //back
                                        break;
                                    default:
                                        system("cls");
                                        puts("There's no such paragraph!");
                                        puts("Press ENTER when ready...");
                                        wait();
                                        break;
                                }
                            }while (flag != '4');
                            break;
                        case '2':
                            //delete unit
                            system("cls");
                            if (sorted != NULL) print_from_head(sorted);
                            else print_from_head(info);
                            puts("Enter ID of the unit you want to delete:");
                            deleteNum = enterCheck();
                            removeNode(info,deleteNum);
                            puts("Press ENTER to continue");
                            wait();
                            break;
                        case 3:
                            //edit unit
                            /*
                            system("cls");
                            puts("Enter ID of the unit you want to edit:");
                            editNum = enterCheck();
                            */
                            puts("under construction!");
                            wait();
                            break;
                        case 4:
                            //swap unit
                            break;
                        case 5:
                            //copy unit
                            break;
                        case '3':
                            //search
                            do {
                                system("cls");
                                if (sorted != NULL) print_from_head(sorted);
                                else print_from_head(info);
                                searchMenu();
                                flag = getchar();
                                if (flag != '\n') while ((trash = getchar()) != '\n') i++;
                                if (i) flag = '-';
                                switch (flag) {
                                    case '1':
                                        //id filter
                                        printf ("Enter a lower bound of ID\n");
                                        lowerB = check(1,0);
                                        printf ("Enter a upper bound of ID\n");
                                        upperB = check(2,lowerB);
                                        if (sorted==NULL) sorted=filter_int(info,lowerB,upperB,val_id);
                                        else sorted=filter_int(sorted,lowerB,upperB,val_id);
                                        if (filter != NULL) {
                                            free(filter);
                                            filter = NULL;
                                        }
                                        break;
                                    case '2':
                                        //name filter
                                        puts ("Enter name for search filter");
                                        strRead(stdin,&filter);
                                        if (sorted==NULL) sorted=filter_char(info,filter,val_name);
                                        else sorted=filter_char(sorted,filter,val_name);
                                        if (filter != NULL) {
                                            free(filter);
                                            filter = NULL;
                                        }
                                        break;
                                    case '3':
                                        //info filter
                                        puts ("Enter info for search filter");
                                        strRead(stdin,&filter);
                                        if (sorted==NULL) sorted=filter_char(info,filter,val_info);
                                        else sorted=filter_char(sorted,filter,val_info);
                                        if (filter != NULL) {
                                            free(filter);
                                            filter = NULL;
                                        }
                                        break;
                                    case '4':
                                        //numOfPickups filter
                                        printf ("Enter a lower bound of the number of pickups value:");
                                        lowerB = check(1,0);
                                        printf ("Enter a upper bound of the number of pickups value:");
                                        upperB = check(2,lowerB);
                                        if (sorted==NULL) sorted=filter_int(info,lowerB,upperB,val_numOfPickups);
                                        else sorted=filter_int(sorted,lowerB,upperB,val_numOfPickups);
                                        if (filter != NULL) {
                                            free(filter);
                                            filter = NULL;
                                        }
                                        break;
                                    case '5':
                                        //numOfFrets filter
                                        printf ("Enter a lower bound of the number of frets value:");
                                        lowerB = check(1,0);
                                        printf ("Enter a upper bound of the number of frets value:");
                                        upperB = check(2,lowerB);
                                        if (sorted==NULL) sorted=filter_int(info,lowerB,upperB,val_frets);
                                        else sorted=filter_int(sorted,lowerB,upperB,val_frets);
                                        if (filter != NULL) {
                                            free(filter);
                                            filter = NULL;
                                        }
                                        break;
                                    case '6':
                                        //num of strings filter
                                        printf ("Enter a lower bound of the number of strings value:");
                                        lowerB = check(1,0);
                                        printf ("Enter a upper bound of the number of strings value:");
                                        upperB = check(2,lowerB);
                                        if (sorted==NULL) sorted=filter_int(info,lowerB,upperB,val_numOfStrings);
                                        else sorted=filter_int(sorted,lowerB,upperB,val_numOfStrings);
                                        if (filter != NULL) {
                                            free(filter);
                                            filter = NULL;
                                        }
                                        break;
                                    case '7':
                                        //menzure length filter
                                        printf ("Enter a lower bound of the menzure length value:");
                                        lowerFlB = floatEnterSort(1,0);
                                        printf ("Enter a upper bound of the menzure length value:");
                                        upperFlB = floatEnterSort(2,lowerFlB);
                                        if (sorted==NULL) sorted=filter_float(info,lowerFlB,upperFlB,val_menzure);
                                        else sorted=filter_float(sorted,lowerFlB,upperFlB,val_menzure);
                                        if (filter != NULL) {
                                            free(filter);
                                            filter = NULL;
                                        }
                                        break;
                                    case '8':
                                        //neck radius filter
                                        printf ("Enter a lower bound of the necck radius value:");
                                        lowerFlB = floatEnterSort(1,0);
                                        printf ("Enter a upper bound of the neck radius value:");
                                        upperFlB = floatEnterSort(2,lowerFlB);
                                        if (sorted==NULL) sorted=filter_float(info,lowerFlB,upperFlB,val_radius);
                                        else sorted=filter_float(sorted,lowerFlB,upperFlB,val_radius);
                                        if (filter != NULL) {
                                            free(filter);
                                            filter = NULL;
                                        }
                                        break;
                                    case 'b':
                                        break;
                                    default:
                                        system("cls");
                                        puts("There's no such paragraph!");
                                        puts("Press ENTER when ready...");
                                        wait();
                                        break;
                                }
                            } while (flag != 'b');
                            break;
                        case 7:
                            //sort
                            do {
                                system("cls");
                                if (sorted != NULL) print_from_head(sorted);
                                else print_from_head(info);
                                sortMenu();
                                flag = getchar();
                                if (flag != '\n') while ((trash = getchar()) != '\n') i++;
                                if (i) flag = '-';
                                switch (flag) {
                                    case '1':
                                        //id sort
                                        system("cls");
                                        sorted = makeHead();
                                        sorted = sort_int(info,val_id,compare_smaller_int);
                                        print_from_head(sorted);
                                        wait();
                                        break;
                                    case '2':
                                        //numOfPickups sort
                                        system("cls");
                                        sorted = makeHead();
                                        sorted = sort_int(info,val_numOfPickups,compare_smaller_int);
                                        print_from_head(sorted);
                                        wait();
                                        break;
                                    case '3':
                                        //numOfFrets sort
                                        system("cls");
                                        sorted = makeHead();
                                        sorted = sort_int(info,val_frets,compare_smaller_int);
                                        print_from_head(sorted);
                                        wait();
                                        break;
                                    case '4':
                                        //num of strings sort
                                        system("cls");
                                        sorted = makeHead();
                                        sorted = sort_int(info,val_numOfStrings,compare_smaller_int);
                                        print_from_head(sorted);
                                        wait();
                                        break;
                                    case '5':
                                        //menzure length sort
                                        system("cls");
                                        sorted = makeHead();
                                        sorted = sort_float(info,val_menzure,compare_smaller_float);
                                        print_from_head(sorted);
                                        wait();
                                        break;
                                    case '6':
                                        //neck radius sort
                                        system("cls");
                                        sorted = makeHead();
                                        sorted = sort_float(info,val_radius,compare_smaller_float);
                                        print_from_head(sorted);
                                        wait();
                                        break;
                                    case 'b':
                                        break;
                                    default:
                                        system("cls");
                                        puts("There's no such paragraph!");
                                        puts("Press ENTER when ready...");
                                        wait();
                                        break;

                                }
                            } while (flag != 'b');
                            break;
                        case '4':
                            //save current table
                            //puts("Enter name of the file:");
                            tempName = getInput();
                            temp = fopen(tempName,"wb+");
                            if (sorted != NULL) {
                                p = sorted->first;
                                for (i = 0; i < sorted->length; i++) {
                                    fprintf(temp, "%d;%s;%s;%d;%d;%d;%2.f;%.2f", p->id, p->guitar->name,
                                            p->guitar->info, p->guitar->numOfPickups, p->guitar->numOfFrets,
                                            p->guitar->numOfString, p->guitar->menzureLength,
                                            p->guitar->neckRadius);
                                    for (j = 0; j < p->guitar->numOfString; j++) {
                                        fprintf(temp, ";%d", p->guitar->stringsWidth[j]);
                                    }
                                    fprintf(temp, "\n");
                                    p = p->next;
                                }
                            }
                            puts("All printed succesfully!");
                            wait();
                            fclose(temp);
                            i = 0;
                            if (filename != NULL) {
                                free(filename);
                                filename = NULL;
                            }
                            break;
                        case '9':
                            //back
                            if (sorted != NULL) sorted = NULL;
                            df = NULL;
                            break;
                        default:
                            system("cls");
                            puts("There's no such paragraph!");
                            puts("Press ENTER when ready...");
                            wait();
                            break;
                    }
                } while (flag != '9');
                //current list menu
                break;
            case '2':
                //new list from keyboard
                system("cls");
                if (filename != NULL) {
                    free(filename);
                    filename = NULL;
                }
                temp = tempfileOpen(&filename);
                if (temp == NULL) {
                    perror("Cannot create/open temp file!");
                    wait();
                    exit(777);
                } else {
                    do {
                        system("cls");
                        fprintf(temp,"%s\n",dataScan());
                        fseek(temp,0,SEEK_SET);
                        puts("Do you want to enter one more line? (1 - yes, 2 - no)");
                        flag = getchar();
                        while (flag != '1' && flag != '2') {
                            puts("There's no such paragraph!\nPress ENTER when ready...");
                            wait();
                            puts("Do you want to enter one more line? (1 - yes, 2 - no)");
                            flag = getchar();
                        }
                    } while (flag == '1');
                    system("cls");
                    fileCount = csvCount(temp);
                    if (fileCount >= 1) {
                        info = makeHead();
                        addFirst(info,temp);
                        info->last = info->first;
                        info->first->next = info->last;
                        for (j = 1;j < fileCount;j++) {
                            addLast(info,temp);
                        }
                        puts("All data read succesfully!");
                    } else puts("Looks like you haven't entered anything (or some file error happened)...");
                    puts("Press ENTER to continue!");
                    getchar();
                    wait();
                    tempFileClose(temp,filename);
                    do {
                        system("cls");
                        if (sorted != NULL) print_from_head(sorted);
                        else print_from_head(info);
                        tableMenu();
                        flag = getchar();
                        if (flag != '\n') while ((trash = getchar()) != '\n') i++;
                        if (i) flag ='-';
                        switch (flag) {
                            case '1':
                                //add unit
                                do {
                                    system("cls");
                                    if (sorted != NULL) print_from_head(sorted);
                                    else print_from_head(info);
                                    addMenu();
                                    flag = getchar();
                                    if (flag != '\n') while ((trash = getchar()) != '\n') i++;
                                    if (i) flag = '-';
                                    switch (flag) {
                                        case '1':
                                            //add last
                                            system("cls");
                                            if (filename != NULL) {
                                                free(filename);
                                                filename = NULL;
                                            }
                                            temp = tempfileOpen(&filename);
                                            if (temp == NULL) {
                                                perror("Cannot create/open temp file!");
                                                wait();
                                                exit(777);
                                            } else {
                                                system("cls");
                                                fprintf(temp, "%s\n", dataScan());
                                            }
                                            system("cls");
                                            insert(info,temp,info->length);
                                            puts("Success! Press ENTER to continue");
                                            wait();
                                            break;
                                        case '2':
                                            //add first
                                            system("cls");
                                            if (filename != NULL) {
                                                free(filename);
                                                filename = NULL;
                                            }
                                            temp = tempfileOpen(&filename);
                                            if (temp == NULL) {
                                                perror("Cannot create/open temp file!");
                                                wait();
                                                exit(777);
                                            } else {
                                                system("cls");
                                                fprintf(temp, "%s\n", dataScan());
                                            }
                                            system("cls");
                                            insert(info,temp,1);
                                            puts("Success! Press ENTER to continue");
                                            wait();
                                            break;
                                        case '3':
                                            //add at the selectes position
                                            system("cls");
                                            if (filename != NULL) {
                                                free(filename);
                                                filename = NULL;
                                            }
                                            temp = tempfileOpen(&filename);
                                            if (temp == NULL) {
                                                perror("Cannot create/open temp file!");
                                                wait();
                                                exit(777);
                                            } else {
                                                system("cls");
                                                fprintf(temp, "%s\n", dataScan());
                                            }
                                            puts("Enter the position number (ID of the new element)");
                                            scanf("%d",&insertPos);
                                            system("cls");
                                            insert(info,temp,insertPos);
                                            puts("Success! Press ENTER to continue");
                                            wait();
                                            break;
                                        case '4':
                                            //back
                                            break;
                                        default:
                                            system("cls");
                                            puts("There's no such paragraph!");
                                            puts("Press ENTER when ready...");
                                            wait();
                                            break;
                                    }
                                }while (flag != '4');
                                break;
                            case '2':
                                //delete unit
                                system("cls");
                                if (sorted != NULL) print_from_head(sorted);
                                else print_from_head(info);
                                puts("Enter ID of the unit you want to delete:");
                                deleteNum = enterCheck();
                                removeNode(info,deleteNum);
                                puts("Success! Press ENTER to continue");
                                wait();
                                break;
                            case 3:
                                //edit unit
                                /*
                                system("cls");
                                puts("Enter ID of the unit you want to edit:");
                                editNum = enterCheck();
                                */
                                puts("under construction!");
                                break;
                            case 4:
                                //swap unit
                                break;
                            case 5:
                                //copy unit
                                break;
                            case '3':
                                //search
                                do {
                                    system("cls");
                                    if (sorted != NULL) print_from_head(sorted);
                                    else print_from_head(info);
                                    searchMenu();
                                    flag = getchar();
                                    if (flag != '\n') while ((trash = getchar()) != '\n') i++;
                                    if (i) flag = '-';
                                    switch (flag) {
                                        case '1':
                                            //id filter
                                            printf ("Enter a lower bound of ID");
                                            lowerB = check(1,0);
                                            printf ("Enter a upper bound of ID");
                                            upperB = check(2,lowerB);
                                            if (sorted==NULL) sorted=filter_int(info,lowerB,upperB,val_id);
                                            else sorted=filter_int(sorted,lowerB,upperB,val_id);
                                            if (filter != NULL) {
                                                free(filter);
                                                filter = NULL;
                                            }
                                            break;
                                        case '2':
                                            //name filter
                                            puts ("Enter name for search filter");
                                            strRead(stdin,&filter);
                                            if (sorted==NULL) sorted=filter_char(info,filter,val_name);
                                            else sorted=filter_char(sorted,filter,val_name);
                                            if (filter != NULL) {
                                                free(filter);
                                                filter = NULL;
                                            }
                                            break;
                                        case '3':
                                            //info filter
                                            puts ("Enter info for search filter");
                                            strRead(stdin,&filter);
                                            if (sorted==NULL) sorted=filter_char(info,filter,val_info);
                                            else sorted=filter_char(sorted,filter,val_info);
                                            if (filter != NULL) {
                                                free(filter);
                                                filter = NULL;
                                            }
                                            break;
                                        case '4':
                                            //numOfPickups filter
                                            printf ("Enter a lower bound of the number of pickups value:");
                                            lowerB = check(1,0);
                                            printf ("Enter a upper bound of the number of pickups value:");
                                            upperB = check(2,lowerB);
                                            if (sorted==NULL) sorted=filter_int(info,lowerB,upperB,val_numOfPickups);
                                            else sorted=filter_int(sorted,lowerB,upperB,val_numOfPickups);
                                            if (filter != NULL) {
                                                free(filter);
                                                filter = NULL;
                                            }
                                            break;
                                        case '5':
                                            //numOfFrets filter
                                            printf ("Enter a lower bound of the number of frets value:");
                                            lowerB = check(1,0);
                                            printf ("Enter a upper bound of the number of frets value:");
                                            upperB = check(2,lowerB);
                                            if (sorted==NULL) sorted=filter_int(info,lowerB,upperB,val_frets);
                                            else sorted=filter_int(sorted,lowerB,upperB,val_frets);
                                            if (filter != NULL) {
                                                free(filter);
                                                filter = NULL;
                                            }
                                            break;
                                        case '6':
                                            //num of strings filter
                                            printf ("Enter a lower bound of the number of strings value:");
                                            lowerB = check(1,0);
                                            printf ("Enter a upper bound of the number of strings value:");
                                            upperB = check(2,lowerB);
                                            if (sorted==NULL) sorted=filter_int(info,lowerB,upperB,val_numOfStrings);
                                            else sorted=filter_int(sorted,lowerB,upperB,val_numOfStrings);
                                            if (filter != NULL) {
                                                free(filter);
                                                filter = NULL;
                                            }
                                            break;
                                        case '7':
                                            //menzure length filter
                                            printf ("Enter a lower bound of the menzure length value:");
                                            lowerFlB = floatEnterSort(1,0);
                                            printf ("Enter a upper bound of the menzure length value:");
                                            upperFlB = floatEnterSort(2,lowerFlB);
                                            if (sorted==NULL) sorted=filter_float(info,lowerFlB,upperFlB,val_menzure);
                                            else sorted=filter_float(sorted,lowerFlB,upperFlB,val_menzure);
                                            if (filter != NULL) {
                                                free(filter);
                                                filter = NULL;
                                            }
                                            break;
                                        case '8':
                                            //neck radius filter
                                            printf ("Enter a lower bound of the necck radius value:");
                                            lowerFlB = floatEnterSort(1,0);
                                            printf ("Enter a upper bound of the neck radius value:");
                                            upperFlB = floatEnterSort(2,lowerFlB);
                                            if (sorted==NULL) sorted=filter_float(info,lowerFlB,upperFlB,val_radius);
                                            else sorted=filter_float(sorted,lowerFlB,upperFlB,val_radius);
                                            if (filter != NULL) {
                                                free(filter);
                                                filter = NULL;
                                            }
                                            break;
                                        case 'b':
                                            break;
                                        default:
                                            system("cls");
                                            puts("There's no such paragraph!");
                                            puts("Press ENTER when ready...");
                                            wait();
                                            break;
                                    }
                                } while (flag != 'b');
                                break;
                            case 7:
                                //sort
                                do {
                                    system("cls");
                                    if (sorted != NULL) print_from_head(sorted);
                                    else print_from_head(info);
                                    flag = getchar();
                                    if (flag != '\n') while ((trash = getchar()) != '\n') i++;
                                    if (i) flag = '-';
                                    switch (flag) {
                                        case '1':
                                            //id sort
                                            system("cls");
                                            sorted = makeHead();
                                            sorted = sort_int(info,val_id,compare_smaller_int);
                                            print_from_head(sorted);
                                            wait();
                                            break;
                                        case '2':
                                            //numOfPickups sort
                                            system("cls");
                                            sorted = makeHead();
                                            sorted = sort_int(info,val_numOfPickups,compare_smaller_int);
                                            print_from_head(sorted);
                                            wait();
                                            break;
                                        case '3':
                                            //numOfFrets sort
                                            system("cls");
                                            sorted = makeHead();
                                            sorted = sort_int(info,val_frets,compare_smaller_int);
                                            print_from_head(sorted);
                                            wait();
                                            break;
                                        case '4':
                                            //num of strings sort
                                            system("cls");
                                            sorted = makeHead();
                                            sorted = sort_int(info,val_numOfStrings,compare_smaller_int);
                                            print_from_head(sorted);
                                            wait();
                                            break;
                                        case '5':
                                            //menzure length sort
                                            system("cls");
                                            sorted = makeHead();
                                            sorted = sort_float(info,val_menzure,compare_smaller_float);
                                            print_from_head(sorted);
                                            wait();
                                            break;
                                        case '6':
                                            //neck radius sort
                                            system("cls");
                                            sorted = makeHead();
                                            sorted = sort_float(info,val_radius,compare_smaller_float);
                                            print_from_head(sorted);
                                            wait();
                                            break;
                                        case 'b':
                                            break;
                                        default:
                                            system("cls");
                                            puts("There's no such paragraph!");
                                            puts("Press ENTER when ready...");
                                            wait();
                                            break;

                                    }
                                } while (flag != 'b');
                                break;
                            case '4':
                                //save current table
                                puts("Enter name of the file:");
                                strRead(stdin,&filename);
                                temp = fopen(filename,"wb+");
                                if (sorted != NULL) {
                                    while (p != NULL) {
                                        p = sorted->first;
                                        for (i = 0; i < sorted->length; i++) {
                                            fprintf(temp, "%d;%s;%s;%d;%d;%d;%2f;%2f", p->id, p->guitar->name,
                                                    p->guitar->info, p->guitar->numOfPickups, p->guitar->numOfFrets,
                                                    p->guitar->numOfString, p->guitar->menzureLength,
                                                    p->guitar->neckRadius);
                                            for (j = 0; j < p->guitar->numOfString; j++) {
                                                fprintf(temp, ";%d", p->guitar->stringsWidth[j]);
                                            }
                                        }
                                        fprintf(temp, "\n");
                                        p = p->next;
                                    }
                                }
                                puts("All printed succesfully!");
                                getchar();
                                wait();
                                fclose(temp);
                                if (filename != NULL) {
                                    free(filename);
                                    filename = NULL;
                                }
                                break;
                            case '9':
                                //back
                                if (sorted != NULL) sorted = NULL;
                                df = NULL;
                                break;
                            default:
                                system("cls");
                                puts("There's no such paragraph!");
                                puts("Press ENTER when ready...");
                                wait();
                                break;
                        }
                    } while (flag != '9');
                }
                break;
            case '3':
                //print help
                puts("Enjoy yourselves!");
                wait();
                break;
            case '0':
                //clean everything
                if (info != NULL) clearList(info);
                if (sorted != NULL) clearList(sorted);
                if (df != NULL) df = NULL;
                if (p != NULL) {
                    p = NULL;
                }
                if (filename != NULL) {
                    free(filename);
                    filename = NULL;
                }
                if (info != NULL) {
                    if (info->last != NULL) {
                        free(info->last);
                        info->last = NULL;
                    }
                    if (info->first != NULL) {
                        free(info->first);
                        info->first = NULL;
                    }
                    free(info);
                    info = NULL;
                }
                exit(0);
            default:
                system("cls");
                puts("There's no such paragraph!");
                puts("Press ENTER when ready...");
                wait();
                break;
        }
    } while (flag != 0);

}
