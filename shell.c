#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <fcntl.h>

/* COUNT_TOK()
   TAKES A STRING AND RETURNS HOW MANY TOKENS ARE IN IT
   ACCORDING TO HOW MANY SPACES ARE IN THE STRING */
int count_tok(char *input){
  int ctr = 0;
  char *ptr = input;
  if(strstr(input, ";")){
    while((ptr = strchr(ptr, ';')) != NULL){
      ctr ++;
      ptr ++;
    }
  }
  else{
    while((ptr = strchr(ptr, ' ')) != NULL){
      ctr ++;
      ptr ++;
    }
  }
  return ctr +1;
}

/* PARSE()
   TAKES A STRING AND THE NUMBER OF TOKENS IN THE STRING
   SEPARATES THE STRING AT THE SPACES
   RETURNS A DOUBLE POINTER TO THE SEPARATED STRINGS */
char **parse(char *line, int numtok){
  if(strstr(line, "\n")){
    line[strlen(line) -1] = '\0';
  }
  char **ret = calloc(256, sizeof(char));
  for(int i = 0; i < numtok +1; i++){
    ret[i] = strsep(&line, " ");
  }
  return ret;
}

/* MULT_PARSE()
   TAKES IN A STRING, REMOVES THE NEWLINE, SEPARATES IT BY
   SEMICOLONS, AND RETURNS A DOUBLE POINTER
 */
char **mult_parse(char *line, int numtok){
  line[strlen(line) -1] = '\0';
  char **ret = calloc(256, sizeof(char));
  for(int i = 0; i < numtok +1; i ++){
    ret[i] = strsep(&line, ";");
  }
  return ret;
}

/* REDIRECT_OUT()
   TAKES A DOUBLE POINTER AND FORKS A CHILD
   OPENS A FILE DUPLICATE OF STDOUT AND EXECUTES THE COMMAND
   RETURNS VOID
*/
void redirect_out(char **parsed){
  pid_t child_a = fork();
  if(child_a == 0){
    int fd = open(parsed[2], O_CREAT | O_WRONLY , 0666);
    dup2(fd, STDOUT_FILENO);
    close(fd);
    parsed[1] = NULL;
    execvp(parsed[0], parsed);
    exit(0);
  }
}

/* REDIRECT_IN()
   TAKES IN A DOUBLE POINTER AND
   REDIRECTS THE INPUT OF A COMMAND FROM A FILE
 */
void redirect_in(char **parsed){
  pid_t child_a = fork();
  if(child_a == 0){
    printf("1");
    int fd = open(parsed[2], O_RDONLY, 0666);
    dup2(fd, STDIN_FILENO);
    close(fd);
    parsed[1] = NULL;
    execvp(parsed[0], parsed);
    exit(0);
  }
}

/* RUN_CMD()
   TAKES IN A STRING AND CALLS PARSE ON IT
   THEN IT DETERMINES IF THE COMMAND IS CD OR EXIT
   IN WHICH CASE IT WILL BE IMMEDIATELY IMPLEMENTED
   IF IT ISN'T EITHER OF THOSE, IT WILL FORK A CHILD
   AND MAKE THE CHILD RUN THE COMMAND */
int run_cmd(char *input){
  int numtok = count_tok(input);

  char **parsed = parse(input, numtok);
  //CHANGE DIRECTORY
  if ( strcmp(parsed[0], "cd" ) == 0) {
    chdir(parsed[1]);
  }
  //EXIT
  else if ( strcmp(parsed[0], "exit") == 0) {
    exit(0);
  }
  //REDIRECTION
  else if (numtok > 1 && strcmp(parsed[1], ">") == 0){
    redirect_out(parsed);
  }
  else if (numtok > 1 && strcmp(parsed[1], "<") == 0){
    redirect_in(parsed);
  }
  //EXEC COMMAND
  else{
    pid_t child_a = fork();
    if(child_a == 0){
      execvp(parsed[0], parsed);
      exit(0);
    }
  }
}

/* RUN_MULT_CMD()
   TAKES IN A STRING, CALLS MULT_PARSE ON THE STRING,
   AND CALLS RUN_CMD ON EACH INDEX OF THE PARSED STRING
   RETURNS VOID */
void run_mult_cmd(char *input){
  int numtok = count_tok(input);
  char **mult_parsed = mult_parse(input, numtok);
  for(int i = 0; i < numtok; i ++){
    run_cmd(mult_parsed[i]);
  }
}

/* MAIN() */
int main(int argc, int *argv[]){
  while(1){
    char input[256];
    fgets(input, 256, stdin);
    if(strstr(input, ";")){
      //RUN MULTIPLE COMMANDS
      run_mult_cmd(input);
    }
    else{
      //RUN ONE COMMAND
      run_cmd(input);
    }
  }
  return 0;
}
