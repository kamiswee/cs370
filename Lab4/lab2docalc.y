%{
/*	Kay Sweebe
 *	CS370
 *	January 25, 2019
 *	Lab2.2
 *
 *	The changes made to this lab include:
 *		- Extend the context free grammer of the calculator to intake variables
 *      - Create a %UNION type in YACC to allow LEX to return integer or string
 *      - 
 *		  so that the first ($1) and third ($3) tokens are multiplied together. The result is
 *		  stored as an expression.
 *
 *
 */



/*
 *			**** CALC ****
 *
 * This routine will function like a desk calculator
 * There are 26 integer registers, named 'a' thru 'z'
 *
 */

/* This calculator depends on a LEX description which outputs either VARIABLE or INTEGER.
   The return type via yylval is integer 

   When we need to make yylval more complicated, we need to define a pointer type for yylval 
   and to instruct YACC to use a new type so that we can pass back better values
 
   The registers are based on 0, so we substract 'a' from each single letter we get.

   based on context, we have YACC do the correct memory look up or the storage depending
   on position

   Shaun Cooper
    January 2015

   problems  fix unary minus, fix parenthesis, add multiplication
   problems  make it so that verbose is on and off with an input argument instead of compiled in
*/


	/* begin specs */
#include <stdio.h>
#include <ctype.h>
#include "lex.yy.c"
#include "symtable.c"

int regs[26];
int base, debugsw;

void yyerror (s)  /* Called by yyparse on error */
     char *s;
{
  printf ("%s\n", s);
}


%}
/*  Defines the start symbol, what values come back from LEX and how the operators are 
    associated.
    
    The start symbol is P. We also have tokens INTEGER and VARIABLE. Since a token is
    going from one to two tokens, we want to include a %UNION type in yacc to specify
    in our grammer than an expression can be of type integer or string.

*/

%start P


%token <integer> INTEGER 
%token <string> VARIABLE


%left '|'
%left '&'
%left '+' '-'
%left '*' '/' '%'
%left UMINUS

%union
{
    int integer;
    char *string;
}

// We have to tell yacc to consider expressions as numbers and not strings.
// This is necessary since we added in a union.
%type <integer> expr



%%	/* end specs, begin rules  */
P       :   DECLS list; // declarations first and then list (statements, expressions, etc.)

DECLS   :   DECLS DECL
        |   /*empty*/
        ;
    
DECL    :   INT VARIABLE ';' '\n' 
            { fprintf(stderr, "Variable found: %s\n", $2);}
        ;

list	:	/* empty */
	|	list stat '\n'
	|	list error '\n'
			{ yyerrok; }
	;

stat	:	expr
			{ fprintf(stderr,"the anwser is%d\n", $1); }
	|	VARIABLE '=' expr
			{ //regs[$1] = $3; }
			}
	;

expr	:	'(' expr ')'
			{ $$ = $2; }
	|	expr '-' expr
			{ $$ = $1 - $3; }
	|	expr '+' expr
			{ $$ = $1 + $3; }
	|	expr '/' expr
			{ $$ = $1 / $3; }
	|	expr '*' expr // this was added
			{ $$ = $1 * $3; } // this was added
	|	expr '%' expr
			{ $$ = $1 % $3; }
	|	expr '&' expr
			{ $$ = $1 & $3; }
	|	expr '|' expr
			{ $$ = $1 | $3; }
	|	'-' expr	%prec UMINUS // this was modified
			{ $$ = -$2; }
	|	VARIABLE
			{ //$$ = regs[$1]; fprintf(stderr,"found a variable value =%d\n",$1); 
			}
	|	INTEGER {$$=$1; fprintf(stderr,"found an integer\n");}
	
	;



%%	/* end of rules, start of program */

int main()
{ yyparse();
}
