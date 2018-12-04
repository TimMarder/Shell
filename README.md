# Project 1 - Shell[ing] out commands

## Tim Marder & Sophia Xia

### Features Implemented

- Reads one line at a time and separates command from args.
- Forks and executes commands.
- Successfully runs exit and cd commands.
- Reads and runs multiple commands.
- Redirection!
- Piping (basic only)

### Features not implemented

- Piping with commands longer than 1 word.

### Bugs

Piping only works with commands that are one word. If more than one is used, the pipe is not recognized.

### Functions

#### *int count_tok(char *input)*
TAKES A STRING AND RETURNS HOW MANY TOKENS ARE IN IT ACCORDING TO HOW MANY SPACES ARE IN THE STRING

#### char **parse(char *line, int numtok)
TAKES A STRING AND THE NUMBER OF TOKENS IN THE STRING SEPARATES THE STRING AT THE SPACES RETURNS A DOUBLE POINTER TO THE SEPARATED STRINGS

#### char **mult_parse(char *line, int numtok)
TAKES IN A STRING, REMOVES THE NEWLINE, SEPARATES IT BY
   SEMICOLONS, AND RETURNS A DOUBLE POINTER

#### void redirect_out(char **parsed)
TAKES A DOUBLE POINTER AND FORKS A CHILD
   OPENS A FILE DUPLICATE OF STDOUT AND EXECUTES THE COMMAND
   RETURNS VOID

#### void redirect_in(char **parsed)
TAKES IN A DOUBLE POINTER AND
   REDIRECTS THE INPUT OF A COMMAND FROM A FILE
   RETURNS VOID

#### void pipes(char **parsed)
TAKES IN A DOUBLE POINTER AND FORKS A CHILD
   CREATES A PIPE AND THE OUTPUT OF THE FIRST COMMAND
   BECOMES THE INPUT OF THE SECOND COMMAND
   RETURNS VOID
   
#### int run_cmd(char *input)
TAKES IN A STRING AND CALLS PARSE ON IT
   THEN IT DETERMINES IF THE COMMAND IS CD OR EXIT
   IN WHICH CASE IT WILL BE IMMEDIATELY IMPLEMENTED
   IF IT ISN'T EITHER OF THOSE, IT WILL FORK A CHILD
   AND MAKE THE CHILD RUN THE COMMAND
 
#### void run_mult_cmd(char *input)
TAKES IN A STRING, CALLS MULT_PARSE ON THE STRING,
     AND CALLS RUN_CMD ON EACH INDEX OF THE PARSED STRING
     RETURNS VOID
     
#### int main(int argc, int *argv[])
MAIN COMMAND
