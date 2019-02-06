/*	Kay Sweebe
	CS370
	Lab 2.1
	January 18, 2019

	The changes I made were:
		- To print the line number, the format string %d needed to be passed an integer. The 
		  integer used was newline which is a counter that counts the current line number. 
		- The directive for the newline character \n was added such that when a newline
		  was found, the counter newline was incremented by one and we printed a newline.



*/

         /* simple lex program which removes comments from a source program
            The main key is that a variable "comment" is set when the start of a comment
            is seen and then unset when the ending set is seen.  It is possible to have
            two starts closed by one end.

            Shaun Cooper
            January 2015
 
         */
        int comment = 0;
        int debug=0;  /* out prints debug statements if desired */
        int newline = 1; /* counts number of newlines in input */
%%

"/*"	{
	if (comment && debug) fprintf(stderr,
		" >>>>>>>> line %d: Possible Nested comment <<<<<<<<<<\n", newline);
	comment = 1;
	}

"*/"	{
          if (!comment) printf("%s",yytext); /*print out if it is not in a comment */
  	  comment = 0;
	}
.       { if (!comment) printf("%s",yytext);}

\n	{
	newline++; /* count number of lines in file */
        printf("\n");
	}
%%

int yywrap(void)
{ return 1;
}

main()
{
  yylex();
  
}

