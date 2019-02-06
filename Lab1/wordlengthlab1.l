     /*  Kay Sweebe
         CS370
         Lab 1 -- using UNIX and lex
         January 18, 2018

	 Input: A file

         Output: A frequency count of alphabetic strings and the number of numbers found within the file.

         Definitions: 
             counting array lgths of size 100
             counting int count initially set to 0

         Rules:
             For each word found ([a-zA-Z]+), we increment the counter in the counting array at the 
             index value equivalent to the size of the word.
             
             For each number found ([0-9]+), we increment the counter count.

             If the character is any character except newline (.) or newline (\n), do nothing.

     */

         

     /*  This lex routine uses a counting array to match alphabeticstrings 
         and make a frequency count.
  
         The real item to notice is that yywrap() is called at EOF and then is run
         to do what we need to do.   yywrap() returns true when we have a successful 
         end to the program.  We may want to return false (0) if we want to lexing process 
         to fail 

        Shaun Cooper
        January 2015
   */
	int lgths[100];
        int count=0;
%%
[a-zA-Z]+	{lgths[yyleng]++; // this is a comment
                }
[0-9]+          {count++;         // the curly braces are used to make compound statements
                }
.	|
\n	;
%%
yywrap()
{
	int i;
	printf("Length  No. words\n");

        // Print the size of the words and their corresponding frequency
	for (i=1; i<100; i++) {
		if (lgths[i] > 0) {
			printf("%5d%10d\n",i,lgths[i]);
		}
	}
        // Print the number of numbers found
        printf("Number of numbers: %d \n ",count);
	return(1);
}

main()
{  yylex();

}
