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

char **parse(char *line, int argc){
  line[strlen(line) -1] = '\0';
  char **ret = calloc(256, sizeof(char));
  for(int i = 0; i < argc +1; i++){
    ret[i] = strsep(&line, " ");
  }
   //remove the new lines
  return ret;
}

int main(int argc, char *argv[]){

<<<<<<< HEAD
  while(1){
    pid_t child_a;
  
    char *input = calloc(256, sizeof(char));

    fgets(input, 256, stdin);
=======
  char input[256];
  //char newinput[256];
  char cmd[256];
  char args[256];
>>>>>>> d8a3cabc0ce258685b20c1653667dc6b9796dd44

    char **parsed = parse(input, argc);
    printf("%s %s %s\n", parsed[0], parsed[1], parsed[2]);

<<<<<<< HEAD
    child_a = fork();
=======
  /*for (int i = 0 ; i < sizeof(input) - 2 ; i++) {
      newinput[i] = input[i];
  }*/

  char **parsed = parse(input);
  printf("%s %s %s\n", parsed[0], parsed[1], parsed[2]);
>>>>>>> d8a3cabc0ce258685b20c1653667dc6b9796dd44

    if(child_a == 0){
      printf("%d %d\n", getpid(), getppid() );
      execvp(parsed[0], parsed);
      printf("%s\n", strerror(errno));
    }
    kill(child_a, SIGKILL);
    return 1;
  }
}
