#include<stdio.h>

#include<malloc.h>
#include<string.h>
#include<stdlib.h>


#ifndef _SYMTAB
#define _SYMTAB

int size=0;
void Insert(char *name, int offset);
void Display();
//void Delete();
int Search(char *name);

/* SymbTab structure is an object with attributes:
 *      label: An array of size 10.
 *      symbol: An array of size 10.
 *      addr: An int that stores the address of our object.
 *      *next: The memory location of the next element in the symbol table.
 *             If there is no next element, the value is NULL. 
 *      *first: The memory location of the first element in the symbol table.
 *              If there is no first element, the value is NULL.
 *      *last: The memory location of the last element in the symbol table.
 *              If there is no last element, the value is NULL.
*/
struct SymbTab
{
    char *name;
    int offset;
    struct SymbTab *next;
    struct SymbTab *first;
    struct SymbTab *last;
};

#endif
