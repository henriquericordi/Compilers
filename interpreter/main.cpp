#include <cstdio>
#include <iostream>
#include <cctype>
#include <cstdlib>
#include "bib.h"

using namespace std;

void print_char(char);
void print_number(int);
void prog();
void loop();
void cmd();
void expr();
void rest();
void match(int);

token lookahead;

// auxiliares do calculo de <expr>
int calculus = 0;
int value_ant = 0;

void print_char(char c) {
	printf("%c ", c);
}

void print_number(int i) {
	printf("%d ", i);
}

void prog() {
	cmd();
	loop();
}

void loop() {
	if (lookahead.type != EOF) {
		prog();
	}
  else {
    //fim
  }
}

void cmd() {
	if (lookahead.type == VAR) {
		int var_reference = lookahead.value;
		match(VAR); match(EQUALS); expr(); value_insertion(var_reference, calculus); calculus = 0;
	}
	else if (lookahead.type == PRINT) {
		match(PRINT); expr(); cout << calculus << endl; calculus = 0;
	}
	else {
		printf("Error CMD\n");
        exit(1);
	}
}

void expr() {
	if (lookahead.type == VAR) {
	  value_ant = get_value(lookahead.value);
		match(VAR); rest();
	}
	else if (lookahead.type == NUM) {
	  value_ant = lookahead.value;
		match(NUM); rest();
	}
	else {
    printf("Error EXPR\n");
    exit(1);
	}
}

void rest() {
	if (lookahead.type == PLUS) {
		calculus += value_ant; match(PLUS); expr();
	}
	else if (lookahead.type == EOL) {
		calculus += value_ant; match(EOL);
	}
	else {
		printf("Error REST\n");
        exit(1);
	}
}

void match(int type) {
	if (lookahead.type == type) {
		lookahead = next_token();
	}
	else {
		printf("Match error");
	}
}

int main() {
	getline(cin, input);
	while (input != "") {
		pos = 0;
		lookahead = next_token();
		prog();
		getline(cin, input);
	}
	return 0;
}
