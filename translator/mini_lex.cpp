#include "cstdio"
#include "string"
#include "iostream"
#include "cstdlib"

// constantes para types dos tokens
#define NUM 256
#define PLUS 257
#define MINUS 258
#define MULT 259
#define DIV 260
#define EQUALS 261
#define EOL 262
#define PRINT 263
#define VAR 264
#define ERR 1000

using namespace std;

// estrutura de representação dos Tokens
struct token
{
    int type;
    double value;
};

double stack[50];

// entrada para o Lex
string input;
// posição atual (char) em input
int pos = 0;
// char auxiliar para "manter" o último símbolo
char c = EOF;
// contagem da linha atual
int current_line = 0;

// retorno o type do token (recebe um int)
string token_name(int t)
{
    switch (t)
    {
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
    }
    return "ERROR";
}

// faz a leitura de um char em input
char get_char()
{
    if (pos < input.length())
    {
        return input[pos++];
    }
    if (input[pos] == ';') {
        return EOL;
    }
    else
    {
        return EOF;
    }
}

// faz a identificação do próximo Token na input e o retorna
token next_token() {
    token t;
    char peek;
    // manter o último símbolo ou requisitar um novo
    if (c == EOF)
    {
        peek = get_char();
    }
    else
    {
        peek = c;
        c = EOF;
    }
    //ignorar espaços e tabulações
    do
    {
        if (peek == ' ' || peek == '\t')
            continue;
        else if (peek == '\n')
            current_line++;
        else
            break;
    } while (peek = get_char());
    // identificação de inteiros e reais
    if (isdigit(peek)) {
        int v = 0;
        double r = 0.0;
        do
        {
            v = v * 10 + atoi(&peek);
            peek = get_char();
        } while (isdigit(peek));
        // continuação como real
        if (peek == '.')
        {
            peek = get_char();
            double factor = 1.0;
            do
            {
                //r *= factor;
                factor /= 10.0;
                r += atoi(&peek) * factor;
                peek = get_char();
            } while (isdigit(peek));
        }
        double number = (double)v + r;
        t.type = NUM;
        t.value = number;
        c = peek;
    }
    else if (peek == '+')
    {
        t.type = PLUS;
    }
    else if (peek == '-')
    {
        t.type = MINUS;
    }
    else if (peek == ';') {
      t.type = EOL;
    }
    else if (peek = '=') {
      t.type = EQUALS;
    }
    else if (peek = "print") {
      t.type = PRINT;
    }
    else if (peek == EOF)
    {
        t.type = EOF;
    }
    else
    {
        t.type = ERR;
    }
    return t;
}
