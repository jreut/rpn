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
	int top = 0;
	for (int i = 0; i < length; i++ ) { 
		if (tokens[i].type == OPERAND) {
			stack[top] = tokens[i].contents.operand;
			top++;
		} else { 
			int first = stack[--top];
			int second = stack[--top];
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
	struct token tokens[] = {
		{ .type = OPERAND, .contents = { .operand = 2 }},
		{ .type = OPERAND, .contents = { .operand = 3 }},
		{ .type = OPERATOR, .contents = { .operator = MULTIPLY }}, 
		{ .type = OPERAND, .contents = { .operand = 4 }},
		{ .type = OPERATOR, .contents = { .operator = SUBTRACT }},
		{ .type = OPERAND, .contents = { .operand = 1 }},
		{ .type = OPERAND, .contents = { .operand = 2 }},
		{ .type = OPERAND, .contents = { .operand = 3 }},
		{ .type = OPERATOR, .contents = { .operator = ADD }},
		{ .type = OPERATOR, .contents = { .operator = SUBTRACT }},
		{ .type = OPERATOR, .contents = { .operator = DIVIDE }}
	};
	int expected = -2;
	size_t len = sizeof(tokens) / sizeof(struct token); 
	evaluate(tokens, len, &result);
	printf("got: %d, expected: %d\n", result, expected);
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
