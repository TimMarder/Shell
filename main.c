#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

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
