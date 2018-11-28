#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#define LSH_RL_BUFSIZE 1024

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

//TEST
char *lsh_read_line(void)
{
  int bufsize = LSH_RL_BUFSIZE;
  int position = 0;
  char *buffer = malloc(sizeof(char) * bufsize);
  int c;

  if (!buffer) {
    fprintf(stderr, "lsh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  while (1) {
    // Read a character
    c = getchar();

    // If we hit EOF, replace it with a null character and return.
    if (c == EOF || c == '\n') {
      buffer[position] = '\0';
      return buffer;
    } else {
      buffer[position] = c;
    }
    position++;

    // If we have exceeded the buffer, reallocate.
    if (position >= bufsize) {
      bufsize += LSH_RL_BUFSIZE;
      buffer = realloc(buffer, bufsize);
      if (!buffer) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}

int main(int argc, char *argv[]){

  char input[256];
  //char newinput[256];
  char cmd[256];
  char args[256];

  fgets(input, 256, stdin);

  /*for (int i = 0 ; i < sizeof(input) - 2 ; i++) {
      newinput[i] = input[i];
  }*/

  char **parsed = parse(input);
  printf("%s %s %s\n", parsed[0], parsed[1], parsed[2]);

  //printf("%d\n", strncmp("-a", "-", 1));
  sep_cmd_arg(parsed, cmd, args);
  //printf("%s %s\n", cmd, args);
  //execvp(args[0], args);
}
