#include "menu.h"
#include <stdio.h>

void mainMenu()
{
    puts("1 - Read list from file\n");
    puts("2 - Create new list from keyboard\n");
    puts("3 - Help\n");
    puts("0 - Quit\n");
}

void tableMenu()
{
    puts("1 - Add unit\n");
    puts("2 - Delete unit\n");
    //puts("3 - Edit unit\n");
    //puts("4 - Swap unit\n");
    //puts("5 - Copy unit\n");
    puts("3 - Search by field\n");
    //puts("7 - Proceed to sorting\n");
    puts("4 - Save current table\n");
    puts("9 - Back\n");
}

void searchMenu()
{
    puts ("1 - Enter id filter");
    puts ("2 - Enter name filter");
    puts ("3 - Enter info filter");
    puts ("4 - Enter number of pickups filter");
    puts ("5 - Enter number of frets filter");
    puts ("6 - Enter number of strings filter");
    puts ("7 - Enter menzure length filter");
    puts ("8 - Enter neck radius filter");
    puts ("b - Back");
}

void addMenu()
{
    puts("1 - Add unit at the end of the list\n");
    puts("2 - Add unit at the beginnig of the list\n");
    puts("3 - Add unit at the selected position (count starts with '1')\n");
    puts("4 - Back\n");
}

void sortMenu()
{
    puts ("1 - Search by id");
    puts ("2 - Search by number of pickups");
    puts ("3 - Search by number of frets");
    puts ("4 - Search by number of strings");
    puts ("5 - Search by menzure length");
    puts ("6 - Search by neck radius");
    puts ("b - Back");
}
