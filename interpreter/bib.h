#include "cstdio"
#include "string"
#include "iostream"
#include "cstdlib"
#include <cctype>
#include <vector>
// constantes para types dos tokens
#define NUM 256
#define PLUS 257
#define MINUS 258
#define MULT 259
#define DIV 260
#define EQUALS 261
#define EOL '\n'
#define PRINT 263
#define VAR 264
#define ERR 1000

using namespace std;

struct info {
  string lexeme;
  int value;
};
struct token { // estrutura de representacao dos Tokens
    int type;
    double value;
};
string input; // entrada para o Lex
int pos = 0; // posicao atual (char) em input
char c = EOF; // char auxiliar para "manter" o ultimo simbolo
int current_line = 0; // contagem da linha atual

typedef vector<info> table; // referencia a tabela de simbolos

table symbols; // a tabela de simbolos

bool is_there(string lexeme) {
  for (int i = 0; i < symbols.size(); i++) {
    info aux = symbols[i];
    if (aux.lexeme == lexeme) {
        return true;
    }
  }
  return false;
}

int key_insertion(string lexeme) { // insere uma nova variavel na tabela
  if (!is_there(lexeme)) {
    info aux;
    aux.lexeme = lexeme;
    symbols.push_back(aux);
    return symbols.size() - 1;
  }
  else {
    return -1;
  }
}

bool value_insertion(int index, int value) { // insere/altera o valor de uma variavel
  if (index >= 0 && index < symbols.size()) {
    info aux = symbols[index];
    aux.value = value;
    symbols[index] = aux;
    return true;
  }
  else {
    return false;
  }
}

int get_value(int index) { // retorna o valor de uma variavel
  if (index >= 0 && index < symbols.size()){
    info aux = symbols[index];
    return aux.value;
  }
  else
  {
    return -1;
  }
}

int get_index(string lexeme) { // retorna o indice de uma variavel
  for (int i = 0; i < symbols.size(); i++) {
    info aux = symbols[i];
    if (aux.lexeme == lexeme) {
      return i;
    }
  }
  return -1;
}

string token_name(int t) { // retorno o type do token (recebe um int)
    switch (t) {
      case NUM:
        return "NUM";
      case PLUS:
        return "PLUS";
      case MINUS:
        return "MINUS";
      case EQUALS:
        return "EQUALS";
      case PRINT:
        return "PRINT";
      case VAR:
        return "VAR";
      case EOL:
        return "EOL";
    }
    return "ERROR";
}

char get_char() { // faz a leitura de um char em input
    if (pos < input.length()) {
        return input[pos++];
    }
    else {
        return EOF;
    }
}

token next_token() { // faz a identificação do próximo Token na input e o retorna
	token t;
	char peek; // manter o último símbolo ou requisita um novo
	if (c == EOF) {
		peek = get_char();
	}
	else {
		peek = c;
		c = EOF;
	}
	do { //ignorar espaços e tabulações
		if (peek == ' ' || peek == '\t'){
      continue;
    }
		else if (peek == '\n'){
      current_line++;
    }
		else{
      break;
    }
	} while (peek = get_char());
	if (isdigit(peek)) { // identificação de inteiros
		int v = 0;
		double r = 0.0;
		do {
			v = v * 10 + atoi(&peek);
			peek = get_char();
		} while (isdigit(peek));
		t.type = NUM;
		t.value = v;
		c = peek;
	}
	else if (isalpha(peek)) { // identificação de palavras
		string aux = "";
		do {
			aux += peek;
			peek = get_char();
		} while (isalpha(peek));
		if (aux == "print") {
			t.type = PRINT;
		}
		else {
			t.type = VAR;
			int pos = key_insertion(aux);
			if (pos != -1) {
        t.value = pos;
      }
      else {
        t.value = get_index(aux);
      }
		}
		c = peek;
	}
	else if (peek == '+') {
		t.type = PLUS;
	}
	else if (peek == '=') {
		t.type = EQUALS;
	}
  else if (peek == ';') {
		t.type = EOL;
	}
	else if (peek == EOF) {
		t.type = EOF;
	}
	else {
		t.type = ERR;
	}
	return t;
}
