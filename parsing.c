#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <editline/readline.h>

#include "lib/mpc.h"

/* Use operator string to see which operation to perform */
long eval_op(long x, char* op, long y) {
    if (strcmp(op, "+") == 0) { return x + y; }
    if (strcmp(op, "-") == 0) { return x - y; }
    if (strcmp(op, "*") == 0) { return x * y; }
    if (strcmp(op, "/") == 0) { return x / y; }
    return 0;
}

long eval(mpc_ast_t* tree) {
    
    /* If tagged as number return it directly, otherwise expression. */
    if(strstr(tree->tag, "number")) { return atoi(tree->contents); }

    /* The operator is always the second child. */
    char* op = tree->children[1]->contents;

    /* We store the third child in `x` */
    long x = eval(tree->children[2]);

    /* Iterate the remaining children, combining using our operator */
    int i = 3;
    while (strstr(tree->children[i]->tag, "expr")){
	x = eval_op(x, op, eval(tree->children[i]));
	i++;
    }

    return x;
}

int number_of_leaves(mpc_ast_t* tree) {
    if(tree->children_num == 0) { return 1; }

    int x = number_of_leaves(tree->children[2]);

    int i = 3;
    while (strstr(tree->children[i]->tag, "expr")) {
	x = x + number_of_leaves(tree->children[i]);
	i++;
    }

    return x;
    
}


int main(int argc, char* argv[]) {
    /* Create Some Parsers */
    mpc_parser_t* Number = mpc_new("number");
    mpc_parser_t* Operator = mpc_new("operator");
    mpc_parser_t* Expr = mpc_new("expr");
    mpc_parser_t* Lispy = mpc_new("lispy");

/* Define them with the following Language */
    mpca_lang(MPCA_LANG_DEFAULT,
	      " \
  number : /-?[0-9]+/ ;				 \
  operator: '+' | '-' | '*' | '/';		 \
  expr : <number> | '(' <operator> <expr>+ ')' ; \
  lispy : /^/ <operator> <expr>+ /$/ ;					\
  ",
	      Number, Operator, Expr, Lispy);

    puts("Lispy Version 0.0.0.3");
    puts("To Exit Press Ctrl+c\n");

    while(1) {

	/* Output our prompt and get input */
	char *input = readline("lispy> ");

	/* Add input to histroy */
	add_history(input);

	/* Attempt to Parse the user Input */
	mpc_result_t r;

	if (mpc_parse("<stdin>", input, Lispy, &r)) {
	    long result = eval(r.output);
	    int leaves = number_of_leaves(r.output);
	    printf("Leaves: %d\n", leaves);
	    printf("%li\n", result);
	    mpc_ast_print(r.output);
	    mpc_ast_delete(r.output);
	} else {
	    /* Otherwise Print the Error */
	    mpc_err_print(r.error);
	    mpc_err_delete(r.error);
	}


	
	/* Free retrieved input */
	free(input);
    }

    /* Undefine and Delete our Parsers */
    mpc_cleanup(4, Number, Operator, Expr, Lispy);

    return 0;

}
