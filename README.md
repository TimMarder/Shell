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

- Piping only works with commands that are one word. If more than one is used, the pipe is not recognized.
- Spaces around semi colons, redirection symbols, and pipes cause the program not to work. (Example: "ls;ls" works but "ls ; ls" does not.)

### Functions

#### _int count_tok(char *input)_
Takes a string and returns how many tokens are in it according to how many spaces are in the string.

#### _char **parse(char *line, int numtok)_
Takes a string and the number of tokens in the string separates the string at the spaces returns a double pointer to the separated strings.

#### _char **mult_parse(char *line, int numtok)_
Takes in a string, removes the newline, separates it by semicolons, and returns a double pointer.

#### _void redirect_out(char **parsed)_
Takes a double pointer and forks a child opens a file duplicate of stdout and executes the command returns void.

#### _void redirect_in(char **parsed)_
Takes in a double pointer and redirects the input of a command from a file returns void.

#### _void pipes(char **parsed)_
Takes in a double pointer and forks a child creates a pipe and the output of the first command becomes the input of the second command returns void.
   
#### _int run_cmd(char *input)_
Takes in a string and calls parse on it then it determines if the command is cd or exit in which case it will be immediately implemented if it isn't either of those, it will fork a child and make the child run the command.
 
#### _void run_mult_cmd(char *input)_
Takes in a string, calls mult_parse on the string, and calls run_cmd on each index of the parsed string returns void.
     
#### _int main(int argc, int *argv[])_
Main function.
