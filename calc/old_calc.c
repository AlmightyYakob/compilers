#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define EOS 256
#define NUM 257

int get_token();
int expr(), term(), factor();
void match(int token);

// Channels connecting scanner and parser
int curr_token;
int curr_attribute;

int main() {
	int value;
	// Init first token
	curr_token = get_token();

	// Call parser (start symbol of grammar)
	value = expr();
	assert(curr_token == EOS);

	// Semantic Eval
	fprintf(stderr, "Value = %d\n", value);
}

// Syntax analyzer (parser)
/* Context-free grammer for the calculator language

Version 1:
	E -> E '+' E | E '*' E | '(' E ')' | NUM
	Problem: ambiguous -> There are at least 2 derivations for "2+3*4"
	E -> E + E -> E + E * E -> .. -> NUM + NUM * NUM
	E -> E * E -> E + E * E -> .. -> NUM + NUM * NUM

Version 2: Introduce precedence ('*') > ('+') and associative laws (left for both)
	E -> E '+' T | T
	T -> T '*' F | F
	F -> '(' E ')' | NUM

	E() {
		T();
		E'();
	}
	E'() {
		if (token == '+'){
			see('+');
			T();
			E'();
		}
		else return;
	}
	
	T() {
		F();
		T'();

		// F() see('*') T'()
		// or
		// F()
	}
	T'() {
		if (token == '*'){
			see('*');
			//stuff
		}
		else return;
	}

	F() {
		if (token == '('){
			see('(') E() see(')')
		}
		else if (token == NUM){
			see(NUM)
		}
		else error()
	}

Version 3: 
	E -> T E'
	E' -> + T E' | empty

	T -> F T'
	T' -> * F T | empty
	F -> ( E ) | NUM
*/

int expr(){
	int value = term();
	while (curr_token == '+'){
		match('+');
		value += term();
	}
	return value;
}

int term(){
	int value = factor();
	while (curr_token == '*'){
		match('*');
		value *= factor();
	}
	return value;
}

int factor(){
	int value;
	if (curr_token == '('){
		match('(');
		value = expr();
		match(')');
	}
	else if (curr_token == NUM){
		value = curr_attribute;
		match(NUM);
	}
	else{
		fprintf(stderr, "\nError in factor()\n");
		exit(1);
	}
	return value;
}

// Lexical analyzer (tokenizer/scanner)
int get_token(){
	int c, value;

	while(1){
		switch(c = getchar()) {
			// Ignore whitespace
			case ' ': case '\t':
				continue;
			case '\n':
				fprintf(stderr, "[EOS] %c", c);
				return EOS;
				
			// Additive operators
			case '+':
				fprintf(stderr, "[ADDOP: %c]", c);
				return c;

			// Multiplicative operator
			case '*':
				fprintf(stderr, "[MULOP: %c]", c);
				return c;
			
			// Process parentheses
			case '(': case ')':
				fprintf(stderr, "[%c]", c);
				return c;

			// Default return character
			default:
				// Process a number: ('0'|'1'|..|'9'|)+
				if (isdigit(c)){
					value = 0;
					do {
						value = 10*value + (c - '0');
					}
					while(isdigit(c = getchar()));
					ungetc(c, stdin);

					// Pass value to channel
					curr_attribute = value;

					fprintf(stderr, "[NUM: %d]", value);
					return NUM;
				}
				else{
					fprintf(stderr, "{%c}", c);
					return c;
					// assert(0);
				}
		}
	}

	return 0;
}

void match (int token){
	if (curr_token == token) {
		curr_token = get_token();
	}
	else {
		fprintf(stderr, "\nBad unexpected token: %c\n", curr_token);
		exit(1);
	}
}
