%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "calcul.h"
%}

%union {
    struct ast *a;
    double d;
}

%token <d> NUMBER
%token EOL

%left '+' '-'
%left '*' '/'

%type <a> exp

%start stmt

%%

stmt: exp EOL {
        printf("= %4.4g\n", eval($1));
        treefree($1);
        YYACCEPT;
    }
    ;

exp: exp '+' exp { $$ = newast('+', $1, $3); }
    | exp '-' exp { $$ = newast('-', $1, $3); }
    | exp '*' exp { $$ = newast('*', $1, $3); }
    | exp '/' exp { $$ = newast('/', $1, $3); }
    | '(' exp ')' { $$ = $2; }
    | '-' exp %prec UMINUS { $$ = newast('M', $2, NULL); }
    | NUMBER { $$ = newnum($1); }
    ;

%%
