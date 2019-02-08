#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

#include "symtable.h"

    struct SymbTab *next;
    struct SymbTab *first,*last;
    
    
    /* main() is a user interface that allows the user the ability to create a symbol table
     * (linked list) by inserting elements. The user can also display the table, delete
     * elements, search for an element, modify an element, and end an element.  The 
     * description of these actions are found below main().
    */
    void main()
    {
        int op,y;
        char la[10];
        do
        {
            printf("\n\tSYMBOL TABLE IMPLEMENTATION\n");
            printf("\n\t1.INSERT\n\t2.DISPLAY\n\t3.DELETE\n\t4.SEARCH\n\t5.MODIFY\n\t6.END\n");
            printf("\n\tEnter your option : ");
            scanf("%d",&op);
            switch(op)
            {
                case 1:
                    Insert();
                    break;
                case 2:
                    Display();
                    break;
                case 3:
                    Delete();
                    break;
                case 4:
                    printf("\n\tEnter the label to be searched : ");
                    scanf("%s",la);
                    y=Search(la);
                    printf("\n\tSearch Result:");
                    if(y==1)
                        printf("\n\tThe label is present in the symbol table\n");
                    else
                        printf("\n\tThe label is not present in the symbol table\n");
                    break;
                case 5:
                    //Modify(); - Removed Modify Function
                    break;
                case 6:
                    exit(0);
            }
        }while(op<6);
        
    }  /* and of main */
    
    // Insert() adds an element to the symbol table object.
    // Runtime: O(1)
    void Insert()
    {
        // 0. variable declarations
        int n;  // Used to store the results of our search for element l in the symbol table
        char l[10]; // User input data: A character array of size 10 that represents the 
                    // label of an element in the symbol table.
        
        // 1. Prompt the user to enter a label for the new element
        printf("\n\tEnter the label : ");
        scanf("%s",l);
        
        // 2. Search for the element in the symbol table.
        n=Search(l);
        
        // 3a. If the element is found, a notification is sent to the user informing them
        //     that duplicates are not allowed.
        if(n==1)
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
            strcpy(p->label,l);
            
            // Prompt the user to enter the symbol of the new element
            printf("\n\tEnter the symbol : ");
            scanf("%s",p->symbol);
            
            // Prompt the user to enter the address of the new element
            printf("\n\tEnter the address : ");
            scanf("%d",&p->addr);
            
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
        printf("\n\tLABEL\t\tSYMBOL\t\tADDRESS\n");
        for(i=0;i<size;i++)
        {
            printf("\t%s\t\t%s\t\t%d\n",p->label,p->symbol,p->addr);
            p=p->next;
        }
    }
    
    // Search() checks if a label exists in the table.
    // It returns a flag of 0 if the element is not found.
    // It returns a flag of 1 if the element is found.
    // Runtime: O(n)
    int Search(char lab[])
    {
        int i,flag=0;
        struct SymbTab *p;
        p=first;
        
        // Iterate through the elements
        for(i=0;i<size;i++)
        {
            // Compare each element's label in the list to the input label
            // strcmp() returns 0 if the two strings are equal and 1 if not.
            if(strcmp(p->label,lab)==0)
                // The element was found so change flag to 1
                flag=1;
            // Increment element in the list
            p=p->next;
        }
        return flag;
    }
    
    
    
    // Delete() removes an element from the list
    // Runtime: O(n)
    //              - If the element is found and
    //                      - the element is the first element, O(1).
    //                      - the element is not the first element, up to O(n).
    //              - If the element is not found, O(n)
    void Delete()
    {
        // 0. Variable Declarations
        int a;
        char l[10];
        struct SymbTab *p,*q;
        
        // 1. Get the first element of the list.
        p=first;
        
        // 2. Prompt the user to enter the label of an element.
        printf("\n\tEnter the label to be deleted : ");
        scanf("%s",l);
        
        // 3. Search for the element in the symbol table list.
        a=Search(l);
        
        // 3a. If the element is not found, notify the user.
        if(a==0)
            printf("\n\tLabel not found\n");
        
        // 3b. If the element is found, remove it
        else
        {
            // if the first element is the element to be removed,
            // simply change the first element to the second element (found at first.next).
            if(strcmp(first->label,l)==0)
                first=first->next;
            
            // if the last element is the element to be removed,
            // simply change the second to last element to be the last element
            else if(strcmp(last->label,l)==0)
            {
                // Make q to be p.next
                q=p->next;
                
                // If q is not the label we are looking to remove, then increment until it is
                while(strcmp(q->label,l)!=0)
                {
                    p=p->next;
                    q=q->next;
                }
                
                // Change p.next to null and make it the last element.
                p->next=NULL;
                last=p;
            }
            else
            {
                q=p->next;
                while(strcmp(q->label,l)!=0)
                {
                    p=p->next;
                    q=q->next;
                }
                p->next=q->next;
            }
            size--;
            printf("\n\tAfter Deletion:\n");
            Display();
        }
    }
    
    
