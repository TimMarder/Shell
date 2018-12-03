#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>

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

/* RUN_CMD()
   TAKES IN A STRING AND CALLS PARSE ON IT
   THEN IT DETERMINES IF THE COMMAND IS CD OR EXIT
   IN WHICH CASE IT WILL BE IMMEDIATELY IMPLEMENTED
   IF IT ISN'T EITHER OF THOSE, IT WILL FORK A CHILD
   AND MAKE THE CHILD RUN THE COMMAND */
int run_cmd(char *input){
  pid_t child_a;

  int numtok = count_tok(input);
  printf("%d\n", numtok);
    
  char **parsed = parse(input, numtok);
  //CHANGE DIRECTORY
  //printf("%s %s %s\n", parsed[0], parsed[1], parsed[2]);
  if ( strcmp(parsed[0], "cd" ) == 0) {
    chdir(parsed[1]);
  }
  //EXIT
  else if ( strcmp(parsed[0], "exit") == 0) {
    exit(0);
  }
  else {
    child_a = fork();
    if(child_a == 0){
      printf("%d %d\n", getpid(), getppid() );
      execvp(parsed[0], parsed);
      printf("%s\n", strerror(errno));
      return 0;
    }
    int status;
    int kid = wait(&status);
  }
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

/* MAIN() */
int main(int argc, int *argv[]){
  while(1){
    char input[256];
    fgets(input, 256, stdin);
    if(strstr(input, ";")){
      //RUN MULTIPLE COMMANDS
      int numtok = count_tok(input);
      char **mult_parsed = mult_parse(input, numtok);
      for(int i = 0; i < numtok; i ++){
	printf("%s\n", mult_parsed[i]);
	run_cmd(mult_parsed[i]);
      }
    }
    else{
      //RUN ONE COMMAND
      run_cmd(input);
    }
  }
  return 0;
}
