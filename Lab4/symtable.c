#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

#include "symtable.h"

    struct SymbTab *next;
    struct SymbTab *first,*last;
    
    

    
    // Insert() adds an element to the symbol table object.
    // Runtime: O(1)
    void Insert(char *name, int offset)
    {
        // 0. variable declarations
        int n;  // Used to store the results of our search for element l in the symbol table

        
        // Note: *name is the address of the label
        
        
        // 1. Search for the element in the symbol table.
        n=Search(name);
        
        // 3a. If the element is found, a notification is sent to the user informing them
        //     that duplicates are not allowed.
        if(n!=-1) // -1 means an elt was not found
            printf("\n\tThe label exists already in the symbol table\n\tDuplicate can.t be inserted");
        
        // 3b. If the element is not found, create the new element and add it to the end
        //     of the list.
        else
        {
            // Variable Declarations
            struct SymbTab *p; 
            
            // Allocate space
            p=malloc(sizeof(struct SymbTab));
            
            // Make a copy of string l and set it to the label of p
            strcpy(p->name, name);
            
            // Set offset
            p->offset = offset;
            
            // Since the new element is added to the end of the list,
            // the next element is always null.
            p->next=NULL;
            
            // If the size is 0, then currently there are no elements in the table
            // prior to adding the new element.
            if(size==0)
            {
                // In a linked list, if there is exactly one element l in the list
                // then l is the first element and the last element in the list.
                first=p;
                last=p;
            }
            
            // If the size is not 0, then there exists at least one element in the
            // table prior to adding the new element.
            else
            {
                // In a linked list, if there are 1 or more elements in a list,
                // the new element is added to the end of the list and becomes the
                // last element.
                last->next=p;
                last=p;
            }
            
            // Now that an element has been added, we increment the size of our structure.
            size++;
        }
        
        // 4. Prompt the user to notify them the label was inserted.
        printf("\n\tLabel inserted\n");
    }
    
    // Display() displays the contents of the symbol table
    void Display()
    {
        int i;
        struct SymbTab *p;
        p=first;
        printf("\n\tNAME\t\tOFFSET\n");
        for(i=0;i<size;i++)
        {
            printf("\t%s\t\t%d\n",p->name,p->offset);
            p=p->next;
        }
    }
    
    // Search() checks if a label exists in the table.
    // It returns a flag of 0 if the element is not found.
    // It returns a flag of -1 if the element is found.
    // Runtime: O(n)
    int Search(char *name)
    {
        int i,flag=0;
        struct SymbTab *p;
        p=first;
        
        // Iterate through the elements
        for(i=0;i<size;i++)
        {
            // Compare each element's label in the list to the input label
            // strcmp() returns 0 if the two strings are equal and 1 if not.
            if(strcmp(p->name,name)==0)
                // The element was found so change flag to 1
                flag=1;
            // Increment element in the list
            p=p->next;
        }
        return flag;
    }// end search
    
    
    

    
