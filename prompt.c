#include <stdio.h>
#include <stdlib.h>

#include <editline/readline.h>


int main(int argc, char* argv[]) {
  puts("Lispy Version 0.0.0.1");
  puts("To Exit Press Ctrl+c\n");

  while(1) {
    
    /* Output our prompt and get input */
    char *input = readline("lispy> ");

    /* Add input to histroy */
    add_history(input);

    /* Echo input back to user */
    printf("No you're a %s\n", input);

    /* Free retrieved input */
    free(input);
  }

  return 0;

}
