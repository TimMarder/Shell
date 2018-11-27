#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>

//first separate input with the " " delimiter
//then make the first index the command
//for following indexes, if they begin with "-"
//add a space followed by the flas to the command string
//then the rest of the indexes should be the arguments

char **parse(char *line){
  char **ret = calloc(256, sizeof(char));
  for(int i = 0; ret[i] = strsep(&line, " "); i++);
  return ret;
}

void sep_cmd_arg(char **line, char *cmd, char *args){
  cmd = calloc(256, sizeof(char));
  args = calloc(256, sizeof(char));
  int length = strlen(*line);
  strncat(cmd, line[0], 256);
  printf("%s\n", cmd);
  for(int i = 1; i < length; i ++){
    printf("%s\n", line[i]);
    if(strncmp(line[i], "-", 1) == 0){
      //strncat(" ", cmd, 256);
      strncat(cmd, line[i], 256);
      //printf("%s\n", line[i]);
      printf("cmd added: %s\n", cmd);
    }
    else{
      strncat(args, line[i], 256);
      printf("args added: %s\n", args);
    }
  }
}

int main(int argc, char *argv[]){

  char input[256];
  char cmd[256];
  char args[256];

  fgets(input, 256, stdin);

  char **parsed = parse(input);
  printf("%s %s %s\n", parsed[0], parsed[1], parsed[2]);

  //printf("%d\n", strncmp("-a", "-", 1));
  sep_cmd_arg(parsed, cmd, args);
  //printf("%s %s\n", cmd, args);
  //execvp(args[0], args);
}