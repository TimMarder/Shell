#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>


char **parse(char *line, int argc){
  line[strlen(line) -1] = '\0';
  char **ret = calloc(256, sizeof(char));
  for(int i = 0; i < argc +1; i++){
    ret[i] = strsep(&line, " ");
  }
  return ret;
}


int main(int argc, char *argv[]){
  while(1){
    pid_t child_a;

    char *input = calloc(256, sizeof(char));

    fgets(input, 256, stdin);


    char **parsed = parse(input, argc);
    printf("%s %s %s\n", parsed[0], parsed[1], parsed[2]);

    if ( strcmp(parsed[0], "cd" ) == 0) {
        chdir(parsed[1]);
    }

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
  return 0;
}
