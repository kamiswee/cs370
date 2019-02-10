/*	Kay Sweebe
	CS370
	February 10, 2019
	Lab4

	The changes made to this lab include:
		- adding a declaration such that if a variable is found, lex returns a token VARIABLE
          as a string
        - modifying a declaration such that if a number is found, lex returns a token INTEGER
          as an integer

*/




/*                 Small LEX routine which returns two formal tokens (INTEGER and VARIABLE)
                   along with single string elements like '+'.
 
                    This LEX definition is the companion to the docalc.y YACC routine which
                   is a simple calculator

                    Shaun Cooper
                    January 2015
*/
%{

int mydebug=1;
#include "y.tab.h"
%}


%%
int   {if (mydebug) fprintf(stderr, "int found\n");}


[a-zA-Z][a-zA-Z0-9]*		{
                        // A variable is defined as a letter followed by 
                        // any number of alphanumeric characters after that.
                        if (mydebug) fprintf(stderr,"Letter found\n"); 
                        
                        // Note: Since we created a union, we need to be specific about
                        // whether we are sending a string or an integer.
                        yylval.string = strdup(yytext);
                        
                        // Return the token VARIABLE to yacc
                        return(VARIABLE);}
                       
[0-9][0-9]*	{
                // Intakes a number between 0 and 99
                if (mydebug) fprintf(stderr,"Digit found\n"); 
                
                // Note: Since we created a union, we need to be specific about
                // whether we are sending a string or an integer.
                yylval.string=atoi((const char *)yytext); 
                
                // Return the token INTEGER to yacc
                return(INTEGER);
                       }
                       
[ \t]		{if (mydebug) fprintf(stderr,"Whitespace found\n");}

[=\-+*/%&|()] 	{ if (mydebug) fprintf(stderr,"return a token %c\n",*yytext); 
                       return (*yytext);}
                       
\n 		{ if (mydebug) fprintf(stderr,"cariage return %c\n",*yytext); 
                       return (*yytext);}


%%

int yywrap(void)
{ return 1;}


