#include <stdlib.h>
#include <stdio.h>

enum operator {
	ADD,
	SUBTRACT,
	MULTIPLY,
	DIVIDE
};

enum token_type {
	OPERATOR,
	OPERAND
};

struct token {
	enum token_type type;
	union {
		int operand;
		enum operator operator;
	} contents;
};

int
evaluate(struct token *tokens, size_t length, int *result)
{
	int *stack = malloc(sizeof(int) * length);
	int first, second, top = 0;
	for (int i = 0; i < length; i++ ) { 
		switch (tokens[i].type) {
		case OPERAND:
			stack[top++] = tokens[i].contents.operand;
			break;
		case OPERATOR:
			first = stack[--top];
			second = stack[--top];
			switch (tokens[i].contents.operator) {
			case ADD: 
				stack[top++] = first + second;
				break;
			case SUBTRACT:
				stack[top++] = first - second;
				break;
			case MULTIPLY:
				stack[top++] = first * second;
				break;
			case DIVIDE:
				stack[top++] = first / second;
				break;
			}
			break;
		}
	}
	*result = stack[--top];
	free(stack);	
	return 0;
}

int
main(int argc, char *argv[])
{
	int result;
	struct token* tokens = malloc(sizeof(struct token) * argc);

	for (int i = 1; i < argc; i++) {
		switch (argv[i][0]) {
			case '+':
				tokens[i-1].type = OPERATOR;
				tokens[i-1].contents.operator = ADD;
				break;
			case '-':
				tokens[i-1].type = OPERATOR;
				tokens[i-1].contents.operator = SUBTRACT;
				break;
			case '*':
				tokens[i-1].type = OPERATOR;
				tokens[i-1].contents.operator = MULTIPLY;
				break;
			case '/':
				tokens[i-1].type = OPERATOR;
				tokens[i-1].contents.operator = DIVIDE;
				break;
			default:
				tokens[i-1].type = OPERAND;
				tokens[i-1].contents.operand = atoi(argv[i]);
				break;
		}
	}
	evaluate(tokens, argc - 1, &result);
	printf("got: %d\n", result);
}

/*
 * 1 2 +
 * => 3
 * 1 2 3 + *
 * 1
 * 1 2
 * 1 2 3
 * 1 5
 * 5
 */
