#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>


char **parse(char *line, int argc){
  if(strstr(line, "\n")){
    line[strlen(line) -1] = '\0';
  }
  char **ret = calloc(256, sizeof(char));
  for(int i = 0; i < argc +1; i++){
    ret[i] = strsep(&line, " ");
  }
  return ret;
}

char **mult_parse(char *line, int argc){
  line[strlen(line) -1] = '\0';
  char **ret = calloc(256, sizeof(char));
  for(int i = 0; i < argc +1; i++){
    ret[i] = strsep(&line, ";");
  }
  return ret;
}

int run_cmd(char *input, int argc){
  pid_t child_a;
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

int main(int argc, char *argv[]){

  while(1){
    char *input = calloc(256, sizeof(char));

    fgets(input, 256, stdin);

    if(strstr(input, ";")){
      char **mult_parsed = mult_parse(input, argc);
      printf("%d %s %s %s\n", argc, mult_parsed[0], mult_parsed[1], mult_parsed[2]); 
      for(int i = 0; i < argc +1; i ++){
	run_cmd(mult_parsed[i], argc);
      }
    }
    else{
      run_cmd(input, argc);
    }    
  }
  return 0;

}
