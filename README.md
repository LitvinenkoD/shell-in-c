Testing:
run make, then ./tester to test

our ./mysh program performs all necessary tasks.
we tried to organize the filestructure well, so that it's more manageble to develop and read the program.
src and include folders contain .c and .h files for the implementation.

program runtime is divided into 3 main parts
1 get a line of input from whatever source is used
2 break the line into words, and break words into tokens, then expand any wildcard tokens 
and store the final result in a "tokens" list.
3 through a series of if statements, determine the nature of the request by analyzing the token list.
tokenization is almost check free and whatever the user inputs will be turned into tokens to work from.

all necessary functionality is working: redirection, interactive/batch modes, then/else statements, piping, linux functions, wildcards and directory traversal.
